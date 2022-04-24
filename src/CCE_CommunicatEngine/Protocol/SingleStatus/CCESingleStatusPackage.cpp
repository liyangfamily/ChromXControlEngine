#include "CCE_CommunicatEngine/CCESingleStatusPackage.h"

CCEAbstractSingleStatusPackage::CCEAbstractSingleStatusPackage()
{

}

CCEAbstractSingleStatusPackage::CCEAbstractSingleStatusPackage(const QByteArray &data)
    : CCEPackage(data)
{

}

CCEAbstractSingleStatusPackage::~CCEAbstractSingleStatusPackage()
{

}

quint16 CCESingleStatusPackage_ReadTDCurTemperature::getCurTemperature() const
{
   DO_GETUSHORTRESULT(getContent());
}

quint16 CCESingleStatusPackage_ReadTICurTemperature::getCurTemperature() const
{
    DO_GETUSHORTRESULT(getContent());
}

quint16 CCESingleStatusPackage_ReadCOLUMNTemperature::getCurTemperature() const
{
    DO_GETUSHORTRESULT(getContent());
}

quint16 CCESingleStatusPackage_ReadMicroPIDValue::getValue() const
{
    DO_GETUSHORTRESULT(getContent());
}

quint16 CCESingleStatusPackage_ReadEPCPressure::getValue() const
{
    DO_GETUSHORTRESULT(getContent());
}

SSingleStatus CCESingleStatusPackage_ReadAllInfo::getInfo() const
{
    SSingleStatus info;
    QByteArray data = getContent();
    info.setRawData(data);
    return info;
}
