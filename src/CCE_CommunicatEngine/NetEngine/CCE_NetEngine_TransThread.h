#ifndef CVTE_H_CCE_NETENGINE_TRANSTHREAD
#define CVTE_H_CCE_NETENGINE_TRANSTHREAD
#pragma once

#include "CCE_CommunicatEngine/CCEEnginePackage.h"

#include <QObject>
#include <QList>
#include <QAbstractSocket>
#include <QSerialPort>
#include <QMutex>
#include <QHash>
#include <QSet>
#include <unordered_map>

class CCE_NetEngine;
class CCE_NetEngine_TransThread : public QObject
{
    Q_OBJECT

public:
    explicit CCE_NetEngine_TransThread(CCE_NetEngine* pThreadEngine, int nPayLoad = 4096, QObject *parent = 0);
    virtual ~CCE_NetEngine_TransThread();
    QList<QObject*> clientsList();
    int currentClients();
    void setPayLoad(int nPayLoad);
    bool isActive();
    bool canExit();
    void emptyRabbishCan();
    ECommunicatType transThreadType();
protected:
    void  push_to_rabbish_can(QObject* deleteObjSocket);
    //socket终止后响应
    virtual void closeSocket(QObject* objSocket);

public slots:
    /******************************Engine信号响应槽函数********************************/
    //建立连接
    virtual void slot_EstablishUDPConnection(CCE_NetEngine_TransThread* threadid, const QString& addr, quint16 port);
    virtual void slot_EstablishCOMConnection(CCE_NetEngine_TransThread* threadid, QString comName);
    //发送数据
    virtual void slot_SendData(QObject* objSocket, CCEEnginePackage);
    //设置为不活动
    void slot_Deactivate();
    //立刻设置为不活动，断开所有连接
    void slot_DeactivateImmediately(CCE_NetEngine_TransThread* threadid);
    //断开所有连接
    void slot_DisconnectAll(CCE_NetEngine_TransThread* threadid);
    //断开某个连接
    void slot_Disconnect(QObject* objSocket);

    /******************************内部响应槽函数********************************/
protected slots:
    //socket收到数据后响应
    virtual void slot_New_Data_Recieved();
    //socket发送数据后响应
    virtual void slot_Some_Data_Sended(qint64);
    //socket发生错误后响应
    virtual void slot_DisplayError(QAbstractSocket::SocketError socketError);
    virtual void slot_DisplayError(QSerialPort::SerialPortError serialError);

signals:
    /******************************发往Engine信号********************************/
    //向Engine发送消息信号
    void sig_Message(QObject* objSocket, QString);
    //向Engine设备socket错误信息信号
    void sig_SocketError(QObject* objSocket, QAbstractSocket::SocketError socketError);
    void sig_SocketError(QObject* objSocket, QSerialPort::SerialPortError serialError);
    //向Engine发送socket终止信号
    void sig_SocketClosed(QObject* objSocket);
    //向Engine发送收到数据信号
    void sig_Data_Received(QObject* objSocket, CCEEnginePackage);
    //向Engine发送发送数据信号
    void sig_Data_Sended(QObject* objSocket, qint64);
    //向Engine发送连接建立的信号
    void sig_NewUDPConnectionEstablish(QObject* objSocket, const QString& addr, quint16 port);
    void sig_NewCOMConnectionEstablish(QObject* objSocket, QString comName);

protected:
    static int RUBBISH_CAN_SIZE;
    bool m_bActivated;
    //sending buffer
    std::unordered_map<QObject*, QList<CCEEnginePackage>> m_buffer_sending;
    std::unordered_map<QObject*, QList<qint64>> m_buffer_sending_offset;
    //The socket and the connection-direction
    QSet<QObject*> m_clientList;
    int m_nPayLoad;
    QMutex m_mutex_protect;
    CCE_NetEngine* m_pThreadPool;
    //Rabbish Can
    QList<QObject*> m_rabbish_can;
    QSet<QObject*> m_set_rabbish_can;
    QMutex m_mutex_rabbish_can;

    ECommunicatType m_communicatType = ECommunicatType::ECT_NULL;
};
#endif
