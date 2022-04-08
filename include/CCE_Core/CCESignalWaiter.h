/*********************************************************************************************************
** This file is part of the CCE_Core module of the CCE Toolkit.
*********************************************************************************************************/
#ifndef CHROMX_H_CCESIGNALWAITER
#define CHROMX_H_CCESIGNALWAITER
#pragma once

#include <CCE_Core/CCECoreGlobal>

#include <QObject>
#include <QEventLoop>

class CCESignalWaiterPrivate;
class CCE_CORE_EXPORT CCESignalWaiter : public QObject
{
	Q_OBJECT
	Q_DECLARE_PRIVATE(CCESignalWaiter)
public:
	CCESignalWaiter(const QObject* sender, const char* signal);
	~CCESignalWaiter();

	static bool wait(const QObject* sender, const char* signal, int msec = -1, QEventLoop::ProcessEventsFlags flags = QEventLoop::AllEvents);
	bool wait(int msec = -1, bool forceWait = false, QEventLoop::ProcessEventsFlags flags = QEventLoop::AllEvents);
	bool hasCapturedSignal() const;

public Q_SLOTS:
	void signalCaught();
	void cancelWait();

private:
	void timerEvent(QTimerEvent* event);
private:
	QScopedPointer<CCESignalWaiterPrivate> d_ptr;
};
#endif
