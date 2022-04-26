#ifndef CCESTATUSWARNDEVICE_H
#define CCESTATUSWARNDEVICE_H

#include <CCE_ChromXItem/CCEChromXItemGlobal>
#include <CCE_ChromXItem/CCEAbstractModule.h>

class CCEStatusWarnDevicePrivate;
class CCE_CHROMXITEM_EXPORT CCEStatusWarnDevice : public CCEAbstractModule
{
    Q_DECLARE_PRIVATE(CCEStatusWarnDevice)
    Q_OBJECT
public:
    enum EDeviceStatus{
        EDS_CarrierGasRunningOut = 1,
        EDS_UnableToMaintainCarrierGasPressure = 2,
        EDS_SamplingPressureAnomaly = 4,
        EDS_TDFault = 8,
        EDS_TIFault = 16,
        EDS_COLUMNFault = 32,
        EDS_PIDFault = 64,
        EDS_OvertemperatureAlarm = 128,
    };
    explicit CCEStatusWarnDevice(QObject *parent = nullptr);
    ~CCEStatusWarnDevice();

    quint16 readExistAbnormal(bool sync=true, int msec=CCE_Defalut_SyncTimeout);
    quint8 getExistAbnormal();

    quint16 readDeviceStatus(bool sync=true, int msec=CCE_Defalut_SyncTimeout);
    quint8 getDeviceStatus();
    bool testDeviceStatus(EDeviceStatus testStatus);

    quint16 readDeviceSelfTestStatus(bool sync=true, int msec=CCE_Defalut_SyncTimeout);
    quint8 getDeviceSelfTestStatus();

    quint16 readDeviceTestComplete(bool sync=true, int msec=CCE_Defalut_SyncTimeout);
    quint8 getDeviceTestComplete();
protected:
    virtual void registerCallBack() override;
    quint16 onParseReadExistAbnormal(const QByteArray& data);
    quint16 onParseReadDeviceStatus(const QByteArray& data);
    quint16 onParseReadDeviceSelfTestStatus(const QByteArray& data);
    quint16 onParseReadDeviceTestComplete(const QByteArray& data);
};

#endif // CCESTATUSWARNDEVICE_H
