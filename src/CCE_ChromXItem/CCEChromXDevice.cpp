#include "CCE_ChromXItem/CCEChromXDevice.h"
#include "CCE_ChromXItem/CCEDetectServer.h"
#include "CCE_ChromXItem/CCEMainCtrlDevice.h"
#include "CCE_CommunicatEngine/CCECommunicatEngineDef.h"
#include <QDebug>
class CCEChromXDevicePrivate
{
public:
    CCEChromXDevicePrivate(){}
    //定义模块类
    CCEDetectServer m_detectServer;
    CCEMainCtrlDevice m_mainCtrlDevice;
    CCEChromXDevice* q_ptr = nullptr;
    SDetectItemInfo m_detectInfo;
    //在此类构造函数处给所有模块注册SDetectInfo结构体，让所有子模块共享这部分数据，包括socket信息
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
    return d_ptr->m_detectServer;
}

CCEMainCtrlDevice &CCEChromXDevice::mainCtrlDevice()
{
    return d_ptr->m_mainCtrlDevice;
}

bool CCEChromXDevice::initSubModule()
{
    if(!d_ptr->m_detectServer.isConnect()){
        return false;
    }
    qDebug()<<"initSubModule...";
    //创建子模块
    d_ptr->m_mainCtrlDevice.setSocket(d_ptr->m_detectServer.mainCOMSocket());
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
    connect(&d_ptr->m_detectServer,&CCEDetectServer::sig_DeviceConnect,this,[this]{
        initSubModule();//后续此部分内容还是需要改成SDetectInfo,在共享信息后，此链接可以不需要
    });
}
