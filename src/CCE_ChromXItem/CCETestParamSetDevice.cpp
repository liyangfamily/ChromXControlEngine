#include "CCETestParamSetDevice.h"
#include "CCEAbstractModule_p.h"

class CCETestParamSetDevicePrivate : public CCEAbstractModulePrivate
{
public:
    CCETestParamSetDevicePrivate(){}
    ~CCETestParamSetDevicePrivate(){}
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
