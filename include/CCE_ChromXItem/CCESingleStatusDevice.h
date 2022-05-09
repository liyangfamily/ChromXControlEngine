#ifndef CCESINGLESTATUSDEVICE_H
#define CCESINGLESTATUSDEVICE_H

#include <CCE_ChromXItem/CCEChromXItemGlobal>
#include <CCE_ChromXItem/CCEAbstractModule.h>

class CCESingleStatusDevicePrivate;
class CCE_CHROMXITEM_EXPORT CCESingleStatusDevice : public CCEAbstractModule
{
    Q_DECLARE_PRIVATE(CCESingleStatusDevice)
    Q_OBJECT
public:
    explicit CCESingleStatusDevice(QObject *parent = nullptr);
    ~CCESingleStatusDevice();

    quint16 readTDCurTemperature(bool sync=true, int msec=CCE_Defalut_SyncTimeout);
    quint16 getTDCurTemperature();

    quint16 readTICurTemperature(bool sync=true, int msec=CCE_Defalut_SyncTimeout);
    quint16 getTICurTemperature();

    quint16 readCOLUMNTemperature(bool sync=true, int msec=CCE_Defalut_SyncTimeout);
    quint16 getCOLUMNTemperature();

    quint16 readMicroPIDValue(bool sync=true, int msec=CCE_Defalut_SyncTimeout);
    quint16 getMicroPIDValue();

    quint16 readEPCPressure(bool sync=true, int msec=CCE_Defalut_SyncTimeout);
    quint16 getEPCPressure();

    quint16 readAllInfo(bool sync=true, int msec=CCE_Defalut_SyncTimeout);
    SSingleStatus getAllInfo();

protected:
    virtual void registerCallBack() override;
    quint16 onParseReadTDCurTemperature(const QByteArray& data);
    quint16 onParseReadTICurTemperature(const QByteArray& data);
    quint16 onParseReadCOLUMNTemperature(const QByteArray& data);
    quint16 onParseReadMicroPIDValue(const QByteArray& data);
    quint16 onParseReadEPCPressure(const QByteArray& data);
    quint16 onParseReadAllInfo(const QByteArray& data);
};

#endif // CCESINGLESTATUSDEVICE_H
