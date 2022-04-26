#ifndef CCESINGLECTRLDEVICE_H
#define CCESINGLECTRLDEVICE_H

#include <CCE_ChromXItem/CCEChromXItemGlobal>
#include <CCE_ChromXItem/CCEAbstractModule.h>

class CCESingleCtrlDevicePrivate;
class CCE_CHROMXITEM_EXPORT CCESingleCtrlDevice : public CCEAbstractModule
{
    Q_DECLARE_PRIVATE(CCESingleCtrlDevice)
    Q_OBJECT
public:
    explicit CCESingleCtrlDevice(QObject *parent = nullptr);
    ~CCESingleCtrlDevice();
    /*********************************************************************************************************
    **单控模控制单元（unit 0x12）
    *********************************************************************************************************/
    quint16 writePumpVoltage(quint8 pumpVoltage, bool sync = true, int msec = CCE_Defalut_SyncTimeout);
    quint16 readPumpVoltage(bool sync = true, int msec = CCE_Defalut_SyncTimeout);
    quint8  getPumpVoltage();

    quint16 writeSampleValve(quint8 sampleValveSwitch, bool sync = true, int msec = CCE_Defalut_SyncTimeout);
    quint16 readSampleValve(bool sync = true, int msec = CCE_Defalut_SyncTimeout);
    quint8  getSampleValve();

    quint16 writeDetectValve(quint8 detectValveSwitch, bool sync = true, int msec = CCE_Defalut_SyncTimeout);
    quint16 readDetectValve(bool sync = true, int msec = CCE_Defalut_SyncTimeout);
    quint8  getDetectValve();

    quint16 writeFan(quint8 fanSwitch, bool sync = true, int msec = CCE_Defalut_SyncTimeout);
    quint16 readFan(bool sync = true, int msec = CCE_Defalut_SyncTimeout);
    quint8  getFan();

    quint16 writeTDModule(quint16 TDStartTime, quint8 TDPWM, quint8 TDSwitch,
                          bool sync = true, int msec = CCE_Defalut_SyncTimeout);
    quint16 readTDModule(bool sync = true, int msec = CCE_Defalut_SyncTimeout);
    SSingleDeviceCtrl getTDAllData();

    quint16 writeTIModule(quint16 TIStartTime, quint8 TIPWM, quint8 TISwitch,
                          bool sync = true, int msec = CCE_Defalut_SyncTimeout);
    quint16 readTIModule(bool sync = true, int msec = CCE_Defalut_SyncTimeout);
    SSingleDeviceCtrl getTIAllData();

    quint16 writeCOLUMNModule(quint16 COLUMNStartTime, quint8 COLUMNPWM, quint8 COLUMNSwitch,
                          bool sync = true, int msec = CCE_Defalut_SyncTimeout);
    quint16 readCOLUMNModule(bool sync = true, int msec = CCE_Defalut_SyncTimeout);
    SSingleDeviceCtrl getCOLUMNAllData();

    quint16 writeMicroPIDModule(quint16 microPIDBiasVoltage, quint16 microPIDFreq, quint8 microPIDSwitch,
                          bool sync = true, int msec = CCE_Defalut_SyncTimeout);
    quint16 readMicroPIDModule(bool sync = true, int msec = CCE_Defalut_SyncTimeout);
    SSingleMicroPIDCtrl getMicroPIDAllData();


    quint16 writeEPCVoltage(quint16 EPCVoltage, bool sync = true, int msec = CCE_Defalut_SyncTimeout);
    quint16 readEPCVoltage(bool sync = true, int msec = CCE_Defalut_SyncTimeout);
    quint16 getEPCVoltage();

    quint16 writeEPCSwitch(quint8 EPCSwitch, bool sync = true, int msec = CCE_Defalut_SyncTimeout);
    quint16 readEPCSwitch(bool sync = true, int msec = CCE_Defalut_SyncTimeout);
    quint8  getEPCSwitch();

protected:
    virtual void registerCallBack() override;
    quint16 onParseWritePumpVoltage(const QByteArray& data);
    quint16 onParseReadPumpVoltage(const QByteArray& data);
    quint16 onParseWriteSampleValve(const QByteArray& data);
    quint16 onParseReadSampleValve(const QByteArray& data);
    quint16 onParseWriteDetectValve(const QByteArray& data);
    quint16 onParseReadDetectValve(const QByteArray& data);
    quint16 onParseWriteFan(const QByteArray& data);
    quint16 onParseReadFan(const QByteArray& data);
    quint16 onParseWriteTDModule(const QByteArray& data);
    quint16 onParseReadTDModule(const QByteArray& data);
    quint16 onParseWriteTIModule(const QByteArray& data);
    quint16 onParseReadTIModule(const QByteArray& data);
    quint16 onParseWriteCOLUMNModule(const QByteArray& data);
    quint16 onParseReadCOLUMNModule(const QByteArray& data);
    quint16 onParseWriteMicroPIDModule(const QByteArray& data);
    quint16 onParseReadMicroPIDModule(const QByteArray& data);
    quint16 onParseWriteEPCVoltage(const QByteArray& data);
    quint16 onParseReadEPCVoltage(const QByteArray& data);
    quint16 onParseWriteEPCSwitch(const QByteArray& data);
    quint16 onParseReadEPCSwitch(const QByteArray& data);
};

#endif // CCESINGLECTRLDEVICE_H
