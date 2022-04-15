#include "CCE_ChromXItem/CCEDetectServer.h"
#include <CCE_CommunicatEngine/CCECluster>

#include <QSerialPortInfo>

class CCEDetectServerPrivate
{
public:
    CCEDetectServerPrivate(){}
    CCEDetectServer* q_ptr = nullptr;

    //储存连个串口额信息
    QPair<QObject*,QString> m_mainCOM;
    QPair<QObject*,QString> m_assistCOM;
};

CCEDetectServer::CCEDetectServer(QObject *parent)
    : QObject{parent},d_ptr(new CCEDetectServerPrivate)
{
    d_ptr->q_ptr = this;
    connect(gCluster,&CCECluster::sig_NewCOMConnectionEstablish,this,[this](QObject* objSocket, QString comName){
        if(d_ptr->m_mainCOM.second==comName){
            d_ptr->m_mainCOM.first = objSocket;
            qDebug()<<d_ptr->m_mainCOM;
        }
        if(d_ptr->m_assistCOM.second==comName){
            d_ptr->m_assistCOM.first = objSocket;
            qDebug()<<d_ptr->m_assistCOM;
        }
        if(d_ptr->m_mainCOM.first/*&&d_ptr->m_assistCOM.first*/){
            emit sig_DeviceConnect();
        }
    });
}

CCEDetectServer::~CCEDetectServer()
{

}

bool CCEDetectServer::isConnect()
{
    if(!d_ptr->m_mainCOM.first){
        qDebug()<< "Main Ctrl Device Not Connect...";
        return false;
    }
    if(!d_ptr->m_assistCOM.first){
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
    if(gCluster->slot_ConnectToCOM(comName)){
        d_ptr->m_mainCOM.second = comName;
    }
}

void CCEDetectServer::connectAssistCOM(QString comName)
{
    if(gCluster->slot_ConnectToCOM(comName)){
        d_ptr->m_assistCOM.second = comName;
    }
}

void CCEDetectServer::disConnectCOM(QString comName)
{
    if(d_ptr->m_mainCOM.second==comName){
        gCluster->slot_Disconnect(d_ptr->m_mainCOM.first);
        emit sig_DeviceDisConnect();
        return;
    }
    if(d_ptr->m_assistCOM.second==comName){
        gCluster->slot_Disconnect(d_ptr->m_assistCOM.first);
        emit sig_DeviceDisConnect();
        return;
    }
}

void CCEDetectServer::disConnectAllCOM()
{
    gCluster->disconnectAllConnect();
    emit sig_DeviceDisConnect();
}

QObject *CCEDetectServer::mainCOMSocket()
{
    if(isConnect()){
        return d_ptr->m_mainCOM.first;
    }
    return nullptr;
}

QObject *CCEDetectServer::assistCOMSocket()
{
    if(isConnect()){
        return d_ptr->m_assistCOM.first;
    }
    return nullptr;
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
