#include "CCE_ChromXItem/CCEMainCtrlDevice.h"
#include "CCEAbstractModule_p.h"
#include <CCE_CommunicatEngine/CCEClusterProxy>

class CCEMainCtrlDevicePrivate : public CCEAbstractModulePrivate
{
    Q_DECLARE_PUBLIC(CCEMainCtrlDevice)
public:
    CCEMainCtrlDevicePrivate(){}
    ~CCEMainCtrlDevicePrivate(){}

    SMainCtrl m_mainCtrlData;
};


CCEMainCtrlDevice::CCEMainCtrlDevice(QObject *parent):
    CCEAbstractModule{*new CCEMainCtrlDevicePrivate, parent}
{
}

CCEMainCtrlDevice::~CCEMainCtrlDevice()
{
}

quint16 CCEMainCtrlDevice::writeHardwareVersion(quint8 value, bool sync, int msec)
{
    CCEMainCtrlPackage_WriteHardwareVersion pack(value);
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

quint16 CCEMainCtrlDevice::readHardwareVersion(bool sync, int msec)
{
    CCEMainCtrlPackage_ReadHardwareVersion pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

quint8 CCEMainCtrlDevice::getHardwareVersion()
{
    Q_D(CCEMainCtrlDevice);
    return d->m_mainCtrlData.hardWareVersion;
}

quint16 CCEMainCtrlDevice::writeARMSoftwareVersion(quint8 value, bool sync, int msec)
{
    CCEMainCtrlPackage_WriteARMSoftwareVersion pack(value);
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

quint16 CCEMainCtrlDevice::readARMSoftwareVersion(bool sync, int msec)
{
    CCEMainCtrlPackage_ReadARMSoftwareVersion pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

quint8 CCEMainCtrlDevice::getARMSoftwareVersion()
{
    Q_D(CCEMainCtrlDevice);
    return d->m_mainCtrlData.armSoftwareVersion;
}

quint16 CCEMainCtrlDevice::writeStartSelfTest(quint8 value, bool sync, int msec)
{
    CCEMainCtrlPackage_WriteStartSelfTest pack(value);
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

quint16 CCEMainCtrlDevice::readStartSelfTest(bool sync, int msec)
{
    CCEMainCtrlPackage_ReadStartSelfTest pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

quint8 CCEMainCtrlDevice::getStartSelfTest()
{
    Q_D(CCEMainCtrlDevice);
    return d->m_mainCtrlData.selfTestStatus;
}

void CCEMainCtrlDevice::registerCallBack()
{
    Q_D(CCEMainCtrlDevice);
    d->m_packageMgr.registerPackage(CCEMainCtrlPackage_ReadHardwareVersion(),
                                        std::bind(&CCEMainCtrlDevice::onParseReadHardwareVersion,this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCEMainCtrlPackage_WriteHardwareVersion(),
                                        std::bind(&CCEMainCtrlDevice::onParseWriteHardwareVersion,this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCEMainCtrlPackage_ReadARMSoftwareVersion(),
                                        std::bind(&CCEMainCtrlDevice::onParseReadARMSoftwareVersion,this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCEMainCtrlPackage_WriteARMSoftwareVersion(),
                                        std::bind(&CCEMainCtrlDevice::onParseWriteARMSoftwareVersion,this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCEMainCtrlPackage_ReadStartSelfTest(),
                                        std::bind(&CCEMainCtrlDevice::onParseReadStartSelfTest,this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCEMainCtrlPackage_WriteStartSelfTest(),
                                        std::bind(&CCEMainCtrlDevice::onParseWriteStartSelfTest,this,std::placeholders::_1));
}

quint16 CCEMainCtrlDevice::onParseReadHardwareVersion(const QByteArray &data)
{
    Q_D(CCEMainCtrlDevice);
    CCEMainCtrlPackage_ReadHardwareVersion pack(data);
    quint16 ret = pack.isValid();
    if(ret==CCEAPI::EResult::ER_Success){
        d->m_mainCtrlData.hardWareVersion = pack.getVersion();
        qDebug()<<"Got it! hard version:"<<d->m_mainCtrlData.hardWareVersion;
    }
    return ret;
}

quint16 CCEMainCtrlDevice::onParseWriteHardwareVersion(const QByteArray &data)
{
    CCEMainCtrlPackage_WriteHardwareVersion pack(data);
    DO_RETOPERATIONRESULT(pack);
}

quint16 CCEMainCtrlDevice::onParseReadARMSoftwareVersion(const QByteArray &data)
{
    Q_D(CCEMainCtrlDevice);
    CCEMainCtrlPackage_ReadARMSoftwareVersion pack(data);
    quint16 ret = pack.isValid();
    if(ret==CCEAPI::EResult::ER_Success){
        d->m_mainCtrlData.armSoftwareVersion = pack.getVersion();
        qDebug()<<"Got it! arm version:"<<d->m_mainCtrlData.armSoftwareVersion;
    }
    return ret;
}

quint16 CCEMainCtrlDevice::onParseWriteARMSoftwareVersion(const QByteArray &data)
{
    CCEMainCtrlPackage_WriteARMSoftwareVersion pack(data);
    DO_RETOPERATIONRESULT(pack);
}

quint16 CCEMainCtrlDevice::onParseReadStartSelfTest(const QByteArray &data)
{
    Q_D(CCEMainCtrlDevice);
    CCEMainCtrlPackage_ReadStartSelfTest pack(data);
    quint16 ret = pack.isValid();
    if(ret==CCEAPI::EResult::ER_Success){
        d->m_mainCtrlData.selfTestStatus = pack.getStatus();
        qDebug()<<"Got it! self test status:"<<d->m_mainCtrlData.selfTestStatus;
    }
    return ret;
}

quint16 CCEMainCtrlDevice::onParseWriteStartSelfTest(const QByteArray &data)
{
    CCEMainCtrlPackage_WriteStartSelfTest pack(data);
    DO_RETOPERATIONRESULT(pack);
}
