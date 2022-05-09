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
    DO_GETUINTRESULT(getContent());
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
    info.bigLittleSwap();
    return info;
}

CCETestDataPackage_ReportAllInfo::CCETestDataPackage_ReportAllInfo(const quint8 &ret):
    m_retValue(ret)
{

}

STestData CCETestDataPackage_ReportAllInfo::getInfo() const
{
    STestData info;
    QByteArray data = getContent();
    info.setRawData(data);
    info.bigLittleSwap();
    return info;
}
