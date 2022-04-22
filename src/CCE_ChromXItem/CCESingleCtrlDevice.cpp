#include "CCE_ChromXItem/CCESingleCtrlDevice.h"
#include "CCEAbstractModule_p.h"

class CCESingleCtrlDevicePrivate : public CCEAbstractModulePrivate
{
public:
    CCESingleCtrlDevicePrivate(){}
    ~CCESingleCtrlDevicePrivate(){}

    SSingleCtrl m_singleCtrl;
};

CCESingleCtrlDevice::CCESingleCtrlDevice(QObject *parent)
    : CCEAbstractModule{*new CCESingleCtrlDevicePrivate, parent}
{

}

CCESingleCtrlDevice::~CCESingleCtrlDevice()
{

}

void CCESingleCtrlDevice::registerCallBack()
{

}
