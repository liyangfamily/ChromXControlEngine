#include "CCE_ChromXItem/CCEChromXDevice.h"
#include "CCE_ChromXItem/CCEDetectServer.h"
#include "CCE_ChromXItem/CCEMainCtrlDevice.h"
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

bool CCEChromXDevice::registerModule()
{
    //初始化探卡服务
    d_ptr->m_detectServer = new CCEDetectServer(this);

    //初始化主控模块
    d_ptr->m_mainCtrlDevice = new CCEMainCtrlDevice(this);
    d_ptr->m_mainCtrlDevice->init(d_ptr->m_detectServer->getMainDetectInfo());
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
