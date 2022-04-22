#include "CCE_ChromXItem/CCELEDPanelUnitDevice.h"
#include "CCEAbstractModule_p.h"

class CCELEDPanelUnitDevicePrivate : public CCEAbstractModulePrivate
{
public:
    CCELEDPanelUnitDevicePrivate(){}
    ~CCELEDPanelUnitDevicePrivate(){}

    SLEDPanelUnit m_LEDPanelUnit;
};

CCELEDPanelUnitDevice::CCELEDPanelUnitDevice(QObject *parent)
    : CCEAbstractModule{*new CCELEDPanelUnitDevicePrivate, parent}
{

}

CCELEDPanelUnitDevice::~CCELEDPanelUnitDevice()
{

}

void CCELEDPanelUnitDevice::registerCallBack()
{

}
