#include "CCE_ChromXItem/CCETestDataDevice.h"
#include "CCEAbstractModule_p.h"
#include <CCE_CommunicatEngine/CCEClusterProxy>


class CCETestDataDevicePrivate : public CCEAbstractModulePrivate
{
    Q_DECLARE_PUBLIC(CCETestDataDevice)
public:
    CCETestDataDevicePrivate(){}
    ~CCETestDataDevicePrivate(){}

    STestData m_testData;
};


CCETestDataDevice::CCETestDataDevice(QObject *parent)
    : CCEAbstractModule{*new CCETestDataDevicePrivate, parent}
{

}

CCETestDataDevice::~CCETestDataDevice()
{

}

quint16 CCETestDataDevice::readTDCurTemperature(bool sync, int msec)
{
    CCETestDataPackage_ReadTDCurTemperature pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

quint16 CCETestDataDevice::getTDCurTemperature()
{
    Q_D(CCETestDataDevice);
    return d->m_testData.TDCurTemperature;
}

quint16 CCETestDataDevice::readTICurTemperature(bool sync, int msec)
{
    CCETestDataPackage_ReadTICurTemperature pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

quint16 CCETestDataDevice::getTICurTemperature()
{
    Q_D(CCETestDataDevice);
    return d->m_testData.TICurTemperature;
}

quint16 CCETestDataDevice::readCurTestRunTime(bool sync, int msec)
{
    CCETestDataPackage_ReadCurTestRunTime pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

quint16 CCETestDataDevice::getCurTestRunTime()
{
    Q_D(CCETestDataDevice);
    return d->m_testData.curTestRunTime;
}

quint16 CCETestDataDevice::readCOLUMNTemperature(bool sync, int msec)
{
    CCETestDataPackage_ReadCOLUMNTemperature pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

quint16 CCETestDataDevice::getCOLUMNTemperature()
{
    Q_D(CCETestDataDevice);
    return d->m_testData.COLUMNTemperature;
}

quint16 CCETestDataDevice::readMicroPIDValue(bool sync, int msec)
{
    CCETestDataPackage_ReadMicroPIDValue pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

quint16 CCETestDataDevice::getMicroPIDValue()
{
    Q_D(CCETestDataDevice);
    return d->m_testData.MicroPIDValue;
}

quint16 CCETestDataDevice::readAllInfo(bool sync, int msec)
{
    CCETestDataPackage_ReadAllInfo pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

STestData CCETestDataDevice::getAllInfo()
{
    Q_D(CCETestDataDevice);
    return d->m_testData;
}

void CCETestDataDevice::registerCallBack()
{
    Q_D(CCETestDataDevice);
    d->m_packageMgr.registerPackage(CCETestDataPackage_ReadTDCurTemperature(),
                                        std::bind(&CCETestDataDevice::onParseReadTDCurTemperature,this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCETestDataPackage_ReadTICurTemperature(),
                                        std::bind(&CCETestDataDevice::onParseReadTICurTemperature,this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCETestDataPackage_ReadCurTestRunTime(),
                                    std::bind(&CCETestDataDevice::onParseReadCurTestRunTime,this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCETestDataPackage_ReadCOLUMNTemperature(),
                                        std::bind(&CCETestDataDevice::onParseReadCOLUMNTemperature,this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCETestDataPackage_ReadMicroPIDValue(),
                                        std::bind(&CCETestDataDevice::onParseReadMicroPIDValue,this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCETestDataPackage_ReadAllInfo(),
                                        std::bind(&CCETestDataDevice::onParseReadAllInfo,this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCETestDataPackage_ReportAllInfo(),
                                        std::bind(&CCETestDataDevice::onParseReportAllInfo,this,std::placeholders::_1));
}

quint16 CCETestDataDevice::onParseReadTDCurTemperature(const QByteArray &data)
{
    Q_D(CCETestDataDevice);
    CCETestDataPackage_ReadTDCurTemperature pack(data);
    quint16 ret = pack.isValid();
    if(ret==CCEAPI::EResult::ER_Success){
        d->m_testData.TDCurTemperature = pack.getCurTemperature();
        qDebug()<<"Got it! TDCurTemperature:"<<d->m_testData.TDCurTemperature;
    }
    return ret;
}

quint16 CCETestDataDevice::onParseReadTICurTemperature(const QByteArray &data)
{
    Q_D(CCETestDataDevice);
    CCETestDataPackage_ReadTICurTemperature pack(data);
    quint16 ret = pack.isValid();
    if(ret==CCEAPI::EResult::ER_Success){
        d->m_testData.TICurTemperature = pack.getCurTemperature();
        qDebug()<<"Got it! TICurTemperature:"<<d->m_testData.TICurTemperature;
    }
    return ret;
}

quint16 CCETestDataDevice::onParseReadCurTestRunTime(const QByteArray &data)
{
    Q_D(CCETestDataDevice);
    CCETestDataPackage_ReadCurTestRunTime pack(data);
    quint16 ret = pack.isValid();
    if(ret==CCEAPI::EResult::ER_Success){
        d->m_testData.curTestRunTime = pack.getValue();
        qDebug()<<"Got it! COLUMNTemperature:"<<d->m_testData.COLUMNTemperature;
    }
    return ret;
}

quint16 CCETestDataDevice::onParseReadCOLUMNTemperature(const QByteArray &data)
{
    Q_D(CCETestDataDevice);
    CCETestDataPackage_ReadCOLUMNTemperature pack(data);
    quint16 ret = pack.isValid();
    if(ret==CCEAPI::EResult::ER_Success){
        d->m_testData.COLUMNTemperature = pack.getCurTemperature();
        qDebug()<<"Got it! COLUMNTemperature:"<<d->m_testData.COLUMNTemperature;
    }
    return ret;
}

quint16 CCETestDataDevice::onParseReadMicroPIDValue(const QByteArray &data)
{
    Q_D(CCETestDataDevice);
    CCETestDataPackage_ReadMicroPIDValue pack(data);
    quint16 ret = pack.isValid();
    if(ret==CCEAPI::EResult::ER_Success){
        d->m_testData.MicroPIDValue = pack.getValue();
        qDebug()<<"Got it! MicroPIDValue:"<<d->m_testData.MicroPIDValue;
    }
    return ret;
}

quint16 CCETestDataDevice::onParseReadAllInfo(const QByteArray &data)
{
    Q_D(CCETestDataDevice);
    CCETestDataPackage_ReadAllInfo pack(data);
    quint16 ret = pack.isValid();
    if(ret==CCEAPI::EResult::ER_Success){
        d->m_testData = pack.getInfo();
        qDebug()<<QString("Got it! TDCurTemper:%1,TICurTemper:%2,CurTestRunTime:%3,COLUMNTemper:%4,MicroPIDValue:%5.") \
                  .arg(d->m_testData.TDCurTemperature)\
                  .arg(d->m_testData.TICurTemperature)\
                  .arg(d->m_testData.curTestRunTime)\
                  .arg(d->m_testData.COLUMNTemperature)\
                  .arg(d->m_testData.MicroPIDValue);
    }
    return ret;
}

quint16 CCETestDataDevice::onParseReportAllInfo(const QByteArray &data)
{
    Q_D(CCETestDataDevice);
    CCETestDataPackage_ReportAllInfo pack(data);
    quint16 ret = pack.isValid();
    if(ret==CCEAPI::EResult::ER_Success){
        d->m_testData = pack.getInfo();
        qDebug()<<QString("Got it! TDCurTemper:%1,TICurTemper:%2,CurTestRunTime:%3,COLUMNTemper:%4,MicroPIDValue:%5.") \
                  .arg(d->m_testData.TDCurTemperature)\
                  .arg(d->m_testData.TICurTemperature)\
                  .arg(d->m_testData.curTestRunTime)\
                  .arg(d->m_testData.COLUMNTemperature)\
                  .arg(d->m_testData.MicroPIDValue);
    }

    CCETestDataPackage_ReportAllInfo packSend(ret);
    packSend.build();
    CCEEnginePackage enginePack;\
    if(enginePack.initByDetectInfo(d->m_deviceDetectInfo)){
        enginePack.setData(packSend.getDataToSend());
        CCEClusterProxy::asyncSend(enginePack);
    }
    return ret;
}
