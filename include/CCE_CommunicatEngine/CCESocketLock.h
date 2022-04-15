/*********************************************************************************************************
** This file is part of the CCE_CommunicatEngine module of the CCE Toolkit.
*********************************************************************************************************/
#ifndef CVTE_H_CCESOCKETLOCK
#define CVTE_H_CCESOCKETLOCK
#pragma once

#include <CCE_CommunicatEngine/CCEEnginePackage>
#include <CCE_CommunicatEngine/CCEClusterProxy>

#include <QObject>
#include <QMutex>
#include <QUuid>
#include <QEvent>


class CCE_COMMUNICATENGINE_EXPORT CCESyncWaiter : public QObject
{
    Q_OBJECT

public:
    CCESyncWaiter(CCEEnginePackage packInfo);
    ~CCESyncWaiter();
    bool syncLock(int msec = 1500, bool force = false);
    bool syncLockEventLoop(int msec = 1500);
    CCEEnginePackage syncRecPackage();
protected:
    bool event(QEvent* e) override;
signals:
    void sig_syncFinnish();

public slots:
    void slot_ParsingDataFrame(QObject *psource, CCEEnginePackage dataFrame);
private:
    QObject* m_socketObj = nullptr;
    bool m_forceWait = false;
    CCEEnginePackage m_syncPackage;
    CCEEnginePackage m_syncRecPackage;
};

class CCE_COMMUNICATENGINE_EXPORT CCESocketExclusiveLock : public QObject
{
    Q_OBJECT

public:
    CCESocketExclusiveLock(QObject *socketObj);
    ~CCESocketExclusiveLock();
    bool autoLock(int msec = 1000);
    QUuid exclusiveKey();
signals:
    void sig_locked();
public slots:
    void slot_TransThreadLocked(QObject * objSocket, bool bStatus, QUuid uuid);
private:
    QObject * m_socketObj = nullptr;
    QMutex m_exclusiveLock;

    QUuid m_exclusiveUuid;
};

class CCE_COMMUNICATENGINE_EXPORT CCEItemExclusiveLock : public QObject
{
    Q_OBJECT

public:
    CCEItemExclusiveLock(QString hostName);
    ~CCEItemExclusiveLock();
    bool autoLock();
    QUuid exclusiveKey();

private:
    QString m_hostName;

    QUuid m_exclusiveUuid;
};
#endif
