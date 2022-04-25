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
    SPIDAll PIDAll{0};
    QByteArray buffer = getContent();
    if (buffer.size() < sizeof(SPIDAll)) {
        return PIDAll;
    }
    memcpy(&PIDAll,buffer.data(),sizeof(SPIDAll));
    return PIDAll;
}

CCETestParamSetPackage_WriteAllPID::CCETestParamSetPackage_WriteAllPID(const SPIDAll &PIDAll):
    m_PIDAll(PIDAll)
{

}

CCETestParamSetPackage_WriteTestParamSet::CCETestParamSetPackage_WriteTestParamSet(quint16 offsetPos, const QByteArray &writeData):
    m_writeData(writeData)
{
    m_address += offsetPos;
}

CCETestParamSetPackage_ReadTestParamSet::CCETestParamSetPackage_ReadTestParamSet(quint16 offsetPos, quint8 readLenght):
    m_readLenght(readLenght)
{
    m_address += offsetPos;
}

QByteArray CCETestParamSetPackage_ReadTestParamSet::getValue() const
{
    return getContent();
}
