#include "CCE_CommunicatEngine/CCELEDPanelUnitPackage.h"

CCEAbstractLEDPanelUnitPackage::CCEAbstractLEDPanelUnitPackage()
{

}

CCEAbstractLEDPanelUnitPackage::CCEAbstractLEDPanelUnitPackage(const QByteArray &data):
    CCEPackage(data)
{

}

CCEAbstractLEDPanelUnitPackage::~CCEAbstractLEDPanelUnitPackage()
{

}


quint8 CCELEDPanelUnitPackage_ReadHardwareVersion::getVersion() const
{
    DO_GETCHARRESULT(getContent());
}

CCELEDPanelUnitPackage_WriteHardwareVersion::CCELEDPanelUnitPackage_WriteHardwareVersion(quint8 ver):
    m_version(ver)
{

}

quint16 CCELEDPanelUnitPackage_ReadAllPressureSensor::getCarrierGasPressure() const
{
    QByteArray buffer = getContent();
    if (buffer.size() < sizeof(SPressureSensor)) {
        return 0;
    }
    const SPressureSensor* test = (SPressureSensor*)buffer.constData();
    return CCEUIHelper::bigLittleSwap16(test->carrierGasPressure);
}

quint16 CCELEDPanelUnitPackage_ReadAllPressureSensor::getSamplingPumpPressure() const
{
    QByteArray buffer = getContent();
    if (buffer.size() < sizeof(SPressureSensor)) {
        return 0;
    }
    const SPressureSensor* test = (SPressureSensor*)buffer.constData();
    return CCEUIHelper::bigLittleSwap16(test->samplingPumpPressure);
}

quint16 CCELEDPanelUnitPackage_ReadAllPressureSensor::getAuxGasPressure() const
{
    QByteArray buffer = getContent();
    if (buffer.size() < sizeof(SPressureSensor)) {
        return 0;
    }
    const SPressureSensor* test = (SPressureSensor*)buffer.constData();
    return CCEUIHelper::bigLittleSwap16(test->auxGasPressure);
}

quint16 CCELEDPanelUnitPackage_ReadAllEvnSensor::getEnvTemperature() const
{
    QByteArray buffer = getContent();
    if (buffer.size() < sizeof(SEnvSensor)) {
        return 0;
    }
    const SEnvSensor* test = (SEnvSensor*)buffer.constData();
    return CCEUIHelper::bigLittleSwap16(test->envTemperature);
}

quint16 CCELEDPanelUnitPackage_ReadAllEvnSensor::getEnvHumidity() const
{
    QByteArray buffer = getContent();
    if (buffer.size() < sizeof(SEnvSensor)) {
        return 0;
    }
    const SEnvSensor* test = (SEnvSensor*)buffer.constData();
    return CCEUIHelper::bigLittleSwap16(test->envHumidity);
}

quint16 CCELEDPanelUnitPackage_ReadAllEvnSensor::getEnvPressure() const
{
    QByteArray buffer = getContent();
    if (buffer.size() < sizeof(SEnvSensor)) {
        return 0;
    }
    const SEnvSensor* test = (SEnvSensor*)buffer.constData();
    return CCEUIHelper::bigLittleSwap16(test->envPressure);
}

SLEDPanelLight CCELEDPanelUnitPackage_ReadAllLight::getValue() const
{
    SLEDPanelLight light;
    QByteArray buffer = getContent();
    if (buffer.size() < sizeof(SLEDPanelLight)) {
        return light;
    }
    memcpy(&light,buffer.data(),sizeof(SLEDPanelLight));
    return light;
}

CCELEDPanelUnitPackage_WriteAllLight::CCELEDPanelUnitPackage_WriteAllLight(SLEDPanelLight light):
    m_light(light)
{

}
