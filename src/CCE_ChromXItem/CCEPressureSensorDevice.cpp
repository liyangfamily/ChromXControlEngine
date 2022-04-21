#include "CCE_ChromXItem/CCEPressureSensorDevice.h"
#include "CCEAbstractModule_p.h"

class CCEPressureSensorDevicePrivate : public CCEAbstractModulePrivate
{
public:
    CCEPressureSensorDevicePrivate(){}
    ~CCEPressureSensorDevicePrivate(){}
};

CCEPressureSensorDevice::CCEPressureSensorDevice(QObject *parent)
    : CCEAbstractModule{*new CCEPressureSensorDevicePrivate, parent}
{

}

CCEPressureSensorDevice::~CCEPressureSensorDevice()
{

}

void CCEPressureSensorDevice::registerCallBack()
{

}
