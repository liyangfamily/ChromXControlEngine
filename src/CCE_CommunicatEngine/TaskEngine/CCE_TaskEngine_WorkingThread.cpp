#include "CCE_TaskEngine_WorkingThread.h"
#include "CCE_TaskEngine.h"
#include "CCE_TaskEngine_TaskBase.h"

CCE_TaskEngine_WorkingThread::CCE_TaskEngine_WorkingThread(CCE_TaskEngine * taskEngine, QObject *parent /*= 0*/) :
    QObject(parent)
{
    m_bRuning = true;
    m_taskEngine = taskEngine;
    Q_ASSERT(m_taskEngine != NULL);
    m_bBusy = false;
}

CCE_TaskEngine_WorkingThread::~CCE_TaskEngine_WorkingThread()
{
}

void CCE_TaskEngine_WorkingThread::slot_SetStopMark(CCE_TaskEngine_WorkingThread* taskThread)
{
    if (taskThread != this)
        return;
    m_bRuning = false;
    m_taskEngine->m_mutex_protect.lock();
    m_taskEngine->m_nExistingThreads--;
    m_taskEngine->m_mutex_protect.unlock();
    this->deleteLater();
    QThread::currentThread()->quit();
}

void CCE_TaskEngine_WorkingThread::slot_FetchNewTask(CCE_TaskEngine_WorkingThread* taskThread)
{
    if (taskThread != this)
        return;
    if (m_bRuning)
    {

        bool bValid = false;
        CCE_TaskEngine_TaskBase * ptr = this->m_taskEngine->popTask(&bValid);

        if (bValid == true && ptr != NULL)
        {
            m_bBusy = true;
            if (ptr->lockRun() == true)
            {
                int res = ptr->run();
                ptr->delRef();
                if (res != 0)
                    this->m_taskEngine->slot_pushTask(ptr, false);
                ptr->unlockRun();
            }
            else
            {
                ptr->delRef();
                this->m_taskEngine->slot_pushTask(ptr, false);
            }
            m_bBusy = false;

        }

        emit sig_taskFinished(this);

    }

}
