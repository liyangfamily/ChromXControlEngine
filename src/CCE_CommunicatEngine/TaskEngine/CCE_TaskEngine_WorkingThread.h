#ifndef CVTE_H_CCE_TASKENGINE_WORKINGTHREAD
#define CVTE_H_CCE_TASKENGINE_WORKINGTHREAD
#pragma once
#include <QObject>

class CCE_TaskEngine;
class CCE_TaskEngine_WorkingThread :public QObject
{
    Q_OBJECT
public:
    explicit CCE_TaskEngine_WorkingThread(CCE_TaskEngine * taskEngine, QObject *parent = 0);
    ~CCE_TaskEngine_WorkingThread();
    bool m_bBusy;

protected:
    CCE_TaskEngine * m_taskEngine;
    bool m_bRuning;

signals:
    void sig_taskFinished(CCE_TaskEngine_WorkingThread* taskThread);
public slots:
    void slot_SetStopMark(CCE_TaskEngine_WorkingThread* taskThread);
    void slot_FetchNewTask(CCE_TaskEngine_WorkingThread* taskThread);

};
#endif
