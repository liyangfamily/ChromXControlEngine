#include "CCE_ChromXItem/CCEMainCtrlDevice.h"
#include <CCE_CommunicatEngine/CCEPackageManager>
#include <CCE_CommunicatEngine/CCEPackageDispatcher>
#include <CCE_CommunicatEngine/CCEClusterProxy>

class CCEMainCtrlDevicePrivate
{
public:
    CCEMainCtrlDevicePrivate(){}
    CCEMainCtrlDevice* q_ptr = nullptr;

    QObject* socket=nullptr;
    CCEPackageManager m_packageMgr;
};


CCEMainCtrlDevice::CCEMainCtrlDevice(QObject *parent): QObject{parent},
    d_ptr(new CCEMainCtrlDevicePrivate)
{
    init();
}

CCEMainCtrlDevice::~CCEMainCtrlDevice()
{

}

void CCEMainCtrlDevice::setSocket(QObject *socket)
{
    Q_ASSERT(socket);
    if(!socket){
        qDebug()<<"setSocket is nullptr.";
    }
    d_ptr->socket = socket;
}

quint16 CCEMainCtrlDevice::writeHardwareVersion(int value, bool sync, int msec)
{
    return quint16();
}

quint16 CCEMainCtrlDevice::readHardwareVersion(bool sync, int msec)
{
    CCEMainCtrlPackage_ReadHardwareVersion pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

quint8 CCEMainCtrlDevice::getHardwareVersion()
{
    return quint8();
}

bool CCEMainCtrlDevice::event(QEvent *e)
{
    if (e->type() == CCEPackageEvent::s_transitPackage_eventType)
    {
        CCEPackageEvent *tempE = static_cast<CCEPackageEvent*>(e);
        d_ptr->m_packageMgr.handle(CCEPackage(tempE->package().data()));
    }
    return QObject::event(e);
}

bool CCEMainCtrlDevice::init()
{
    gDispatcher->registerTransitObject(this);
    registerCallBack();
    return true;
}

void CCEMainCtrlDevice::registerCallBack()
{
    d_ptr->m_packageMgr.registerPackage(CCEMainCtrlPackage_ReadHardwareVersion(),
                                        std::bind(&CCEMainCtrlDevice::onParseReadHardwareVersion,this,std::placeholders::_1));
}

quint16 CCEMainCtrlDevice::onParseReadHardwareVersion(const QByteArray &data)
{
    qDebug()<<"Got it!"<<CCEUIHelper::byteArrayToHexStr(data);
    return quint16();
}
