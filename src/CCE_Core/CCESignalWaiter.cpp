/*********************************************************************************************************
** This file is part of the CCE_Core module of the CCE Toolkit.
*********************************************************************************************************/

/*!
\class CCESignalWaiter

\inmodule CCE_Core

\brief The CCESignalWaiter class blocks and processes events until a signal is emitted

In many cases, writing code that assumes certain actions are synchronous is considerably simpler than breaking your function into
multiple blocks and using signals and slots to connect them all. Using this class, CCESignalWaiter::wait will block until a certain
signal is emitted and then return. The return value is true if the signal was caught, or false if a user-specified timeout elapses
before catching the signal.

\code
void MyObject::myFunction() {
	CCESignalWaiter waiter(myOtherObject, SIGNAL(longProcessFinished()));
	myOtherObject->longProcess();
	if (waiter.wait(5000)) {
		doSomething(myOtherObject->information());
	}
	else {
		QMessageBox::information(0, "MyObject", "Timed out while waiting on longProcessFinished()", QMessageBox::Ok);
	}
}
\endcode

\bold {Note:}
CCESignalWaiter is not reentrant. In particular, only one CCESignalWaiter object per thread can be safely waiting at a
time. If a second CCESignalWaiter is used while the first is waiting, the first will not return until the second has
timed out or successfully caught its signal.
*/

#include "CCE_Core/CCESignalWaiter.h"

#include <QCoreApplication>
#include <QTimerEvent>

class CCESignalWaiterPrivate
{
public:
	Q_DECLARE_PUBLIC(CCESignalWaiter)

		CCESignalWaiterPrivate()
	{
		ready = false;
		emitted = false;
		timeout = false;
		waiting = false;
	}

	bool ready, timeout, emitted, waiting;
	int timerID;
	CCESignalWaiter* q_ptr = nullptr;
	void stopTimer()
	{
		if (timerID)
			q_ptr->killTimer(timerID);
		timerID = 0;
		waiting = false;
	}
};

CCESignalWaiter::CCESignalWaiter(const QObject* sender, const char* signal)
	:d_ptr(new CCESignalWaiterPrivate)
{
	d_ptr->q_ptr = this;
	Q_ASSERT(sender && signal);
	if (sender&&signal)
		connect(sender, signal, this, SLOT(signalCaught()));
}

CCESignalWaiter::~CCESignalWaiter()
{
}

bool CCESignalWaiter::wait(const QObject * sender, const char * signal, int msec, QEventLoop::ProcessEventsFlags flags)
{
	CCESignalWaiter w(sender, signal);
	return w.wait(msec, false, flags);
}

bool CCESignalWaiter::wait(int msec, bool forceWait, QEventLoop::ProcessEventsFlags flags)
{
	Q_D(CCESignalWaiter);
	// Clear the emission status
	d->ready = false;
	d->emitted = false;

	// Check input parameters
	if (msec < -1 || msec == 0)
		return false;

    // activate the timeout
	if (msec != -1)
		d->timerID = startTimer(msec);

	// Make sure to wait for events
	flags |= QEventLoop::WaitForMoreEvents;

	// Begin waiting
	d->waiting = true;
	if (forceWait) {
		while (!d->timeout)
			QCoreApplication::processEvents(flags);
		d->ready = true;
	}
	else {
		while (!d->ready && !d->timeout)
			QCoreApplication::processEvents(flags);
	}
	// Clean up and return status
	d->stopTimer();
	d->emitted = d->ready;
	d->waiting = false;
	return d->ready;
}

bool CCESignalWaiter::hasCapturedSignal() const
{
	return d_func()->emitted;
}

void CCESignalWaiter::signalCaught()
{
	Q_D(CCESignalWaiter);
	if (!d->waiting) return;
	d->ready = true;
	d->stopTimer();
}

void CCESignalWaiter::cancelWait()
{
	Q_D(CCESignalWaiter);
	if (!d->waiting) return;
	d->timeout = true;
	d->stopTimer();
}

void CCESignalWaiter::timerEvent(QTimerEvent* event)
{
	Q_UNUSED(event);
	cancelWait();
}
