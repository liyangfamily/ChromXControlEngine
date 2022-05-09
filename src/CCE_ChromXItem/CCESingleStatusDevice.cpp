#include "CCE_ChromXItem/CCESingleStatusDevice.h"
#include "CCEAbstractModule_p.h"
#include <CCE_CommunicatEngine/CCEClusterProxy>

class CCESingleStatusDevicePrivate : public CCEAbstractModulePrivate
{
    Q_DECLARE_PUBLIC(CCESingleStatusDevice)
public:
    CCESingleStatusDevicePrivate(){}
    ~CCESingleStatusDevicePrivate(){}

    SSingleStatus m_singleStatus;
};


CCESingleStatusDevice::CCESingleStatusDevice(QObject *parent)
    : CCEAbstractModule{*new CCESingleStatusDevicePrivate, parent}
{

}

CCESingleStatusDevice::~CCESingleStatusDevice()
{

}

quint16 CCESingleStatusDevice::readTDCurTemperature(bool sync, int msec)
{
    CCESingleStatusPackage_ReadTDCurTemperature pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

quint16 CCESingleStatusDevice::getTDCurTemperature()
{
    Q_D(CCESingleStatusDevice);
    return d->m_singleStatus.TDCurTemperature;
}

quint16 CCESingleStatusDevice::readTICurTemperature(bool sync, int msec)
{
    CCESingleStatusPackage_ReadTICurTemperature pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

quint16 CCESingleStatusDevice::getTICurTemperature()
{
    Q_D(CCESingleStatusDevice);
    return d->m_singleStatus.TICurTemperature;
}

quint16 CCESingleStatusDevice::readCOLUMNTemperature(bool sync, int msec)
{
    CCESingleStatusPackage_ReadCOLUMNTemperature pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

quint16 CCESingleStatusDevice::getCOLUMNTemperature()
{
    Q_D(CCESingleStatusDevice);
    return d->m_singleStatus.COLUMNTemperature;
}

quint16 CCESingleStatusDevice::readMicroPIDValue(bool sync, int msec)
{
    CCESingleStatusPackage_ReadMicroPIDValue pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

quint16 CCESingleStatusDevice::getMicroPIDValue()
{
    Q_D(CCESingleStatusDevice);
    return d->m_singleStatus.MicroPIDValue;
}

quint16 CCESingleStatusDevice::readEPCPressure(bool sync, int msec)
{
    CCESingleStatusPackage_ReadEPCPressure pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

quint16 CCESingleStatusDevice::getEPCPressure()
{
    Q_D(CCESingleStatusDevice);
    return d->m_singleStatus.EPCPressure;
}

quint16 CCESingleStatusDevice::readAllInfo(bool sync, int msec)
{
    CCESingleStatusPackage_ReadAllInfo pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

SSingleStatus CCESingleStatusDevice::getAllInfo()
{
    Q_D(CCESingleStatusDevice);
    return d->m_singleStatus;
}

void CCESingleStatusDevice::registerCallBack()
{
    Q_D(CCESingleStatusDevice);
    d->m_packageMgr.registerPackage(CCESingleStatusPackage_ReadTDCurTemperature(),
                                        std::bind(&CCESingleStatusDevice::onParseReadTDCurTemperature,this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCESingleStatusPackage_ReadTICurTemperature(),
                                        std::bind(&CCESingleStatusDevice::onParseReadTICurTemperature,this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCESingleStatusPackage_ReadCOLUMNTemperature(),
                                        std::bind(&CCESingleStatusDevice::onParseReadCOLUMNTemperature,this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCESingleStatusPackage_ReadMicroPIDValue(),
                                        std::bind(&CCESingleStatusDevice::onParseReadMicroPIDValue,this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCESingleStatusPackage_ReadEPCPressure(),
                                    std::bind(&CCESingleStatusDevice::onParseReadEPCPressure,this,std::placeholders::_1));
//    d->m_packageMgr.registerPackage(CCESingleStatusPackage_ReadAllInfo(),
//                                    std::bind(&CCESingleStatusDevice::onParseReadAllInfo,this,std::placeholders::_1));
}

quint16 CCESingleStatusDevice::onParseReadTDCurTemperature(const QByteArray &data)
{
    Q_D(CCESingleStatusDevice);
    CCESingleStatusPackage_ReadTDCurTemperature pack(data);
    quint16 ret = pack.isValid();
    if(ret==CCEAPI::EResult::ER_Success){
        d->m_singleStatus.TDCurTemperature = pack.getCurTemperature();
        qDebug()<<"Got it! TDCurTemperature:"<<d->m_singleStatus.TDCurTemperature;
    }
    return ret;
}

quint16 CCESingleStatusDevice::onParseReadTICurTemperature(const QByteArray &data)
{
    Q_D(CCESingleStatusDevice);
    CCESingleStatusPackage_ReadTICurTemperature pack(data);
    quint16 ret = pack.isValid();
    if(ret==CCEAPI::EResult::ER_Success){
        d->m_singleStatus.TICurTemperature = pack.getCurTemperature();
        qDebug()<<"Got it! TICurTemperature:"<<d->m_singleStatus.TICurTemperature;
    }
    return ret;
}

quint16 CCESingleStatusDevice::onParseReadCOLUMNTemperature(const QByteArray &data)
{
    Q_D(CCESingleStatusDevice);
    CCESingleStatusPackage_ReadCOLUMNTemperature pack(data);
    quint16 ret = pack.isValid();
    if(ret==CCEAPI::EResult::ER_Success){
        d->m_singleStatus.COLUMNTemperature = pack.getCurTemperature();
        qDebug()<<"Got it! COLUMNTemperature:"<<d->m_singleStatus.COLUMNTemperature;
    }
    return ret;
}

quint16 CCESingleStatusDevice::onParseReadMicroPIDValue(const QByteArray &data)
{
    Q_D(CCESingleStatusDevice);
    CCESingleStatusPackage_ReadMicroPIDValue pack(data);
    quint16 ret = pack.isValid();
    if(ret==CCEAPI::EResult::ER_Success){
        d->m_singleStatus.MicroPIDValue = pack.getValue();
        qDebug()<<"Got it! MicroPIDValue:"<<d->m_singleStatus.MicroPIDValue;
    }
    return ret;
}

quint16 CCESingleStatusDevice::onParseReadEPCPressure(const QByteArray &data)
{
    Q_D(CCESingleStatusDevice);
    CCESingleStatusPackage_ReadEPCPressure pack(data);
    quint16 ret = pack.isValid();
    if(ret==CCEAPI::EResult::ER_Success){
        d->m_singleStatus.EPCPressure = pack.getValue();
        qDebug()<<"Got it! EPCPressure:"<<d->m_singleStatus.EPCPressure;
    }
    return ret;
}

quint16 CCESingleStatusDevice::onParseReadAllInfo(const QByteArray &data)
{
    Q_D(CCESingleStatusDevice);
    CCESingleStatusPackage_ReadAllInfo pack(data);
    quint16 ret = pack.isValid();
    if(ret==CCEAPI::EResult::ER_Success){
        d->m_singleStatus = pack.getInfo();
        qDebug()<<QString("Got it! TDCurTemper:%1,TICurTemper:%2,COLUMNTemper:%3,MicroPIDValue:%4,EPCPressure:%5.") \
                  .arg(d->m_singleStatus.TDCurTemperature)\
                  .arg(d->m_singleStatus.TICurTemperature)\
                  .arg(d->m_singleStatus.COLUMNTemperature)\
                  .arg(d->m_singleStatus.MicroPIDValue)\
                  .arg(d->m_singleStatus.EPCPressure);
    }
    return ret;
}
