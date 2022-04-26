#include "CCE_ChromXItem/CCETestParamSetDevice.h"
#include "CCEAbstractModule_p.h"
#include <CCE_CommunicatEngine/CCEClusterProxy>

static const int g_singlePackLength = 212;

class CCETestParamSetDevicePrivate : public CCEAbstractModulePrivate
{
    Q_DECLARE_PUBLIC(CCETestParamSetDevice)
public:
    CCETestParamSetDevicePrivate(){}
    ~CCETestParamSetDevicePrivate(){}

    STestParamSet m_testParamSet;
    bool m_runParamAsyncReadComplete = false;
};


CCETestParamSetDevice::CCETestParamSetDevice(QObject *parent)
    : CCEAbstractModule{*new CCETestParamSetDevicePrivate, parent}
{

}

CCETestParamSetDevice::~CCETestParamSetDevice()
{

}

quint16 CCETestParamSetDevice::writePIDAll(const SPIDAll &data, bool sync, int msec)
{
    //内部自动大小端转换
    CCETestParamSetPackage_WriteAllPID pack(data);
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

quint16 CCETestParamSetDevice::readPIDAll(bool sync, int msec)
{
    CCETestParamSetPackage_ReadAllPID pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

SPIDAll &CCETestParamSetDevice::getPIDAll()
{
    Q_D(CCETestParamSetDevice);
    return d->m_testParamSet.PIDAll;
}

quint16 CCETestParamSetDevice::writeRunParam(const SRunParamSet &data, bool sync, int msec)
{
    Q_D(CCETestParamSetDevice);
    //赋值给临时变量并转换大小端
    SRunParamSet tempData= data;
    tempData.bigLittleSwap();

    //计算包个数
    int packageCount = sizeof(SRunParamSet)/g_singlePackLength;
    if (0 != sizeof(SRunParamSet)%g_singlePackLength)
        packageCount += 1;

    for(int i = 0;i<packageCount;++i){
        //计算便宜与下发数据
        int offsetPos = g_singlePackLength*i;
        QByteArray writeData = QByteArray((char*)&tempData+offsetPos,(i == packageCount - 1)?(sizeof(SRunParamSet) - offsetPos):g_singlePackLength);

        CCETestParamSetPackage_WriteRunParam pack(offsetPos,writeData);
        pack.build();

        CCEEnginePackage enginePack;\
        if(!enginePack.initByDetectInfo(d->m_deviceDetectInfo)){\
            return CCEAPI::EResult::ER_Fail;\
        }\
        enginePack.setData(pack.getDataToSend());\
        if (sync) {\
            CCEEnginePackage recEnginePack;\
            quint16 ret = CCEClusterProxy::syncSend(enginePack, recEnginePack, msec);\
            if(ret!=CCEAPI::EResult::ER_Success){ \
                return ret; \
            } \
            ret = d->m_packageMgr.handle(CCEPackage(recEnginePack.data()));
            if(CCEAPI::EResult::ER_Success != ret){
                return ret;
            }
        }\
        else {\
            if(!CCEClusterProxy::asyncSend(enginePack)){
                return CCEAPI::EResult::ER_Fail;
            }
        }\
    }
    d->m_testParamSet.runParamSet = data;
    qDebug()<<QString("Got it! Write RunParam:%1.").arg(CCEUIHelper::byteArrayToHexStr(QByteArray((char*)&d->m_testParamSet.runParamSet,sizeof(SRunParamSet))));
    return CCEAPI::EResult::ER_Success;
}

quint16 CCETestParamSetDevice::readRunParam(bool sync, int msec)
{
    Q_D(CCETestParamSetDevice);

    int packageCount = sizeof(SRunParamSet)/g_singlePackLength;
    if (0 != sizeof(SRunParamSet)%g_singlePackLength)
        packageCount += 1;

    for(int i = 0;i<packageCount;++i){
        int offsetPos = g_singlePackLength*i;
        int tempReadLength = (i == packageCount - 1)?(sizeof(SRunParamSet) - offsetPos):g_singlePackLength;
        CCETestParamSetPackage_ReadRunParam pack(offsetPos,tempReadLength);
        pack.build();

        CCEEnginePackage enginePack;\
        if(!enginePack.initByDetectInfo(d->m_deviceDetectInfo)){\
            return CCEAPI::EResult::ER_Fail;\
        }\
        enginePack.setData(pack.getDataToSend());\
        if (sync) {\
            CCEEnginePackage recEnginePack;\
            quint16 ret = CCEClusterProxy::syncSend(enginePack, recEnginePack, msec);\
            if(ret!=CCEAPI::EResult::ER_Success){ \
                return ret; \
            } \
            ret = d->m_packageMgr.handle(CCEPackage(recEnginePack.data()));
            if(CCEAPI::EResult::ER_Success != ret){
                return ret;
            }
            //memcpy(&d->m_testParamSet.runParamSet + offsetPos,recEnginePack.data().data(),tempReadLength);
        }\
        else {\
            if(!CCEClusterProxy::asyncSend(enginePack)){
                return CCEAPI::EResult::ER_Fail;
            }
        }\
    }
    if(sync){
        d->m_testParamSet.runParamSet.bigLittleSwap();
        qDebug()<<QString("Got it! Read RunParam:%1.").arg(CCEUIHelper::byteArrayToHexStr(QByteArray((char*)&d->m_testParamSet.runParamSet,sizeof(SRunParamSet))));
    }
    else{
        d->m_runParamAsyncReadComplete = true;
    }
    return CCEAPI::EResult::ER_Success;
}

SRunParamSet &CCETestParamSetDevice::getRunParam()
{
    Q_D(CCETestParamSetDevice);
    return d->m_testParamSet.runParamSet;
}

quint16 CCETestParamSetDevice::writeTestStatus(quint8 value, bool sync, int msec)
{
    CCETestParamSetPackage_WriteTestStatus pack(value);
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

quint16 CCETestParamSetDevice::readTestStatus(bool sync, int msec)
{
    CCETestParamSetPackage_ReadTestStatus pack;
    pack.build();

    CCE_DECLARE_COMMANDSEND(d_ptr,pack);
}

quint8 CCETestParamSetDevice::getTestStatus()
{
    Q_D(CCETestParamSetDevice);
    return d->m_testParamSet.testStatus;
}

void CCETestParamSetDevice::registerCallBack()
{
    Q_D(CCETestParamSetDevice);
    d->m_packageMgr.registerPackage(CCETestParamSetPackage_WriteAllPID(),
                                        std::bind(&CCETestParamSetDevice::onParseWriteAllPID,this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCETestParamSetPackage_ReadAllPID(),
                                        std::bind(&CCETestParamSetDevice::onParseReadAllPID,this,std::placeholders::_1));

    d->m_packageMgr.registerPackage(CCETestParamSetPackage_WriteRunParam(),
                                        std::bind(&CCETestParamSetDevice::onParseWriteRunParam,this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCETestParamSetPackage_WriteRunParam(g_singlePackLength,QByteArray()),
                                        std::bind(&CCETestParamSetDevice::onParseWriteRunParam,this,std::placeholders::_1));

    d->m_packageMgr.registerPackage(CCETestParamSetPackage_ReadRunParam(),
                                        std::bind(&CCETestParamSetDevice::onParseReadRunParam,this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCETestParamSetPackage_ReadRunParam(g_singlePackLength,0),
                                        std::bind(&CCETestParamSetDevice::onParseReadRunParam,this,std::placeholders::_1));

    d->m_packageMgr.registerPackage(CCETestParamSetPackage_WriteTestStatus(),
                                        std::bind(&CCETestParamSetDevice::onParseWriteTestStatus,this,std::placeholders::_1));
    d->m_packageMgr.registerPackage(CCETestParamSetPackage_ReadTestStatus(),
                                        std::bind(&CCETestParamSetDevice::onParseReadTestStatus,this,std::placeholders::_1));
}

quint16 CCETestParamSetDevice::onParseWriteAllPID(const QByteArray &data)
{
    CCETestParamSetPackage_WriteAllPID pack(data);
    DO_RETOPERATIONRESULT(pack);
}

quint16 CCETestParamSetDevice::onParseReadAllPID(const QByteArray &data)
{
    Q_D(CCETestParamSetDevice);
    CCETestParamSetPackage_ReadAllPID pack(data);
    quint16 ret = pack.isValid();
    if(ret==CCEAPI::EResult::ER_Success){
        d->m_testParamSet.PIDAll = pack.getValue();
        qDebug()<<QString("Got it! TD PID:%1,%2,%3\n TD PID:%4,%5,%6\n COLUMN PID:%7,%8,%9.") \
                  .arg(d->m_testParamSet.PIDAll.TD_PID_P_Parma).arg(d->m_testParamSet.PIDAll.TD_PID_I_Parma).arg(d->m_testParamSet.PIDAll.TD_PID_D_Parma)\
                  .arg(d->m_testParamSet.PIDAll.TI_PID_P_Parma).arg(d->m_testParamSet.PIDAll.TI_PID_I_Parma).arg(d->m_testParamSet.PIDAll.TI_PID_D_Parma)\
                  .arg(d->m_testParamSet.PIDAll.COLUMN_PID_P_Parma).arg(d->m_testParamSet.PIDAll.COLUMN_PID_I_Parma).arg(d->m_testParamSet.PIDAll.COLUMN_PID_D_Parma);
    }
    return ret;
}

quint16 CCETestParamSetDevice::onParseWriteRunParam(const QByteArray &data)
{
    CCETestParamSetPackage_WriteRunParam pack(data);
    quint16 ret = pack.isValid(); \
    if(ret==CCEAPI::EResult::ER_Success){\
        ret = pack.getOperationResult(); \
    } \
    else if(ret==CCEAPI::EResult::ER_CtrlAddrErr){
        CCETestParamSetPackage_WriteRunParam pack(data,g_singlePackLength);
        ret = pack.isValid(); \
        if(ret==CCEAPI::EResult::ER_Success){\
            ret = pack.getOperationResult(); \
        } \
    }
    return ret; \
}

quint16 CCETestParamSetDevice::onParseReadRunParam(const QByteArray &data)
{
    Q_D(CCETestParamSetDevice);
    //此处不做解析，在读取函数中判断解析函数的返回值，并拷贝数据
    CCETestParamSetPackage_ReadRunParam pack(data);
    quint16 ret = pack.isValid();
    if(ret==CCEAPI::EResult::ER_Success){
        quint16 addr = pack.getCtrlAddr();
        QByteArray content = pack.getContent();
        int offsetPos = addr - CCETestParamSetPackage_ReadRunParam::EC_Read_COLUMNFanCloseTemperature;
        if(offsetPos<0){
            qDebug()<<"Got it! But RunParam Address has Problem.";
        }
        memcpy(&d->m_testParamSet.runParamSet + offsetPos,content,content.size());
        //qDebug()<<QString("Got it! RunParam Single Package.").arg(CCEUIHelper::byteArrayToHexStr(content));
        if(d->m_runParamAsyncReadComplete){
            d->m_runParamAsyncReadComplete = false;
            d->m_testParamSet.runParamSet.bigLittleSwap();
            qDebug()<<QString("Got it! Read RunParam:%1.").arg(CCEUIHelper::byteArrayToHexStr(QByteArray((char*)&d->m_testParamSet.runParamSet,sizeof(SRunParamSet))));
        }
    }
    else if(ret==CCEAPI::EResult::ER_CtrlAddrErr){
        CCETestParamSetPackage_ReadRunParam pack(g_singlePackLength,data);
        ret = pack.isValid();
        if(ret==CCEAPI::EResult::ER_Success){
            quint16 addr = pack.getCtrlAddr();
            QByteArray content = pack.getContent();
            int offsetPos = addr - CCETestParamSetPackage_ReadRunParam::EC_Read_COLUMNFanCloseTemperature;
            if(offsetPos<0){
                qDebug()<<"Got it! But RunParam Address has Problem.";
            }
            memcpy(&d->m_testParamSet.runParamSet + offsetPos,content,content.size());
            //qDebug()<<QString("Got it! Read RunParam Single Package.").arg(CCEUIHelper::byteArrayToHexStr(content));
            if(d->m_runParamAsyncReadComplete){
                d->m_runParamAsyncReadComplete = false;
                d->m_testParamSet.runParamSet.bigLittleSwap();
                qDebug()<<QString("Got it! Read RunParam:%1.").arg(CCEUIHelper::byteArrayToHexStr(QByteArray((char*)&d->m_testParamSet.runParamSet,sizeof(SRunParamSet))));
            }
        }
    }
    return ret;
}

quint16 CCETestParamSetDevice::onParseWriteTestStatus(const QByteArray &data)
{
    CCETestParamSetPackage_WriteTestStatus pack(data);
    DO_RETOPERATIONRESULT(pack);
}

quint16 CCETestParamSetDevice::onParseReadTestStatus(const QByteArray &data)
{
    Q_D(CCETestParamSetDevice);
    CCETestParamSetPackage_ReadTestStatus pack(data);
    quint16 ret = pack.isValid();
    if(ret==CCEAPI::EResult::ER_Success){
        d->m_testParamSet.testStatus = pack.getValue();
        qDebug()<<"Got it! testStatus:"<<d->m_testParamSet.testStatus;
    }
    return ret;
}
