#ifndef CCETESTDATADEVICE_H
#define CCETESTDATADEVICE_H

#include <CCE_ChromXItem/CCEChromXItemGlobal>
#include <CCE_ChromXItem/CCEAbstractModule.h>

class CCETestDataDevicePrivate;
class CCE_CHROMXITEM_EXPORT CCETestDataDevice : public CCEAbstractModule
{
    Q_DECLARE_PRIVATE(CCETestDataDevice)
    Q_OBJECT
public:
    explicit CCETestDataDevice(QObject *parent = nullptr);
    ~CCETestDataDevice();

    quint16 readTDCurTemperature(bool sync=true, int msec=CCE_Defalut_SyncTimeout);
    quint16 getTDCurTemperature();

    quint16 readTICurTemperature(bool sync=true, int msec=CCE_Defalut_SyncTimeout);
    quint16 getTICurTemperature();

    quint16 readCurTestRunTime(bool sync=true, int msec=CCE_Defalut_SyncTimeout);
    quint16 getCurTestRunTime();

    quint16 readCOLUMNTemperature(bool sync=true, int msec=CCE_Defalut_SyncTimeout);
    quint16 getCOLUMNTemperature();

    quint16 readMicroPIDValue(bool sync=true, int msec=CCE_Defalut_SyncTimeout);
    quint32 getMicroPIDValue();

    quint16 readAllInfo(bool sync=true, int msec=CCE_Defalut_SyncTimeout);
    STestData getAllInfo();

protected:
    virtual void registerCallBack() override;
    quint16 onParseReadTDCurTemperature(const QByteArray& data);
    quint16 onParseReadTICurTemperature(const QByteArray& data);
    quint16 onParseReadCurTestRunTime(const QByteArray& data);
    quint16 onParseReadCOLUMNTemperature(const QByteArray& data);
    quint16 onParseReadMicroPIDValue(const QByteArray& data);
    quint16 onParseReadAllInfo(const QByteArray& data);
    quint16 onParseReportAllInfo(const QByteArray& data);
};

#endif // CCETESTDATADEVICE_H
