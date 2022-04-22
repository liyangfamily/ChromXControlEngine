﻿#include "CCE_ChromXItem/CCETestDataDevice.h"
#include "CCEAbstractModule_p.h"

class CCETestDataDevicePrivate : public CCEAbstractModulePrivate
{
public:
    CCETestDataDevicePrivate(){}
    ~CCETestDataDevicePrivate(){}

    STestData m_testData;
};


CCETestDataDevice::CCETestDataDevice(QObject *parent)
    : CCEAbstractModule{*new CCETestDataDevicePrivate, parent}
{

}

CCETestDataDevice::~CCETestDataDevice()
{

}

void CCETestDataDevice::registerCallBack()
{

}
