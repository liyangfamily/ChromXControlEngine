﻿#include "CCE_ChromXItem/CCEStatusWarnDevice.h"
#include "CCEAbstractModule_p.h"

class CCEStatusWarnDevicePrivate : public CCEAbstractModulePrivate
{
public:
    CCEStatusWarnDevicePrivate(){}
    ~CCEStatusWarnDevicePrivate(){}

    SStatusWarn m_statusWarn;
};


CCEStatusWarnDevice::CCEStatusWarnDevice(QObject *parent)
    : CCEAbstractModule{*new CCEStatusWarnDevicePrivate,parent}
{

}

CCEStatusWarnDevice::~CCEStatusWarnDevice()
{

}

void CCEStatusWarnDevice::registerCallBack()
{

}
