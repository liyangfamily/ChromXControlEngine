#include "CCE_ChromXItem/CCEChromXDevice.h"
#include "CCE_ChromXItem/CCEDetectServer.h"
#include "CCE_ChromXItem/CCEMainCtrlDevice.h"
#include "CCE_ChromXItem/CCEPressureSensorDevice.h"
#include "CCE_ChromXItem/CCESingleCtrlDevice.h"
#include "CCE_ChromXItem/CCESingleStatusDevice.h"
#include "CCE_ChromXItem/CCEStatusWarnDevice.h"
#include "CCE_ChromXItem/CCETestDataDevice.h"
#include "CCE_ChromXItem/CCETestParamSetDevice.h"

#include "CCE_CommunicatEngine/CCECommunicatEngineDef.h"
#include <QDebug>
class CCEChromXDevicePrivate
{
public:
    CCEChromXDevicePrivate(){}
    ~CCEChromXDevicePrivate(){}
    CCEChromXDevice* q_ptr = nullptr;

    //定义模块类
    CCEDetectServer* m_detectServer = nullptr;
    CCEMainCtrlDevice* m_mainCtrlDevice = nullptr;
    CCEPressureSensorDevice* m_pressureSensorDevice = nullptr;
    CCESingleCtrlDevice* m_singleCtrlDevice = nullptr;
    CCESingleStatusDevice* m_singleStatusDevice = nullptr;
    CCEStatusWarnDevice* m_statusWarnDevice = nullptr;
    CCETestDataDevice* m_testDataDevice = nullptr;
    CCETestParamSetDevice* m_testParamSetDevice = nullptr;
};

CCEChromXDevice::~CCEChromXDevice()
{

}

CCEChromXDevice &CCEChromXDevice::getInstance()
{
    static CCEChromXDevice _instance;
    return _instance;
}

CCEDetectServer &CCEChromXDevice::detectServer()
{
    return *d_ptr->m_detectServer;
}

CCEMainCtrlDevice &CCEChromXDevice::mainCtrlDevice()
{
    return *d_ptr->m_mainCtrlDevice;
}

CCEPressureSensorDevice &CCEChromXDevice::pressureSensorDevice()
{
return *d_ptr->m_pressureSensorDevice;
}

CCESingleCtrlDevice &CCEChromXDevice::singleCtrlDevice()
{
return *d_ptr->m_singleCtrlDevice;
}

CCESingleStatusDevice &CCEChromXDevice::singleStatusDevice()
{
return *d_ptr->m_singleStatusDevice;
}

CCEStatusWarnDevice &CCEChromXDevice::statusWarnDevice()
{
return *d_ptr->m_statusWarnDevice;
}

CCETestDataDevice &CCEChromXDevice::testDataDevice()
{
return *d_ptr->m_testDataDevice;
}

CCETestParamSetDevice &CCEChromXDevice::testParamSetDevice()
{
return *d_ptr->m_testParamSetDevice;
}

bool CCEChromXDevice::registerModule()
{
    //初始化探卡服务
    d_ptr->m_detectServer = new CCEDetectServer(this);

    //初始化主控模块
    d_ptr->m_mainCtrlDevice = new CCEMainCtrlDevice(this);
    d_ptr->m_mainCtrlDevice->init(d_ptr->m_detectServer->getMainDetectInfo());

    //初始化压力传感器单元
    d_ptr->m_pressureSensorDevice = new CCEPressureSensorDevice(this);
    d_ptr->m_pressureSensorDevice->init(d_ptr->m_detectServer->getMainDetectInfo());

    //初始化单控控制单元
    d_ptr->m_singleCtrlDevice = new CCESingleCtrlDevice(this);
    d_ptr->m_singleCtrlDevice->init(d_ptr->m_detectServer->getMainDetectInfo());

    //初始化单控状态单元
    d_ptr->m_singleStatusDevice = new CCESingleStatusDevice(this);
    d_ptr->m_singleStatusDevice->init(d_ptr->m_detectServer->getMainDetectInfo());

    //初始化测试参数设置单元
    d_ptr->m_testParamSetDevice = new CCETestParamSetDevice(this);
    d_ptr->m_testParamSetDevice->init(d_ptr->m_detectServer->getMainDetectInfo());

    //初始化测试数据单元
    d_ptr->m_testDataDevice = new CCETestDataDevice(this);
    d_ptr->m_testDataDevice->init(d_ptr->m_detectServer->getMainDetectInfo());

    //初始化状态警告单元
    d_ptr->m_statusWarnDevice = new CCEStatusWarnDevice(this);
    d_ptr->m_statusWarnDevice->init(d_ptr->m_detectServer->getMainDetectInfo());
    return true;
}

bool CCEChromXDevice::releaseSubModule()
{
    //释放子模块
    return true;
}

CCEChromXDevice::CCEChromXDevice():
    d_ptr(new CCEChromXDevicePrivate)
{
    d_ptr->q_ptr = this;
    registerModule();
}
