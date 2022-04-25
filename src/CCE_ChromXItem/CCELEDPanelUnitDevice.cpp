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

quint16 CCELEDPanelUnitDevice::readAllPressureSensor(bool sync, int msec)
{
    CCELEDPanelUnitPackage_ReadAllPressureSensor pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

quint16 CCELEDPanelUnitDevice::getCarrierGasPressure()
{
    Q_D(CCELEDPanelUnitDevice);
    return d->m_LEDPanelUnit.pressureSensor.carrierGasPressure;
}

quint16 CCELEDPanelUnitDevice::getSamplingPumpPressure()
{
    Q_D(CCELEDPanelUnitDevice);
    return d->m_LEDPanelUnit.pressureSensor.samplingPumpPressure;
}

quint16 CCELEDPanelUnitDevice::getAuxGasPressure()
{
    Q_D(CCELEDPanelUnitDevice);
    return d->m_LEDPanelUnit.pressureSensor.auxGasPressure;
}

quint16 CCELEDPanelUnitDevice::writeAllLight(SLEDPanelLight value, bool sync, int msec)
{
    CCELEDPanelUnitPackage_WriteAllLight pack(value);
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

quint16 CCELEDPanelUnitDevice::readAllLight(bool sync, int msec)
{
    CCELEDPanelUnitPackage_ReadAllLight pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

SLEDPanelLight CCELEDPanelUnitDevice::getAllLight()
{
    Q_D(CCELEDPanelUnitDevice);
    return d->m_LEDPanelUnit.panelLight;
}

quint16 CCELEDPanelUnitDevice::readAllEvnSensor(bool sync, int msec)
{
    CCELEDPanelUnitPackage_ReadAllEvnSensor pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

quint16 CCELEDPanelUnitDevice::getEnvTemperature()
{
    Q_D(CCELEDPanelUnitDevice);
    return d->m_LEDPanelUnit.envSensor.envTemperature;
}

quint16 CCELEDPanelUnitDevice::getEnvHumidity()
{
    Q_D(CCELEDPanelUnitDevice);
    return d->m_LEDPanelUnit.envSensor.envHumidity;
}

quint16 CCELEDPanelUnitDevice::getEnvPressure()
{
    Q_D(CCELEDPanelUnitDevice);
    return d->m_LEDPanelUnit.envSensor.envPressure;
}

void CCELEDPanelUnitDevice::registerCallBack()
{
    Q_D(CCELEDPanelUnitDevice);
    d->m_packageMgr.registerPackage(CCELEDPanelUnitPackage_WriteHardwareVersion(),
                                        std::bind(&CCELEDPanelUnitDevice::onParseWriteHardwareVersion,this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCELEDPanelUnitPackage_ReadHardwareVersion(),
                                        std::bind(&CCELEDPanelUnitDevice::onParseReadHardwareVersion,this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCELEDPanelUnitPackage_ReadAllPressureSensor(),
                                        std::bind(&CCELEDPanelUnitDevice::onParseReadAllPressureSensor,this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCELEDPanelUnitPackage_WriteAllLight(),
                                        std::bind(&CCELEDPanelUnitDevice::onParseWriteAllLight,this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCELEDPanelUnitPackage_ReadAllLight(),
                                        std::bind(&CCELEDPanelUnitDevice::onParseReadAllLight,this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCELEDPanelUnitPackage_ReadAllEvnSensor(),
                                        std::bind(&CCELEDPanelUnitDevice::onParseAllEvnSensor,this,std::placeholders::_1));
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
    quint16 ret = pack.isValid();
    if(ret==CCEAPI::EResult::ER_Success){
        d->m_LEDPanelUnit.version = pack.getVersion();
        qDebug()<<"Got it! hard version:"<<d->m_LEDPanelUnit.version;
    }
    return ret;
}

quint16 CCELEDPanelUnitDevice::onParseReadAllPressureSensor(const QByteArray &data)
{
    Q_D(CCELEDPanelUnitDevice);
    CCELEDPanelUnitPackage_ReadAllPressureSensor pack(data);
    quint16 ret = pack.isValid();
    if(ret==CCEAPI::EResult::ER_Success){
        d->m_LEDPanelUnit.pressureSensor.carrierGasPressure = pack.getCarrierGasPressure();
        d->m_LEDPanelUnit.pressureSensor.samplingPumpPressure = pack.getSamplingPumpPressure();
        d->m_LEDPanelUnit.pressureSensor.auxGasPressure = pack.getAuxGasPressure();
        qDebug()<<QString("Got it! carrierGasPressure:%1,samplingPumpPressure:%2,auxGasPressure:%3.")\
                  .arg(d->m_LEDPanelUnit.pressureSensor.carrierGasPressure)\
                  .arg(d->m_LEDPanelUnit.pressureSensor.samplingPumpPressure)\
                  .arg(d->m_LEDPanelUnit.pressureSensor.auxGasPressure);
    }
    return ret;
}

quint16 CCELEDPanelUnitDevice::onParseWriteAllLight(const QByteArray &data)
{
    CCELEDPanelUnitPackage_WriteAllLight pack(data);
    DO_RETOPERATIONRESULT(pack);
}

quint16 CCELEDPanelUnitDevice::onParseReadAllLight(const QByteArray &data)
{
    Q_D(CCELEDPanelUnitDevice);
    CCELEDPanelUnitPackage_ReadAllLight pack(data);
    quint16 ret = pack.isValid();
    if(ret==CCEAPI::EResult::ER_Success){
        d->m_LEDPanelUnit.panelLight = pack.getValue();
        qDebug()<<QString("Got it! progress:%1,light1:%2,light2:%3,light3:%4,light4:%5,light5:%6.") \
                  .arg(d->m_LEDPanelUnit.panelLight.progress)\
                  .arg(d->m_LEDPanelUnit.panelLight.light1)\
                  .arg(d->m_LEDPanelUnit.panelLight.light2)\
                  .arg(d->m_LEDPanelUnit.panelLight.light3)\
                  .arg(d->m_LEDPanelUnit.panelLight.light4)\
                  .arg(d->m_LEDPanelUnit.panelLight.light5);
    }
    return ret;
}

quint16 CCELEDPanelUnitDevice::onParseAllEvnSensor(const QByteArray &data)
{
    Q_D(CCELEDPanelUnitDevice);
    CCELEDPanelUnitPackage_ReadAllEvnSensor pack(data);
    quint16 ret = pack.isValid();
    if(ret==CCEAPI::EResult::ER_Success){
        d->m_LEDPanelUnit.envSensor.envTemperature = pack.getEnvTemperature();
        d->m_LEDPanelUnit.envSensor.envHumidity = pack.getEnvHumidity();
        d->m_LEDPanelUnit.envSensor.envPressure = pack.getEnvPressure();
        qDebug()<<QString("Got it! envTemperature:%1,envHumidity:%2,envPressure:%3.") \
                  .arg(d->m_LEDPanelUnit.envSensor.envTemperature)\
                  .arg(d->m_LEDPanelUnit.envSensor.envHumidity)\
                  .arg(d->m_LEDPanelUnit.envSensor.envPressure);
    }
    return ret;
}
