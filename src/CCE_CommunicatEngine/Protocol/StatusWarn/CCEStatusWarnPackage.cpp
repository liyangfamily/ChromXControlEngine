#include "CCE_CommunicatEngine/CCEStatusWarnPackage.h"

CCEAbstractStatusWarnPackage::CCEAbstractStatusWarnPackage()
{

}

CCEAbstractStatusWarnPackage::CCEAbstractStatusWarnPackage(const QByteArray &data)
    : CCEPackage(data)
{

}

CCEAbstractStatusWarnPackage::~CCEAbstractStatusWarnPackage()
{

}

quint8 CCEStatusWarnPackage_ReadExistAbnormal::getValue() const
{
    DO_GETCHARRESULT(getContent());
}

quint8 CCEStatusWarnPackage_ReadDeviceStatus::getValue() const
{
    DO_GETCHARRESULT(getContent());
}

quint8 CCEStatusWarnPackage_ReadDeviceSelfTestStatus::getValue() const
{
    DO_GETCHARRESULT(getContent());
}

quint8 CCEStatusWarnPackage_ReadDeviceTestComplete::getValue() const
{
    DO_GETCHARRESULT(getContent());
}
