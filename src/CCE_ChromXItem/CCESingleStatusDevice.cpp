#include "CCE_ChromXItem/CCESingleStatusDevice.h"
#include "CCEAbstractModule_p.h"

class CCESingleStatusDevicePrivate : public CCEAbstractModulePrivate
{
public:
    CCESingleStatusDevicePrivate(){}
    ~CCESingleStatusDevicePrivate(){}
};


CCESingleStatusDevice::CCESingleStatusDevice(QObject *parent)
    : CCEAbstractModule{*new CCESingleStatusDevicePrivate, parent}
{

}

CCESingleStatusDevice::~CCESingleStatusDevice()
{

}

void CCESingleStatusDevice::registerCallBack()
{

}
