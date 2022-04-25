#include "CCE_CommunicatEngine/CCETestDataPackage.h"

CCEAbstractTestDataPackage::CCEAbstractTestDataPackage()
{

}

CCEAbstractTestDataPackage::CCEAbstractTestDataPackage(const QByteArray &data)
    : CCEPackage(data)
{

}

CCEAbstractTestDataPackage::~CCEAbstractTestDataPackage()
{

}

quint16 CCETestDataPackage_ReadTDCurTemperature::getCurTemperature() const
{
   DO_GETUSHORTRESULT(getContent());
}

quint16 CCETestDataPackage_ReadTICurTemperature::getCurTemperature() const
{
    DO_GETUSHORTRESULT(getContent());
}

quint32 CCETestDataPackage_ReadCurTestRunTime::getValue() const
{
    quint32 value = 0;
    QByteArray buffer = getContent();
    if (buffer.size() < 4) {
        return value;
    }
    memcpy(&value, buffer.constData(), 4);
    return CCEUIHelper::bigLittleSwap32(value);
}

quint16 CCETestDataPackage_ReadCOLUMNTemperature::getCurTemperature() const
{
    DO_GETUSHORTRESULT(getContent());
}

quint16 CCETestDataPackage_ReadMicroPIDValue::getValue() const
{
    DO_GETUSHORTRESULT(getContent());
}

STestData CCETestDataPackage_ReadAllInfo::getInfo() const
{
    STestData info;
    QByteArray data = getContent();
    info.setRawData(data);
    return info;
}
