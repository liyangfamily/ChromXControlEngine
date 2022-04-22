#ifndef CCEMAINCTRLDEVICE_H
#define CCEMAINCTRLDEVICE_H

#include <CCE_ChromXItem/CCEChromXItemGlobal>
#include <CCE_ChromXItem/CCEAbstractModule.h>

class CCEMainCtrlDevicePrivate;
class CCE_CHROMXITEM_EXPORT CCEMainCtrlDevice : public CCEAbstractModule
{
    Q_DECLARE_PRIVATE(CCEMainCtrlDevice)
    Q_OBJECT
public:
    explicit CCEMainCtrlDevice(QObject *parent = nullptr);
    ~CCEMainCtrlDevice();
    /*********************************************************************************************************
    **主控设备控制
    *********************************************************************************************************/
    quint16 writeHardwareVersion(quint8 value, bool sync, int msec);
    quint16 readHardwareVersion(bool sync, int msec);
    quint8  getHardwareVersion();

    quint16 writeARMSoftwareVersion(quint8 value, bool sync, int msec);
    quint16 readARMSoftwareVersion(bool sync, int msec);
    quint8  getARMSoftwareVersion();

    quint16 writeStartSelfTest(quint8 value, bool sync, int msec);
    quint16 readStartSelfTest(bool sync, int msec);
    quint8  getStartSelfTest();
protected:
    virtual void registerCallBack() override;
    quint16 onParseReadHardwareVersion(const QByteArray& data);
    quint16 onParseWriteHardwareVersion(const QByteArray& data);
    quint16 onParseReadARMSoftwareVersion(const QByteArray& data);
    quint16 onParseWriteARMSoftwareVersion(const QByteArray& data);
    quint16 onParseReadStartSelfTest(const QByteArray& data);
    quint16 onParseWriteStartSelfTest(const QByteArray& data);
};

#endif // CCEMAINCTRLDEVICE_H
