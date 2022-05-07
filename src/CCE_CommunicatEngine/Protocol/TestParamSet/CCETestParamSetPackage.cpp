#include "CCE_CommunicatEngine/CCETestParamSetPackage.h"

CCEAbstractTestParamSetPackage::CCEAbstractTestParamSetPackage()
{

}

CCEAbstractTestParamSetPackage::CCEAbstractTestParamSetPackage(const QByteArray &data)
    : CCEPackage(data)
{

}

CCEAbstractTestParamSetPackage::~CCEAbstractTestParamSetPackage()
{

}

SPIDAll CCETestParamSetPackage_ReadAllPID::getValue() const
{
    SPIDAll PIDAll;
    QByteArray buffer = getContent();
    if (buffer.size() < sizeof(SPIDAll)) {
        return PIDAll;
    }
    memcpy(&PIDAll,buffer.data(),sizeof(SPIDAll));
    PIDAll.bigLittleSwap();
    return PIDAll;
}

CCETestParamSetPackage_WriteAllPID::CCETestParamSetPackage_WriteAllPID(const SPIDAll &PIDAll):
    m_PIDAll(PIDAll)
{
    m_PIDAll.bigLittleSwap();
}

CCETestParamSetPackage_WriteRunParam::CCETestParamSetPackage_WriteRunParam(quint16 offsetPos, const QByteArray &writeData):
    m_writeData(writeData)
{
    m_address += offsetPos;
}

CCETestParamSetPackage_WriteRunParam::CCETestParamSetPackage_WriteRunParam(const QByteArray &parseData, quint16 offsetPos):
    CCEAbstractTestParamSetPackage(parseData)
{
    m_address += offsetPos;
}

CCETestParamSetPackage_ReadRunParam::CCETestParamSetPackage_ReadRunParam(quint16 offsetPos, quint8 readLenght):
    m_readLenght(readLenght)
{
    m_address += offsetPos;
}

CCETestParamSetPackage_ReadRunParam::CCETestParamSetPackage_ReadRunParam(quint16 offsetPos, const QByteArray &data):
    CCEAbstractTestParamSetPackage(data)
{
    m_address += offsetPos;
}

QByteArray CCETestParamSetPackage_ReadRunParam::getValue() const
{
    return getContent();
}

quint8 CCETestParamSetPackage_ReadTestStatus::getValue() const
{
    DO_GETCHARRESULT(getContent());
}

CCETestParamSetPackage_WriteTestStatus::CCETestParamSetPackage_WriteTestStatus(quint8 value):
    m_value(value)
{

}

SPressureMode CCETestParamSetPackage_ReadPressureMode::getValue() const
{
    SPressureMode pressureMode;
    QByteArray buffer = getContent();
    if (buffer.size() < sizeof(SPressureMode)) {
        return pressureMode;
    }
    memcpy(&pressureMode,buffer.data(),sizeof(SPressureMode));
    pressureMode.bigLittleSwap();
    return pressureMode;
}

CCETestParamSetPackage_WritePressureMode::CCETestParamSetPackage_WritePressureMode(const SPressureMode &pressureMode):
    m_pressureMode(pressureMode)
{
    m_pressureMode.bigLittleSwap();
}

quint8 CCETestParamSetPackage_ReadCounterBlowingTime::getValue() const
{
    DO_GETCHARRESULT(getContent());
}

CCETestParamSetPackage_WriteCounterBlowingTime::CCETestParamSetPackage_WriteCounterBlowingTime(quint8 value):
    m_value(value)
{

}
