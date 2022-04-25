#ifndef CCELEDPANELUNITDEVICE_H
#define CCELEDPANELUNITDEVICE_H

#include <CCE_ChromXItem/CCEChromXItemGlobal>
#include <CCE_ChromXItem/CCEAbstractModule.h>

class CCELEDPanelUnitDevicePrivate;
class CCE_CHROMXITEM_EXPORT CCELEDPanelUnitDevice : public CCEAbstractModule
{
    Q_DECLARE_PRIVATE(CCELEDPanelUnitDevice)
    Q_OBJECT
public:
    explicit CCELEDPanelUnitDevice(QObject *parent = nullptr);
    ~CCELEDPanelUnitDevice();

    quint16 writeHardwareVersion(quint8 value, bool sync=true, int msec=CCE_Defalut_SyncTimeout);
    quint16 readHardwareVersion(bool sync=true, int msec=CCE_Defalut_SyncTimeout);
    quint8  getHardwareVersion();

    quint16 readAllPressureSensor(bool sync=true, int msec=CCE_Defalut_SyncTimeout);
    quint16 getCarrierGasPressure();
    quint16 getSamplingPumpPressure();
    quint16 getAuxGasPressure();

    quint16 writeAllLight(SLEDPanelLight value, bool sync=true, int msec=CCE_Defalut_SyncTimeout);
    quint16 readAllLight(bool sync=true, int msec=CCE_Defalut_SyncTimeout);
    SLEDPanelLight  getAllLight();

    quint16 readAllEvnSensor(bool sync=true, int msec=CCE_Defalut_SyncTimeout);
    quint16 getEnvTemperature();
    quint16 getEnvHumidity();
    quint16 getEnvPressure();

protected:
    virtual void registerCallBack() override;
    quint16 onParseWriteHardwareVersion(const QByteArray& data);
    quint16 onParseReadHardwareVersion(const QByteArray& data);
    quint16 onParseReadAllPressureSensor(const QByteArray& data);
    quint16 onParseWriteAllLight(const QByteArray& data);
    quint16 onParseReadAllLight(const QByteArray& data);
    quint16 onParseAllEvnSensor(const QByteArray& data);
};

#endif // CCELEDPANELUNITDEVICE_H
