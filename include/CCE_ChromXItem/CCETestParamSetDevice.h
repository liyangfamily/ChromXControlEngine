#ifndef CCETESTPARAMSETDEVICE_H
#define CCETESTPARAMSETDEVICE_H

#include <CCE_ChromXItem/CCEChromXItemGlobal>
#include <CCE_ChromXItem/CCEAbstractModule.h>

class CCETestParamSetDevicePrivate;
class CCE_CHROMXITEM_EXPORT CCETestParamSetDevice : public CCEAbstractModule
{
    Q_DECLARE_PRIVATE(CCETestParamSetDevice)
    Q_OBJECT
public:
    explicit CCETestParamSetDevice(QObject *parent = nullptr);
    ~CCETestParamSetDevice();
    quint16 writePIDAll(const SPIDAll& data , bool sync=true, int msec=CCE_Defalut_SyncTimeout);
    quint16 readPIDAll(bool sync=true, int msec=1000);
    SPIDAll&  getPIDAll();

    quint16 writeRunParam(const SRunParamSet& data , bool sync=true, int msec=CCE_Defalut_SyncTimeout);
    quint16 readRunParam(bool sync=true, int msec=1000);
    SRunParamSet&  getRunParam();

    quint16 writeTestStatus(quint8 value , bool sync=true, int msec=CCE_Defalut_SyncTimeout);
    quint16 readTestStatus(bool sync=true, int msec=1000);
    quint8  getTestStatus();
protected:
    virtual void registerCallBack() override;
    quint16 onParseWriteAllPID(const QByteArray& data);
    quint16 onParseReadAllPID(const QByteArray& data);
    quint16 onParseWriteRunParam(const QByteArray& data);
    quint16 onParseReadRunParam(const QByteArray& data);
    quint16 onParseWriteTestStatus(const QByteArray& data);
    quint16 onParseReadTestStatus(const QByteArray& data);
};

#endif // CCETESTPARAMSETDEVICE_H
