#include "CCE_ChromXItem/CCETestParamSetDevice.h"
#include "CCEAbstractModule_p.h"

class CCETestParamSetDevicePrivate : public CCEAbstractModulePrivate
{
public:
    CCETestParamSetDevicePrivate(){}
    ~CCETestParamSetDevicePrivate(){}

    STestParamSet m_testParamSet;
};


CCETestParamSetDevice::CCETestParamSetDevice(QObject *parent)
    : CCEAbstractModule{*new CCETestParamSetDevicePrivate, parent}
{

}

CCETestParamSetDevice::~CCETestParamSetDevice()
{

}

void CCETestParamSetDevice::registerCallBack()
{

}
