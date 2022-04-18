#include "CCE_ChromXItem/CCEDetectServer.h"
#include "CCEAbstractModule_p.h"
#include <CCE_CommunicatEngine/CCECluster>

#include <QSerialPortInfo>

class CCEDetectServerPrivate : public CCEAbstractModulePrivate
{
public:
    CCEDetectServerPrivate(){}
    ~CCEDetectServerPrivate(){}

    //共享探卡信息
    SDetectItemInfo m_mainDeviceDetectInfo;
    SDetectItemInfo m_assistDeviceDetectInfo;
};

CCEDetectServer::CCEDetectServer(QObject *parent)
    : QObject{parent},d_ptr(new CCEDetectServerPrivate)
{
    connect(gCluster,&CCECluster::sig_NewCOMConnectionEstablish,this,&CCEDetectServer::slot_NewCOMConnectionEstablish);
}

CCEDetectServer::~CCEDetectServer()
{

}

bool CCEDetectServer::isConnect()
{
    if(!d_ptr->m_mainDeviceDetectInfo.socketObj){
        qDebug()<< "Main Ctrl Device Not Connect...";
        return false;
    }
    if(!d_ptr->m_assistDeviceDetectInfo.socketObj){
        qDebug()<< "Assist Ctrl Device Not Connect...";
        //return false;
    }
    return true;
}

void CCEDetectServer::autoConnect()
{
    prepareComDevice();
}

void CCEDetectServer::connectMainCOM(QString comName)
{
    gCluster->slot_ConnectToCOM(comName,quint64(EDeviceType::EDT_MainCOMDevice));
}

void CCEDetectServer::connectAssistCOM(QString comName)
{
    gCluster->slot_ConnectToCOM(comName,quint64(EDeviceType::EDT_AssistCOMDevice));
}

void CCEDetectServer::disConnectCOM(QString comName)
{
    if(d_ptr->m_mainDeviceDetectInfo.comInfo.comName==comName){
        gCluster->slot_Disconnect(d_ptr->m_mainDeviceDetectInfo.socketObj);
        d_ptr->m_mainDeviceDetectInfo.clear();
        emit sig_DeviceDisConnect();
        qDebug()<<"Disconnect Main Ctrl Device...";
        return;
    }
    if(d_ptr->m_assistDeviceDetectInfo.comInfo.comName==comName){
        gCluster->slot_Disconnect(d_ptr->m_assistDeviceDetectInfo.socketObj);
        d_ptr->m_assistDeviceDetectInfo.clear();
        emit sig_DeviceDisConnect();
        qDebug()<<"Disconnect Assist Ctrl Device...";
        return;
    }
}

void CCEDetectServer::disConnectAllCOM()
{
    gCluster->disconnectAllConnect();
    d_ptr->m_mainDeviceDetectInfo.clear();
    d_ptr->m_assistDeviceDetectInfo.clear();
    qDebug()<<"Disconnect All Ctrl Device...";
    emit sig_DeviceDisConnect();
}

SDetectItemInfo *CCEDetectServer::getMainDetectInfo()
{
    return &d_ptr->m_mainDeviceDetectInfo;
}

SDetectItemInfo *CCEDetectServer::getAssistDetectInfo()
{
    return &d_ptr->m_assistDeviceDetectInfo;
}

void CCEDetectServer::slot_NewCOMConnectionEstablish(QObject *objSocket, QString comName, quint64 extraData)
{
    Q_ASSERT(objSocket);
    if(EDeviceType::EDT_MainCOMDevice==EDeviceType(extraData)){
        d_ptr->m_mainDeviceDetectInfo.deviceType = EDeviceType(extraData);
        d_ptr->m_mainDeviceDetectInfo.detectType = EDeviceDetectType::EDDT_Manual;
        d_ptr->m_mainDeviceDetectInfo.communType = ECommunicatType::ECT_COM;
        d_ptr->m_mainDeviceDetectInfo.deviceStatus = EDeviceStatus::EDS_Online;
        d_ptr->m_mainDeviceDetectInfo.socketObj = objSocket;
        d_ptr->m_mainDeviceDetectInfo.comInfo.comName = comName;
    }
    else if(EDeviceType::EDT_AssistCOMDevice==EDeviceType(extraData)){
        d_ptr->m_assistDeviceDetectInfo.deviceType = EDeviceType(extraData);
        d_ptr->m_assistDeviceDetectInfo.detectType = EDeviceDetectType::EDDT_Manual;
        d_ptr->m_assistDeviceDetectInfo.communType = ECommunicatType::ECT_COM;
        d_ptr->m_assistDeviceDetectInfo.deviceStatus = EDeviceStatus::EDS_Online;
        d_ptr->m_assistDeviceDetectInfo.socketObj = objSocket;
        d_ptr->m_assistDeviceDetectInfo.comInfo.comName = comName;
    }

    if(d_ptr->m_mainDeviceDetectInfo.socketObj/*&&d_ptr->m_assistDeviceDetectInfo.socketObj*/){
        emit sig_DeviceConnect();
    }
}

void CCEDetectServer::prepareComDevice()
{
    //判断连接主串口
    QStringList mainPortDescriptionList;
    mainPortDescriptionList.append(QStringLiteral("USB 串行设备"));

    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        if (mainPortDescriptionList.contains(info.description()))
        {
            qDebug() << "Find serialPortName:" << info.portName();
            connectMainCOM(info.portName());
        }
    }

    //判断连接辅助串口
    QStringList assistPortDescriptionList;
    assistPortDescriptionList.append("Silicon Labs CP210x USB to UART Bridge");

    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        if (assistPortDescriptionList.contains(info.description()))
        {
            qDebug() << " Find serialPortName:" << info.portName();
            connectAssistCOM(info.portName());
        }
    }
}
