#ifndef CVTE_H_CCEENGINEPACKAGE
#define CVTE_H_CCEENGINEPACKAGE
#pragma once

#include <CCE_CommunicatEngine/CCECommunicatEngineGlobal>
#include "CCE_CommunicatEngine/CCECommunicatEngineDef.h"

#include <QByteArray>
#include <QMetaType>
#include <QObject>
#include <QVariant>
#include <QVector>
#include <QUuid>

enum EPackageRole
{
    EPR_NetAddress = 0,
    EPR_NetPort,
    EPR_COMName,
    //
};

#define DO_BUILDPACKAGE_ASYNC(detectInfo,data) \
    CCEEnginePackage enginePack;\
    enginePack.convertFrom(detectInfo);\
    enginePack.setData(data);\
    return CCEClusterProxy::asyncSend(enginePack);\

class SPackagePrivate;
class CCE_COMMUNICATENGINE_EXPORT CCEEnginePackage
{
public:
    CCEEnginePackage();
    CCEEnginePackage(QObject*, ECommunicatType, EPackageFromType = EPackageFromType::EPFT_Send);
    CCEEnginePackage(const CCEEnginePackage&);
    ~CCEEnginePackage();

    ECommunicatType type() const;
    void setType(ECommunicatType value);

    EPackageFromType fromType() const;
    void setFromType(EPackageFromType value);

    QObject* socketObj() const;
    void setSocketObj(QObject *value);

    QUuid exclusiveKey() const;
    void setExClusiveKey(QUuid);

    QByteArray data() const;
    void setData(const QByteArray&);

    QString hostAddress() const;
    void setHostAddres(const QString&);

    quint16 hostPort() const;
    void setHostPort(const quint16&);

    void setNetInfo(const QString&, const quint16&);

    void setComName(QString comName);
    QString comName() const;

    QString hostName() const;

    bool isEmpty() const;

    static QString genHostName(const QString&, const quint16&);
    static QString genHostName(QString comName);

    //从探卡信息中获取目标socket等信息
    bool initByDetectInfo(QObject* socket);
    /*QVariant exData(int role) const;
    void setExData(int role, const QVariant &value);*/

    CCEEnginePackage& operator=(const CCEEnginePackage& other);

private:
    ECommunicatType m_packType = ECommunicatType::ECT_NULL;
    EPackageFromType m_fromType = EPackageFromType::EPFT_NULL;

    QObject* m_socketObj = 0;
    QByteArray m_dataArray;
    //NET
    QString m_hostAddress;
    quint16 m_hostPort = 0;
    //COM
    QString m_comName;

    //独占模式金钥匙
    QUuid m_exclusiveKey;
};
Q_DECLARE_METATYPE(CCEEnginePackage);
#endif
