#include "CCE_ChromXItem/CCEMainCtrlDevice.h"
#include "CCEAbstractModule_p.h"
#include <CCE_CommunicatEngine/CCEClusterProxy>

class CCEMainCtrlDevicePrivate : public CCEAbstractModulePrivate
{
public:
    CCEMainCtrlDevicePrivate(){}
    ~CCEMainCtrlDevicePrivate(){}
};


CCEMainCtrlDevice::CCEMainCtrlDevice(QObject *parent):
    CCEAbstractModule{*new CCEMainCtrlDevicePrivate, parent}
{
}

CCEMainCtrlDevice::~CCEMainCtrlDevice()
{
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

void CCEMainCtrlDevice::registerCallBack()
{
    d_ptr->m_packageMgr.registerPackage(CCEMainCtrlPackage_ReadHardwareVersion(),
                                        std::bind(&CCEMainCtrlDevice::onParseReadHardwareVersion,this,std::placeholders::_1));
    d_ptr->m_packageMgr.registerPackage(CCEMainCtrlPackage_WriteHardwareVersion(),
                                        std::bind(&CCEMainCtrlDevice::onParseReadHardwareVersion,this,std::placeholders::_1));
}

quint16 CCEMainCtrlDevice::onParseReadHardwareVersion(const QByteArray &data)
{
    qDebug()<<"Got it!"<<CCEUIHelper::byteArrayToHexStr(data);
    return quint16();
}
