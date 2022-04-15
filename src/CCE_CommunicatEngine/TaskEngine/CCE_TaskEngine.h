/*********************************************************************************************************/
/*任务处理引擎，任务队列采用FIFO。
*********************************************************************************************************/
#ifndef CHROMXH_CCE_TASKENGINE
#define CHROMXH_CCE_TASKENGINE
#pragma once

#include <QObject>
#include <QMutex>
#include <QThread>
#include <QVector>
#include <list>

class CCE_TaskEngine_TaskBase;
class CCE_TaskEngine_WorkingThread;
class CCE_TaskEngine : public QObject
{
    Q_OBJECT
    friend class CCE_TaskEngine_WorkingThread;
public:
    explicit CCE_TaskEngine(QObject *parent = 0);
    ~CCE_TaskEngine();
    int creatThreads(int nThreads);
    int removeThreads(int nThreads);
    int threadsCount();
    int payload();
    int idleThreads();

    bool canExit();

protected:
    QMutex m_mutex_protect;

    QVector<CCE_TaskEngine_WorkingThread *> m_vec_workingThreads;
    QVector<QThread *> m_vec_InternalworkingThreads;

    std::list< CCE_TaskEngine_TaskBase * > m_list_tasks;
    int m_nExistingThreads;
    int m_nThread = 2;

protected:
    CCE_TaskEngine_TaskBase* popTask(bool *bValid);

signals:
    void sig_start_work(CCE_TaskEngine_WorkingThread* taskThread);
    void sig_stop_work(CCE_TaskEngine_WorkingThread* taskThread);
public slots:
    void slot_finished_task(CCE_TaskEngine_WorkingThread* taskThread);
    void slot_pushTask(CCE_TaskEngine_TaskBase* task, bool bFire = true);
};
#endif
