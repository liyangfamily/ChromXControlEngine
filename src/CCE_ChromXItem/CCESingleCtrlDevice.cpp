#include "CCE_ChromXItem/CCESingleCtrlDevice.h"
#include "CCEAbstractModule_p.h"
#include <CCE_CommunicatEngine/CCEClusterProxy>

class CCESingleCtrlDevicePrivate : public CCEAbstractModulePrivate
{
public:
    CCESingleCtrlDevicePrivate(){}
    ~CCESingleCtrlDevicePrivate(){}

    SSingleCtrl m_singleCtrlData;
};

CCESingleCtrlDevice::CCESingleCtrlDevice(QObject *parent)
    : CCEAbstractModule{*new CCESingleCtrlDevicePrivate, parent}
{

}

CCESingleCtrlDevice::~CCESingleCtrlDevice()
{

}


quint16 CCESingleCtrlDevice::writePumpVoltage(quint8 pumpVoltage, bool sync, int msec)
{
    CCESingleCtrlPackage_WritePumpVoltage pack(pumpVoltage);
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr, pack);
}


quint16 CCESingleCtrlDevice::readPumpVoltage(bool sync, int msec)
{
    CCESingleCtrlPackage_ReadPumpVoltage pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr, pack);
}


quint8 CCESingleCtrlDevice::getPumpVoltage()
{
    Q_D(CCESingleCtrlDevice);
    return d->m_singleCtrlData.pumpVoltage;
}


quint16 CCESingleCtrlDevice::writeSampleValve(quint8 sampleValveSwitch, bool sync, int msec)
{
    CCESingleCtrlPackage_WriteSampleValve pack(sampleValveSwitch);
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr, pack);
}


quint16 CCESingleCtrlDevice::readSampleValve(bool sync, int msec)
{
    CCESingleCtrlPackage_ReadSampleValve pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr, pack);
}


quint8 CCESingleCtrlDevice::getSampleValve()
{
    Q_D(CCESingleCtrlDevice);
    return d->m_singleCtrlData.samplingValveSwitch;
}


quint16 CCESingleCtrlDevice::writeDetectValve(quint8 detectValveSwitch, bool sync, int msec)
{
    CCESingleCtrlPackage_WriteDetectValve pack(detectValveSwitch);
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr, pack);
}


quint16 CCESingleCtrlDevice::readDetectValve(bool sync, int msec)
{
    CCESingleCtrlPackage_ReadDetectValve pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr, pack);
}


quint8 CCESingleCtrlDevice::getDetectValve()
{
    Q_D(CCESingleCtrlDevice);
    return d->m_singleCtrlData.testValveSwitch;
}


quint16 CCESingleCtrlDevice::writeFan(quint8 fanSwitch, bool sync, int msec)
{
    CCESingleCtrlPackage_WriteFan pack(fanSwitch);
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr, pack);
}


quint16 CCESingleCtrlDevice::readFan(bool sync, int msec)
{
    CCESingleCtrlPackage_ReadFan pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr, pack);
}


quint8 CCESingleCtrlDevice::getFan()
{
    Q_D(CCESingleCtrlDevice);
    return d->m_singleCtrlData.fanSwitch;
}

quint16 CCESingleCtrlDevice::writeTDModule(quint16 TDStartTime, quint8 TDPWM, quint8 TDSwitch,
                                           bool sync, int msec)
{
    CCESingleCtrlPackage_WriteTDModule pack(TDStartTime, TDPWM, TDSwitch);
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr, pack);

}

quint16 CCESingleCtrlDevice::readTDModule(bool sync, int msec)
{
    CCESingleCtrlPackage_ReadTDModule pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr, pack);
}

SSingleDeviceCtrl CCESingleCtrlDevice::getTDAllData()
{
    Q_D(CCESingleCtrlDevice);
    return d->m_singleCtrlData.TDCtrl;
}

quint16 CCESingleCtrlDevice::writeTIModule(quint16 TIStartTime, quint8 TIPWM, quint8 TISwitch,
                                           bool sync, int msec)
{
    CCESingleCtrlPackage_WriteTIModule pack(TIStartTime, TIPWM, TISwitch);
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr, pack);
}


