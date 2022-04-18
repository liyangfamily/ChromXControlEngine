#ifndef CCEMAINCTRLDEVICE_H
#define CCEMAINCTRLDEVICE_H

#include <CCE_ChromXItem/CCEChromXItemGlobal>
#include <CCE_ChromXItem/CCEAbstractModule.h>

class CCEMainCtrlDevicePrivate;
class CCE_CHROMXITEM_EXPORT CCEMainCtrlDevice : public CCEAbstractModule
{
    Q_OBJECT
public:
    explicit CCEMainCtrlDevice(QObject *parent = nullptr);
    ~CCEMainCtrlDevice();
    /*********************************************************************************************************
    **主控设备控制
    *********************************************************************************************************/
    quint16 writeHardwareVersion(int value, bool sync, int msec);
    quint16 readHardwareVersion(bool sync, int msec);
    quint8  getHardwareVersion();
protected:
    virtual void registerCallBack() override;
    quint16 onParseReadHardwareVersion(const QByteArray& data);
};

#endif // CCEMAINCTRLDEVICE_H
