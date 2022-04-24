/*********************************************************************************************************
** This file is part of the CCE_CommunicatEngine module of the CCE Toolkit.
*********************************************************************************************************/

/*!
\class CCEClusterProxy

\inmodule CCE_CommunicatEngine

\brief The CCEClusterProxy class proxy the behavior of the  communication library uses a synchronous or asynchronous method.

\code
    CCEEnginePackage pack(item->socketObject(), EPackageType::EPT_UDP);
    pack.setNetInfo(item->netInfo().ipAddr, item->netInfo().port);
    pack.setData(writeData);
    CCEEnginePackage recPack;
    CCEClusterProxy::syncSend(pack, recPack);
\endcode

\note:
CCECLusterProxy::asyncSend can't get the return result pass the callback function temporarily in the current design. if you want get return result,
maybe you can refer to class CCEPackageEvent and class CCEPackageDispatcher inmodule CCE_CommunicatEngine.
*/

#include "CCE_CommunicatEngine/CCEClusterProxy.h"
#include "CCE_CommunicatEngine/CCESocketLock.h"

#include "CCE_CommunicatEngine/CCECluster.h"
#include "CCE_Core/CCEAPIDef"

QMutex CCEClusterProxy::m_mutex_protect;
QMutex CCEClusterProxy::m_exclusive_protect;
QMap<QString, QUuid> CCEClusterProxy::m_hash_exclusiveHostName;

CCEClusterProxy::~CCEClusterProxy()
{
}

quint16 CCEClusterProxy::syncSend(const CCEEnginePackage& sendPack, CCEEnginePackage& recPack, int mesc/* = 1500*/,bool force/*=false*/)
{
    if (isItemExlusive(sendPack.hostName())) {
        qDebug() << QString("SyncSend====(%1)..is in Exclusive.").arg(sendPack.hostName());
        return CCEAPI::EResult::ER_InExclusiveMode;
    }
    if (!m_mutex_protect.try_lock()) {
        qDebug() << "Lock Failed.";
        return CCEAPI::EResult::ER_SyncSendLockFail;
    }
    CCESyncWaiter syncLocker(sendPack);
    gCluster->slot_SendData(sendPack.socketObj(), sendPack);
    if (syncLocker.syncLock(mesc, force))
    {
        m_mutex_protect.unlock();
        recPack = syncLocker.syncRecPackage();
        return CCEAPI::EResult::ER_Success;
    }
    else
    {
        m_mutex_protect.unlock();
        qDebug() << "Timed out while waiting on syncSend(). hostName:" << sendPack.hostName();
        return CCEAPI::EResult::ER_SyncSendTimeOut;
    }
}

quint16 CCEClusterProxy::exclusiveSyncSend(const CCEEnginePackage & sendPack, CCEEnginePackage & recPack, int mesc)
{
    if (isItemExlusive(sendPack.hostName())) {
        if (sendPack.exclusiveKey() != m_hash_exclusiveHostName[sendPack.hostName()]) {
            qDebug() << QString("%1 Exclusive key not matched.").arg(sendPack.hostName());
            return CCEAPI::EResult::ER_ExclusiveKeyNotMatch;
        }
    }
    CCESyncWaiter syncLocker(sendPack);
    gCluster->slot_SendData(sendPack.socketObj(), sendPack);
    if (syncLocker.syncLockEventLoop(mesc))
    {
        recPack = syncLocker.syncRecPackage();
        return CCEAPI::EResult::ER_Success;
    }
    else
    {
        qDebug() << "Timed out while waiting on syncSend(). hostName:" << sendPack.hostName();
        return CCEAPI::EResult::ER_SyncSendTimeOut;
    }
}

bool CCEClusterProxy::asyncSend(const CCEEnginePackage& sendPack)
{
    if (isItemExlusive(sendPack.hostName())) {
        qDebug() << QString("SyncSend====(%1)..is in Exclusive.").arg(sendPack.hostName());
        return false;
    }
    if (sendPack.isEmpty() || nullptr == sendPack.socketObj())
        return false;
    return gCluster->slot_SendData(sendPack.socketObj(), sendPack);
}

QUuid CCEClusterProxy::setItemExlusive(QString hostName, bool enable)
{
    m_exclusive_protect.lock();
    QUuid id;
    if (enable) {
        id = QUuid::createUuid();
        m_hash_exclusiveHostName[hostName] = id;
    }
    else{
        id = QUuid();
        m_hash_exclusiveHostName.remove(hostName);
    }
    m_exclusive_protect.unlock();
    return id;
}

bool CCEClusterProxy::isItemExlusive(QString hostName)
{
    QMutexLocker m_locker(&m_exclusive_protect);
    return m_hash_exclusiveHostName.contains(hostName);
}