quint16 CCESingleCtrlDevice::readTIModule(bool sync, int msec)
{
    CCESingleCtrlPackage_ReadTIModule pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr, pack);
}

SSingleDeviceCtrl CCESingleCtrlDevice::getTIAllData()
{
    Q_D(CCESingleCtrlDevice);
    return d->m_singleCtrlData.TICtrl;
}

quint16 CCESingleCtrlDevice::writeCOLUMNModule(quint16 COLUMNStartTime, quint8 COLUMNPWM, quint8 COLUMNSwitch,
                                               bool sync, int msec)
{
    CCESingleCtrlPackage_WriteCOLUMNModule pack(COLUMNStartTime, COLUMNPWM, COLUMNSwitch);
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr, pack);
}

quint16 CCESingleCtrlDevice::readCOLUMNModule(bool sync, int msec)
{
    CCESingleCtrlPackage_ReadCOLUMNModule pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr, pack);
}

SSingleDeviceCtrl CCESingleCtrlDevice::getCOLUMNAllData()
{
    Q_D(CCESingleCtrlDevice);
    return d->m_singleCtrlData.COLUMNCtrl;
}

quint16 CCESingleCtrlDevice::writeMicroPIDModule(quint16 microPIDBiasVoltage, quint16 microPIDFreq, quint8 microPIDSwitch,
                                                 bool sync, int msec)
{
    CCESingleCtrlPackage_WritePIDModule pack(microPIDBiasVoltage, microPIDFreq, microPIDSwitch);
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr, pack);
}

quint16 CCESingleCtrlDevice::readMicroPIDModule(bool sync, int msec)
{
    CCESingleCtrlPackage_ReadPIDModule pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr, pack);
}

SSingleMicroPIDCtrl CCESingleCtrlDevice::getMicroPIDAllData()
{
    Q_D(CCESingleCtrlDevice);
    return d->m_singleCtrlData.MicroPIDCtrl;
}

quint16 CCESingleCtrlDevice::writeEPCVoltage(quint16 EPCVoltage, bool sync, int msec)
{
    CCESingleCtrlPackage_WriteEPCVoltage pack(EPCVoltage);
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr, pack);
}


quint16 CCESingleCtrlDevice::readEPCVoltage(bool sync, int msec)
{
    CCESingleCtrlPackage_ReadEPCVoltage pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr, pack);
}


quint16 CCESingleCtrlDevice::getEPCVoltage()
{
    Q_D(CCESingleCtrlDevice);
    return d->m_singleCtrlData.EPCCtrlVoltage;
}


quint16 CCESingleCtrlDevice::writeEPCSwitch(quint8 EPCSwitch, bool sync, int msec)
{
    CCESingleCtrlPackage_WriteEPCSwitch pack(EPCSwitch);
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr, pack);
}


quint16 CCESingleCtrlDevice::readEPCSwitch(bool sync, int msec)
{
    CCESingleCtrlPackage_ReadEPCSwitch pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr, pack);
}


quint8 CCESingleCtrlDevice::getEPCSwitch()
{
    Q_D(CCESingleCtrlDevice);
    return d->m_singleCtrlData.EPCSwitch;
}


