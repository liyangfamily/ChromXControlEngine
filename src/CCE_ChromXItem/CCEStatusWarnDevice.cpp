#include "CCE_ChromXItem/CCEStatusWarnDevice.h"
#include "CCEAbstractModule_p.h"
#include <CCE_CommunicatEngine/CCEClusterProxy>

class CCEStatusWarnDevicePrivate : public CCEAbstractModulePrivate
{
    Q_DECLARE_PUBLIC(CCEStatusWarnDevice)
public:
    CCEStatusWarnDevicePrivate(){}
    ~CCEStatusWarnDevicePrivate(){}

    SStatusWarn m_statusWarn;
};


CCEStatusWarnDevice::CCEStatusWarnDevice(QObject *parent)
    : CCEAbstractModule{*new CCEStatusWarnDevicePrivate,parent}
{

}

CCEStatusWarnDevice::~CCEStatusWarnDevice()
{

}

quint16 CCEStatusWarnDevice::readExistAbnormal(bool sync, int msec)
{
    CCEStatusWarnPackage_ReadExistAbnormal pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

quint8 CCEStatusWarnDevice::getExistAbnormal()
{
    Q_D(CCEStatusWarnDevice);
    return d->m_statusWarn.existAbnormal;
}

quint16 CCEStatusWarnDevice::readDeviceStatus(bool sync, int msec)
{
    CCEStatusWarnPackage_ReadDeviceStatus pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

quint8 CCEStatusWarnDevice::getDeviceStatus()
{
    Q_D(CCEStatusWarnDevice);
    return d->m_statusWarn.deviceStatus;
}

bool CCEStatusWarnDevice::testDeviceStatus(EDeviceStatus testStatus)
{
    Q_D(CCEStatusWarnDevice);
    return testStatus&d->m_statusWarn.deviceStatus;
}

quint16 CCEStatusWarnDevice::readDeviceSelfTestStatus(bool sync, int msec)
{
    CCEStatusWarnPackage_ReadDeviceSelfTestStatus pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

quint8 CCEStatusWarnDevice::getDeviceSelfTestStatus()
{
    Q_D(CCEStatusWarnDevice);
    return d->m_statusWarn.deviceSelfTestStatus;
}

quint16 CCEStatusWarnDevice::readDeviceTestComplete(bool sync, int msec)
{
    CCEStatusWarnPackage_ReadDeviceTestComplete pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

quint8 CCEStatusWarnDevice::getDeviceTestComplete()
{
    Q_D(CCEStatusWarnDevice);
    return d->m_statusWarn.deviceTestComplete;
}

void CCEStatusWarnDevice::registerCallBack()
{
    Q_D(CCEStatusWarnDevice);
    d->m_packageMgr.registerPackage(CCEStatusWarnPackage_ReadExistAbnormal(),
                                        std::bind(&CCEStatusWarnDevice::onParseReadExistAbnormal,this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCEStatusWarnPackage_ReadDeviceStatus(),
                                        std::bind(&CCEStatusWarnDevice::onParseReadDeviceStatus,this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCEStatusWarnPackage_ReadDeviceSelfTestStatus(),
                                        std::bind(&CCEStatusWarnDevice::onParseReadDeviceSelfTestStatus,this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCEStatusWarnPackage_ReadDeviceTestComplete(),
                                        std::bind(&CCEStatusWarnDevice::onParseReadDeviceTestComplete,this,std::placeholders::_1));
}

quint16 CCEStatusWarnDevice::onParseReadExistAbnormal(const QByteArray &data)
{
    Q_D(CCEStatusWarnDevice);
    CCEStatusWarnPackage_ReadExistAbnormal pack(data);
    quint16 ret = pack.isValid();
    if(ret==CCEAPI::EResult::ER_Success){
        d->m_statusWarn.existAbnormal = pack.getValue();
        qDebug()<<"Got it! existAbnormal:"<<d->m_statusWarn.existAbnormal;
    }
    return ret;
}

quint16 CCEStatusWarnDevice::onParseReadDeviceStatus(const QByteArray &data)
{
    Q_D(CCEStatusWarnDevice);
    CCEStatusWarnPackage_ReadDeviceStatus pack(data);
    quint16 ret = pack.isValid();
    if(ret==CCEAPI::EResult::ER_Success){
        d->m_statusWarn.deviceStatus = pack.getValue();
        qDebug()<<"Got it! deviceStatus:"<<d->m_statusWarn.deviceStatus;
    }
    return ret;
}

quint16 CCEStatusWarnDevice::onParseReadDeviceSelfTestStatus(const QByteArray &data)
{
    Q_D(CCEStatusWarnDevice);
    CCEStatusWarnPackage_ReadDeviceSelfTestStatus pack(data);
    quint16 ret = pack.isValid();
    if(ret==CCEAPI::EResult::ER_Success){
        d->m_statusWarn.deviceSelfTestStatus = pack.getValue();
        qDebug()<<"Got it! deviceSelfTestStatus:"<<d->m_statusWarn.deviceSelfTestStatus;
    }
    return ret;
}

quint16 CCEStatusWarnDevice::onParseReadDeviceTestComplete(const QByteArray &data)
{
    Q_D(CCEStatusWarnDevice);
    CCEStatusWarnPackage_ReadDeviceTestComplete pack(data);
    quint16 ret = pack.isValid();
    if(ret==CCEAPI::EResult::ER_Success){
        d->m_statusWarn.deviceTestComplete = pack.getValue();
        qDebug()<<"Got it! deviceTestComplete:"<<d->m_statusWarn.deviceTestComplete;
    }
    return ret;
}
