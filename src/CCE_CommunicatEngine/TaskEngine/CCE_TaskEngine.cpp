#include "CCE_TaskEngine.h"
#include "CCE_TaskEngine_TaskBase.h"
#include "CCE_TaskEngine_WorkingThread.h"

CCE_TaskEngine::CCE_TaskEngine(QObject *parent/* = 0*/) :
    QObject(parent)
{
    m_nExistingThreads = 0;
    creatThreads(m_nThread);
}

CCE_TaskEngine::~CCE_TaskEngine()
{
}

int CCE_TaskEngine::creatThreads(int nThreads)
{
    if (nThreads >= 1 && nThreads <= 128)
    {
        for (int i = 0; i < nThreads; i++)
        {
            CCE_TaskEngine_WorkingThread * thread = new CCE_TaskEngine_WorkingThread(this);
            m_vec_workingThreads.push_back(thread);
            QThread * pTh = new QThread(this);
            m_vec_InternalworkingThreads.push_back(pTh);
            thread->moveToThread(pTh);
            connect(this, &CCE_TaskEngine::sig_start_work, thread, &CCE_TaskEngine_WorkingThread::slot_FetchNewTask, Qt::QueuedConnection);
            connect(this, &CCE_TaskEngine::sig_stop_work, thread, &CCE_TaskEngine_WorkingThread::slot_SetStopMark, Qt::QueuedConnection);
            connect(thread, &CCE_TaskEngine_WorkingThread::sig_taskFinished, this, &CCE_TaskEngine::slot_finished_task, Qt::QueuedConnection);
            pTh->start();
            m_mutex_protect.lock();
            m_nExistingThreads++;
            m_mutex_protect.unlock();
        }

    }
    return m_vec_workingThreads.size();
}

int CCE_TaskEngine::removeThreads(int nThreads)
{
    int nsz = m_vec_workingThreads.size();
    if (nThreads<0 || nThreads>nsz)
        nThreads = nsz;

    for (int i = 0; i < nThreads; i++)
    {
        emit sig_stop_work(m_vec_workingThreads.last()); //发送信号给工作线程，让他自己退出并销毁
        m_vec_InternalworkingThreads.last()->deleteLater();
        m_vec_workingThreads.pop_back();
        m_vec_InternalworkingThreads.pop_back();
    }
    return m_vec_workingThreads.size();
}

int CCE_TaskEngine::threadsCount()
{
    return m_vec_workingThreads.size();
}

int CCE_TaskEngine::payload()
{
    int res = 0;
    m_mutex_protect.lock();
    res = int(m_list_tasks.size());
    m_mutex_protect.unlock();

    return res;
}

int CCE_TaskEngine::idleThreads()
{
    int idle = 0;
    int nsz = m_vec_workingThreads.size();
    for (int i = 0; i < nsz; i++)
    {
        if (m_vec_workingThreads[i]->m_bBusy == false)
            idle++;
    }
    return idle;
}

bool CCE_TaskEngine::canExit()
{
    if(m_nExistingThreads!=0){
        removeThreads(-1);
    }
    return m_nExistingThreads == 0 ? true : false;
}

CCE_TaskEngine_TaskBase * CCE_TaskEngine::popTask(bool * bValid)
{
    *bValid = false;
    CCE_TaskEngine_TaskBase * funcres = 0;
    m_mutex_protect.lock();
    if (m_list_tasks.empty() == false)
    {
        funcres = *m_list_tasks.begin();
        m_list_tasks.pop_front();
        *bValid = true;
    }
    m_mutex_protect.unlock();
    return funcres;
}

void CCE_TaskEngine::slot_pushTask(CCE_TaskEngine_TaskBase * task, bool bFire)
{
    m_mutex_protect.lock();
    m_list_tasks.push_back(task);
    task->addRef();
    m_mutex_protect.unlock();

    int nsz = m_vec_workingThreads.size();
    if (0 == nsz) {
        creatThreads(m_nThread);
    }
    if (bFire == true)
        for (int i = 0; i < nsz; i++)
        {
            if (m_vec_workingThreads[i]->m_bBusy == false)
            {
                slot_finished_task(m_vec_workingThreads[i]);
                break;
            }
        }
}

void CCE_TaskEngine::slot_finished_task(CCE_TaskEngine_WorkingThread* taskThread)
{
    int res = 0;
    m_mutex_protect.lock();
    res = int(m_list_tasks.size());
    m_mutex_protect.unlock();
    if (res)
        emit sig_start_work(taskThread);
}
