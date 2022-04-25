#include "CCE_CommunicatEngine/CCEStatusWarnPackage.h"

CCEAbstractWarnStatusPackage::CCEAbstractWarnStatusPackage()
{

}

CCEAbstractWarnStatusPackage::CCEAbstractWarnStatusPackage(const QByteArray &data)
    : CCEPackage(data)
{

}

CCEAbstractWarnStatusPackage::~CCEAbstractWarnStatusPackage()
{

}

quint8 CCEWarnStatusPackage_ReadExistAbnormal::getValue() const
{
    DO_GETCHARRESULT(getContent());
}

quint8 CCEWarnStatusPackage_ReadDeviceStatus::getValue() const
{
    DO_GETCHARRESULT(getContent());
}

quint8 CCEWarnStatusPackage_ReadDeviceSelfTestStatus::getValue() const
{
    DO_GETCHARRESULT(getContent());
}

quint8 CCEWarnStatusPackage_ReadDeviceTestComplete::getValue() const
{
    DO_GETCHARRESULT(getContent());
}
