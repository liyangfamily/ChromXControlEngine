/*********************************************************************************************************
** This file is part of the CCE_CommunicatEngine module of the CCE Toolkit.
*********************************************************************************************************/
#ifndef CVTE_H_CCECLUSTERPROXY
#define CVTE_H_CCECLUSTERPROXY
#pragma once

#include <CCE_CommunicatEngine/CCECommunicatEngineGlobal>
#include <CCE_CommunicatEngine/CCEEnginePackage>

#include <QMutex>
#include <QMap>
#include <QString>
#include <QUuid>

class CCE_COMMUNICATENGINE_EXPORT CCEClusterProxy: public QObject
{
    friend class CCEItemExclusiveLock;
public:
    ~CCEClusterProxy();

    static quint16 syncSend(const CCEEnginePackage& sendPack, CCEEnginePackage& recPack, int mesc = CCE_Defalut_SyncTimeout, bool force = false);
    static quint16 exclusiveSyncSend(const CCEEnginePackage& sendPack, CCEEnginePackage& recPack, int mesc = CCE_Defalut_SyncTimeout);
    static bool asyncSend(const CCEEnginePackage& sendPack);

    static bool isItemExlusive(QString hostName);
protected:
    static QUuid setItemExlusive(QString hostName, bool enable);
private:
    static QMutex m_mutex_protect;
    static QMutex m_exclusive_protect;
    static QMap<QString, QUuid> m_hash_exclusiveHostName;

};
#endif
