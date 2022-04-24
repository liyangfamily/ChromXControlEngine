#include "CCE_ChromXItem/CCELEDPanelUnitDevice.h"
#include "CCEAbstractModule_p.h"
#include <CCE_CommunicatEngine/CCEClusterProxy>

class CCELEDPanelUnitDevicePrivate : public CCEAbstractModulePrivate
{
    Q_DECLARE_PUBLIC(CCELEDPanelUnitDevice)
public:
    CCELEDPanelUnitDevicePrivate(){}
    ~CCELEDPanelUnitDevicePrivate(){}

    SLEDPanelUnit m_LEDPanelUnit;
};

CCELEDPanelUnitDevice::CCELEDPanelUnitDevice(QObject *parent)
    : CCEAbstractModule{*new CCELEDPanelUnitDevicePrivate, parent}
{

}

CCELEDPanelUnitDevice::~CCELEDPanelUnitDevice()
{

}

quint16 CCELEDPanelUnitDevice::writeHardwareVersion(quint8 value, bool sync, int msec)
{
    CCELEDPanelUnitPackage_WriteHardwareVersion pack(value);
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

quint16 CCELEDPanelUnitDevice::readHardwareVersion(bool sync, int msec)
{
    CCELEDPanelUnitPackage_ReadHardwareVersion pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

quint8 CCELEDPanelUnitDevice::getHardwareVersion()
{
    Q_D(CCELEDPanelUnitDevice);
    return d->m_LEDPanelUnit.version;
}

void CCELEDPanelUnitDevice::registerCallBack()
{
    Q_D(CCELEDPanelUnitDevice);
    d->m_packageMgr.registerPackage(CCELEDPanelUnitPackage_WriteHardwareVersion(),
                                        std::bind(&CCELEDPanelUnitDevice::onParseWriteHardwareVersion,this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCELEDPanelUnitPackage_ReadHardwareVersion(),
                                        std::bind(&CCELEDPanelUnitDevice::onParseReadHardwareVersion,this,std::placeholders::_1));
}

quint16 CCELEDPanelUnitDevice::onParseWriteHardwareVersion(const QByteArray &data)
{
    CCELEDPanelUnitPackage_WriteHardwareVersion pack(data);
    DO_RETOPERATIONRESULT(pack);
}

quint16 CCELEDPanelUnitDevice::onParseReadHardwareVersion(const QByteArray &data)
{
    Q_D(CCELEDPanelUnitDevice);
    CCELEDPanelUnitPackage_ReadHardwareVersion pack(data);
    if(pack.isValid()){
        d->m_LEDPanelUnit.version = pack.getVersion();
        qDebug()<<"Got it! hard version:"<<d->m_LEDPanelUnit.version;
    }
    return CCEAPI::EResult::ER_Success;
}
