/*********************************************************************************************************
** This file is part of the CCE_CommunicatEngine module of the CCE Toolkit.
*********************************************************************************************************/

#include "CCE_CommunicatEngine/CCESocketLock.h"
#include "CCE_CommunicatEngine/CCEPackageEvent.h"
#include "CCE_CommunicatEngine/CCEPackageDispatcher.h"
#include "CCE_CommunicatEngine/CCEPackage.h"
#include "CCE_CommunicatEngine/CCECluster.h"

#include <CCE_Core/CCESignalWaiter>

#ifdef Q_CC_MSVC
#ifdef QT_DEBUG
#pragma comment(lib,"CCE_Cored.lib")
#else
#pragma comment(lib,"CCE_Core.lib")
#endif
#endif
/*!
\class CCESyncWaiter

\inmodule CCE_CommunicatEngine

\brief The class is based on the synchronization lock of the communication library implemented by CCESignalWaiter.

\code
    CCEPackageInteCtrl_DetectInfo detectInfo;
    detectInfo.SetCmdTargetDevice(m_tagetDeviceType);
    detectInfo.build(0);
    QByteArray writeData = detectInfo.getDataToSend();

    SPackage pack(socketObj(), EPackageType::EPT_COM);
    QSerialPort* pSocket = qobject_cast<QSerialPort*>(socketObj());
    if (pSocket)
    {
        pack.setComName(pSocket->portName());
        pack.setData(writeData);
    }
    CCESyncWaiter locker(pack);
    qCluster->slot_SendData(socketObj(), pack);
    if(locker.syncLock(5000)) {
        Spackage recPack=locker.syncRecPackage();
    } else {
        QMessageBox::information(0, "MyObject", "Timed out while waiting on longProcessFinished()", QMessageBox::Ok);
    }
\endcode

\note:
CCESyncWaiter is not reentrant。
*/

CCESyncWaiter::CCESyncWaiter(CCEEnginePackage packInfo):
    m_socketObj(packInfo.socketObj()),m_syncPackage(packInfo)
{
    Q_ASSERT(m_socketObj);
    if (m_socketObj)
    {
        //connect(qCluster, &CCE_Cluster::sig_ParsingDataFrame, this, &CCESyncWaiter::slot_ParsingDataFrame);
        gDispatcher->registerTransitObject(this);
    }
}

CCESyncWaiter::~CCESyncWaiter()
{
    //qDebug() << "CCESyncWaiter unlocked.";
    gDispatcher->unregisterTransitObject(this);
}

bool CCESyncWaiter::syncLock(int msec /*= 3000*/, bool force/* = false*/)
{
    m_forceWait = force;
    m_syncRecPackage = CCEEnginePackage();
    CCESignalWaiter waiter(this, SIGNAL(sig_syncFinnish()));
    return waiter.wait(msec, force);
}

#include <QTimer>
bool CCESyncWaiter::syncLockEventLoop(int msec /*= 3000*/)
{
    QEventLoop loop;
    QTimer outTimer;
    outTimer.setSingleShot(true);
    connect(&outTimer, &QTimer::timeout, &loop, &QEventLoop::quit);
    connect(this, &CCESyncWaiter::sig_syncFinnish, &loop, &QEventLoop::quit);
    outTimer.start(msec); // 超时
    loop.exec();
    if(outTimer.isActive()){
        outTimer.stop();
        return true;
    }
    else{
        outTimer.stop();
        return false;
    }
}

CCEEnginePackage CCESyncWaiter::syncRecPackage()
{
    return m_syncRecPackage;
}

bool CCESyncWaiter::event(QEvent * e)
{
    if (e->type() == CCEPackageEvent::s_transitPackage_eventType)
    {
        CCEPackageEvent *tempE = static_cast<CCEPackageEvent*>(e);
        slot_ParsingDataFrame(tempE->package().socketObj(), tempE->package());
    }
    return QObject::event(e);
}

void CCESyncWaiter::slot_ParsingDataFrame(QObject *psource, CCEEnginePackage dataFrame)
{
    if (psource != m_socketObj)
        return;
//    if (dataFrame.hostName() != m_syncPackage.hostName())
//        return;
    CCEPackage syncPack(m_syncPackage.data());
    CCEPackage recPack(dataFrame.data());
    if (syncPack.getFrameType() == recPack.getFrameType() &&
        syncPack.getUnitAddr() == recPack.getUnitAddr() &&
        syncPack.getCtrlAddr() == recPack.getCtrlAddr())
    {
        if (!m_forceWait) {
            emit sig_syncFinnish();
        }
        m_syncRecPackage = dataFrame;
    }
}

/*********************************************************************************************************/

/*!
\class CCESocketExclusiveLock

\inmodule CCE_CommunicatEngine

\brief The class is based on the socket Exclusive lock of the communication library implemented by CCESignalWaiter.

CCESocketExclusiveLock::autolock():when it returns true, you can get the exclusive key.

\code
    CCESocketExclusiveLock locker(socketObj);
    if(locker.autoLock(5000)) {
        QUuid exclusiveKey=locker.exclusiveKey();
        for(int i=0;i<1000;++i)
        {
            SPackage tempPack(QByteArray());
            tempPack.setExclusiveKey(exclusiveKey);
            qCluster->slot_SendData(socketObj,tempPack);
        }
    } else {
        QMessageBox::information(0, "MyObject", "Timed out while waiting on longProcessFinished()", QMessageBox::Ok);
    }
\endcode

\note:
CCESocketExclusiveLock is not reentrant。
*/

CCESocketExclusiveLock::CCESocketExclusiveLock(QObject * socketObj):
    m_socketObj(socketObj)
{
    Q_ASSERT(m_socketObj);
    connect(gCluster, &CCECluster::sig_ExlusiveLocked, this, &CCESocketExclusiveLock::slot_TransThreadLocked, Qt::QueuedConnection);
}

CCESocketExclusiveLock::~CCESocketExclusiveLock()
{
    gCluster->slot_SetSocketExlusive(m_socketObj, false);
    //qDebug() << "CCEItemExclusiveLock unlocked.";
}

bool CCESocketExclusiveLock::autoLock(int msec)
{
    m_exclusiveUuid = QUuid();
    CCESignalWaiter waiter(this, SIGNAL(sig_locked()));
    //通知去锁
    gCluster->slot_SetSocketExlusive(m_socketObj, true);
    return waiter.wait(msec);
}

QUuid CCESocketExclusiveLock::exclusiveKey()
{
    return m_exclusiveUuid;
}

void CCESocketExclusiveLock::slot_TransThreadLocked(QObject * objSocket, bool bStatus, QUuid uuid)
{
    if (objSocket != m_socketObj)
    {
        return;
    }
    if (bStatus)
    {
        m_exclusiveUuid = uuid;
        emit sig_locked();
        qDebug() << "CCEItemExclusiveLock locked.";
    }
}


CCEItemExclusiveLock::CCEItemExclusiveLock(QString hostName) :
    m_hostName(hostName)
{
}

CCEItemExclusiveLock::~CCEItemExclusiveLock()
{
    CCEClusterProxy::setItemExlusive(m_hostName, false);
    //qDebug() << "CCEItemExclusiveLock unlocked.";
}

bool CCEItemExclusiveLock::autoLock()
{
    m_exclusiveUuid = QUuid();
    //通知去锁
    m_exclusiveUuid = CCEClusterProxy::setItemExlusive(m_hostName, true);
    return !m_exclusiveUuid.isNull();
}

QUuid CCEItemExclusiveLock::exclusiveKey()
{
    return m_exclusiveUuid;
}
