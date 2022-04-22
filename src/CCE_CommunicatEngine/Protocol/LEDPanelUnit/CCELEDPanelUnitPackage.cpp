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
    QByteArray buffer = getContent();
    if (buffer.size() < 1) {
        return 0;
    }
    return buffer.front();
}

CCELEDPanelUnitPackage_WriteHardwareVersion::CCELEDPanelUnitPackage_WriteHardwareVersion(quint8 ver):
    m_version(ver)
{

}

quint16 CCELEDPanelUnitPackage_ReadAllLEDPanelUnit::getCarrierGasPressure() const
{
    quint16 value = 0;
    QByteArray buffer = getContent();
    if (buffer.size() < m_dataLength) {
        return value;
    }
    memcpy(&value, buffer.constData(), 2);
    return value;
}

quint16 CCELEDPanelUnitPackage_ReadAllLEDPanelUnit::getSamplingPumpPressure() const
{
    quint32 value = 0;
    QByteArray buffer = getContent();
    if (buffer.size() < m_dataLength) {
        return value;
    }
    memcpy(&value, buffer.constData()+2, 2);
    return value;
}

quint16 CCELEDPanelUnitPackage_ReadAllLEDPanelUnit::getAuxGasPressure() const
{
    quint32 value = 0;
    QByteArray buffer = getContent();
    if (buffer.size() < m_dataLength) {
        return value;
    }
    memcpy(&value, buffer.constData()+4, 2);
    return value;
}