void CCESingleCtrlDevice::registerCallBack()
{
    Q_D(CCESingleCtrlDevice);
    d->m_packageMgr.registerPackage(CCESingleCtrlPackage_WritePumpVoltage(),
                                    std::bind(&CCESingleCtrlDevice::onParseWritePumpVoltage,
                                              this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCESingleCtrlPackage_ReadPumpVoltage(),
                                    std::bind(&CCESingleCtrlDevice::onParseReadPumpVoltage,
                                              this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCESingleCtrlPackage_WriteSampleValve(),
                                    std::bind(&CCESingleCtrlDevice::onParseWriteSampleValve,
                                              this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCESingleCtrlPackage_ReadSampleValve(),
                                    std::bind(&CCESingleCtrlDevice::onParseReadSampleValve,
                                              this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCESingleCtrlPackage_WriteDetectValve(),
                                    std::bind(&CCESingleCtrlDevice::onParseWriteDetectValve,
                                              this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCESingleCtrlPackage_ReadDetectValve(),
                                    std::bind(&CCESingleCtrlDevice::onParseReadDetectValve,
                                              this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCESingleCtrlPackage_WriteFan(),
                                    std::bind(&CCESingleCtrlDevice::onParseWriteFan,
                                              this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCESingleCtrlPackage_ReadFan(),
                                    std::bind(&CCESingleCtrlDevice::onParseReadFan,
                                              this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCESingleCtrlPackage_WriteTDModule(),
                                    std::bind(&CCESingleCtrlDevice::onParseWriteTDModule,
                                              this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCESingleCtrlPackage_ReadTDModule(),
                                    std::bind(&CCESingleCtrlDevice::onParseReadTDModule,
                                              this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCESingleCtrlPackage_WriteTIModule(),
                                    std::bind(&CCESingleCtrlDevice::onParseWriteTIModule,
                                              this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCESingleCtrlPackage_ReadTIModule(),
                                    std::bind(&CCESingleCtrlDevice::onParseReadTIModule,
                                              this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCESingleCtrlPackage_WriteCOLUMNModule(),
                                    std::bind(&CCESingleCtrlDevice::onParseWriteCOLUMNModule,
                                              this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCESingleCtrlPackage_ReadCOLUMNModule(),
                                    std::bind(&CCESingleCtrlDevice::onParseReadCOLUMNModule,
                                              this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCESingleCtrlPackage_WritePIDModule(),
                                    std::bind(&CCESingleCtrlDevice::onParseWriteMicroPIDModule,
                                              this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCESingleCtrlPackage_ReadPIDModule(),
                                    std::bind(&CCESingleCtrlDevice::onParseReadMicroPIDModule,
                                              this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCESingleCtrlPackage_WriteEPCVoltage(),
                                    std::bind(&CCESingleCtrlDevice::onParseWriteEPCVoltage,
                                              this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCESingleCtrlPackage_ReadEPCVoltage(),
                                    std::bind(&CCESingleCtrlDevice::onParseReadEPCVoltage,
                                              this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCESingleCtrlPackage_WriteEPCSwitch(),
                                    std::bind(&CCESingleCtrlDevice::onParseWriteEPCSwitch,
                                              this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCESingleCtrlPackage_ReadEPCSwitch(),
                                    std::bind(&CCESingleCtrlDevice::onParseReadEPCSwitch,
                                              this,std::placeholders::_1));
}

quint16 CCESingleCtrlDevice::onParseWritePumpVoltage(const QByteArray &data)
{
    CCESingleCtrlPackage_WritePumpVoltage pack(data);
    DO_RETOPERATIONRESULT(pack);
}

quint16 CCESingleCtrlDevice::onParseReadPumpVoltage(const QByteArray &data)
{
    Q_D(CCESingleCtrlDevice);
    CCESingleCtrlPackage_ReadPumpVoltage pack(data);
    quint16 ret = pack.isValid();
    if(ret == CCEAPI::EResult::ER_Success) {
        d->m_singleCtrlData.pumpVoltage = pack.getPumpVoltage();
        qDebug()<<"Got it! pump voltage:"<<d->m_singleCtrlData.pumpVoltage;
    }
    return ret;
}

quint16 CCESingleCtrlDevice::onParseWriteSampleValve(const QByteArray &data)
{
    CCESingleCtrlPackage_WriteSampleValve pack(data);
    DO_RETOPERATIONRESULT(pack);
}

quint16 CCESingleCtrlDevice::onParseReadSampleValve(const QByteArray &data)
{
    Q_D(CCESingleCtrlDevice);
    CCESingleCtrlPackage_ReadSampleValve pack(data);
    quint16 ret = pack.isValid();
    if(ret == CCEAPI::EResult::ER_Success) {
        d->m_singleCtrlData.samplingValveSwitch = pack.getSampleValveStatus();
        qDebug()<<"Got it! sample valve:"<<d->m_singleCtrlData.samplingValveSwitch;
    }
    return ret;
}

quint16 CCESingleCtrlDevice::onParseWriteDetectValve(const QByteArray &data)
{
    CCESingleCtrlPackage_WriteDetectValve pack(data);
    DO_RETOPERATIONRESULT(pack);
}

quint16 CCESingleCtrlDevice::onParseReadDetectValve(const QByteArray &data)
{
    Q_D(CCESingleCtrlDevice);
    CCESingleCtrlPackage_ReadDetectValve pack(data);
    quint16 ret = pack.isValid();
    if(ret == CCEAPI::EResult::ER_Success) {
        d->m_singleCtrlData.testValveSwitch = pack.getDetectValveStatus();
        qDebug()<<"Got it! detect valve:"<<d->m_singleCtrlData.testValveSwitch;
    }
    return ret;
}

quint16 CCESingleCtrlDevice::onParseWriteFan(const QByteArray &data)
{
    CCESingleCtrlPackage_WriteFan pack(data);
    DO_RETOPERATIONRESULT(pack);
}

quint16 CCESingleCtrlDevice::onParseReadFan(const QByteArray &data)
{
    Q_D(CCESingleCtrlDevice);
    CCESingleCtrlPackage_ReadFan pack(data);
    quint16 ret = pack.isValid();
    if(ret == CCEAPI::EResult::ER_Success) {
        d->m_singleCtrlData.fanSwitch = pack.getFanStatus();
        qDebug()<<"Got it! fan switch:"<<d->m_singleCtrlData.fanSwitch;
    }
    return ret;
}

quint16 CCESingleCtrlDevice::onParseWriteTDModule(const QByteArray &data)
{
    CCESingleCtrlPackage_WriteTDModule pack(data);
    DO_RETOPERATIONRESULT(pack);
}

quint16 CCESingleCtrlDevice::onParseReadTDModule(const QByteArray &data)
{
    Q_D(CCESingleCtrlDevice);
    CCESingleCtrlPackage_ReadTDModule pack(data);
    quint16 ret = pack.isValid();
    if(ret == CCEAPI::EResult::ER_Success) {
        d->m_singleCtrlData.TDCtrl.startTime = pack.getTDStartTime();
        d->m_singleCtrlData.TDCtrl.PWMValue = pack.getTDPWM();
        d->m_singleCtrlData.TDCtrl.startSwitch = pack.getTDSwitch();
        qDebug()<<QString("Got it! TDStartTime:%1, Got it! TDPWM:%2, Got it! TDStartSwitch:%3.")
                  .arg(d->m_singleCtrlData.TDCtrl.startTime)
                  .arg(d->m_singleCtrlData.TDCtrl.PWMValue)
                  .arg(d->m_singleCtrlData.TDCtrl.startSwitch);
    }
    return ret;
}

quint16 CCESingleCtrlDevice::onParseWriteTIModule(const QByteArray &data)
{
    CCESingleCtrlPackage_WriteTIModule pack(data);
    DO_RETOPERATIONRESULT(pack);
}

quint16 CCESingleCtrlDevice::onParseReadTIModule(const QByteArray &data)
{
    Q_D(CCESingleCtrlDevice);
    CCESingleCtrlPackage_ReadTIModule pack(data);
    quint16 ret = pack.isValid();
    if(ret == CCEAPI::EResult::ER_Success) {
        d->m_singleCtrlData.TICtrl.startTime = pack.getTIStartTime();
        d->m_singleCtrlData.TICtrl.PWMValue = pack.getTIPWM();
        d->m_singleCtrlData.TICtrl.startSwitch = pack.getTISwitch();
        qDebug()<<QString("Got it! TIStartTime:%1, Got it! TIPWM:%2, Got it! TIStartSwitch:%3.")
                  .arg(d->m_singleCtrlData.TICtrl.startTime)
                  .arg(d->m_singleCtrlData.TICtrl.PWMValue)
                  .arg(d->m_singleCtrlData.TICtrl.startSwitch);
    }
    return ret;
}

quint16 CCESingleCtrlDevice::onParseWriteCOLUMNModule(const QByteArray &data)
{
    CCESingleCtrlPackage_WriteCOLUMNModule pack(data);
    DO_RETOPERATIONRESULT(pack);
}

quint16 CCESingleCtrlDevice::onParseReadCOLUMNModule(const QByteArray &data)
{
    Q_D(CCESingleCtrlDevice);
    CCESingleCtrlPackage_ReadCOLUMNModule pack(data);
    quint16 ret = pack.isValid();
    if(ret == CCEAPI::EResult::ER_Success) {
        d->m_singleCtrlData.COLUMNCtrl.startTime = pack.getCOLUMNStartTime();
        d->m_singleCtrlData.COLUMNCtrl.PWMValue = pack.getCOLUMNPWM();
        d->m_singleCtrlData.COLUMNCtrl.startSwitch = pack.getCOLUMNSwitch();
        qDebug()<<QString("Got it! COLUMNStartTime:%1, Got it! COLUMNPWM:%2, Got it! COLUMNStartSwitch:%3.")
                  .arg(d->m_singleCtrlData.COLUMNCtrl.startTime)
                  .arg(d->m_singleCtrlData.COLUMNCtrl.PWMValue)
                  .arg(d->m_singleCtrlData.COLUMNCtrl.startSwitch);
    }
    return ret;
}

quint16 CCESingleCtrlDevice::onParseWriteMicroPIDModule(const QByteArray &data)
{
    CCESingleCtrlPackage_WritePIDModule pack(data);
    DO_RETOPERATIONRESULT(pack);
}

quint16 CCESingleCtrlDevice::onParseReadMicroPIDModule(const QByteArray &data)
{
    Q_D(CCESingleCtrlDevice);
    CCESingleCtrlPackage_ReadPIDModule pack(data);
    quint16 ret = pack.isValid();
    if(ret == CCEAPI::EResult::ER_Success) {
        d->m_singleCtrlData.MicroPIDCtrl.biasVoltage = pack.getPIDBiasVoltage();
        d->m_singleCtrlData.MicroPIDCtrl.freq = pack.getPIDFrequency();
        d->m_singleCtrlData.MicroPIDCtrl.startSwitch = pack.getPIDSwitch();
        qDebug()<<QString("Got it! PIDBiasVoltage:%1, Got it! PIDFrequency:%2, Got it! PIDSwitch:%3.")
                  .arg(d->m_singleCtrlData.MicroPIDCtrl.biasVoltage)
                  .arg(d->m_singleCtrlData.MicroPIDCtrl.freq)
                  .arg(d->m_singleCtrlData.MicroPIDCtrl.startSwitch);
    }
    return ret;
}

quint16 CCESingleCtrlDevice::onParseWriteEPCVoltage(const QByteArray &data)
{
    CCESingleCtrlPackage_WriteEPCVoltage pack(data);
    DO_RETOPERATIONRESULT(pack);
}

quint16 CCESingleCtrlDevice::onParseReadEPCVoltage(const QByteArray &data)
{
    Q_D(CCESingleCtrlDevice);
    CCESingleCtrlPackage_ReadEPCVoltage pack(data);
    quint16 ret = pack.isValid();
    if(ret == CCEAPI::EResult::ER_Success) {
        d->m_singleCtrlData.EPCCtrlVoltage = pack.getEPCVoltage();
        qDebug()<<"Got it! EPCVoltage:"<<d->m_singleCtrlData.EPCCtrlVoltage;
    }
    return ret;
}

quint16 CCESingleCtrlDevice::onParseWriteEPCSwitch(const QByteArray &data)
{
    CCESingleCtrlPackage_WriteEPCSwitch pack(data);
    DO_RETOPERATIONRESULT(pack);
}

quint16 CCESingleCtrlDevice::onParseReadEPCSwitch(const QByteArray &data)
{
    Q_D(CCESingleCtrlDevice);
    CCESingleCtrlPackage_ReadEPCSwitch pack(data);
    quint16 ret = pack.isValid();
    if(ret == CCEAPI::EResult::ER_Success) {
        d->m_singleCtrlData.EPCSwitch = pack.getEPCSwitch();
        qDebug()<<"Got it! EPCSwitch:"<<d->m_singleCtrlData.EPCSwitch;
    }
    return ret;
}
