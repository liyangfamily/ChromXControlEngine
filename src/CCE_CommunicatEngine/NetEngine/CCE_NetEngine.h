#ifndef CVTE_H_CCE_NETENGINE
#define CVTE_H_CCE_NETENGINE
#pragma once

#include <CCE_CommunicatEngine/CCEEnginePackage>

#include <QObject>
#include <QThread>
#include <QHostAddress>
#include <QScopedPointer>
#include <QAbstractSocket>
#include <QSerialPort>
#include <QUuid>

class CCE_NetEngine_TransThread;
class CCE_NetEngine : public QObject
{
    Q_OBJECT
public:
    explicit CCE_NetEngine(int nPayLoad = 4096, QObject *parent = 0);
    ~CCE_NetEngine();

    void creatTransThreads(int nThreads);
    void removeTransThreads(int nThreads);
    //断开所有
    void disconnectAll();
    //立刻设置为不活动
    void deactiveImmediately();
    //when Program exit, wait for close; use this funcion after use kickallCliens();deacticeImmediately();
    bool canExit();

protected:
    //删除某个传输线程
    bool transThreadDelete(CCE_NetEngine_TransThread* threadid);
private:
    void creatUDPTransThreads(int nThreads);
    void creatCOMTransThreads(int nThreads);
signals:
    /*********************************发往外部信号**********************************/
    //向外部发送消息信号
    void sig_Message(QObject * objSocket, QString);
    //向外部设备socket错误信息信号
    void sig_SocketError(QObject * objSocket, QAbstractSocket::SocketError socketError);
    void sig_SocketError(QObject * objSocket, QSerialPort::SerialPortError serialError);
    //向外部发送socket终止信号
    void sig_SocketAbort(QObject* objSocket);
    //向外部发送收到数据信号
    void sig_Data_Received(QObject* objSocket, CCEEnginePackage);
    //向外部发送发送数据信号
    void sig_Data_Sended(QObject* objSocket, qint64);
    //向外部发送连接建立的信号，信号内容会被替换为结构体
    void sig_NewUDPConnectionEstablish(QObject* objSocket, const QString& addr, quint16 port,quint64 extraData);
    void sig_NewCOMConnectionEstablish(QObject* objSocket, QString comName,quint64 extraData);

    /*********************************发往TransThread信号**********************************/
    //向TransThread发送建立连接信号
    void sig_EstablishUDPConnection(CCE_NetEngine_TransThread* threadid, const QString& addr, quint16 port,quint64 extraData);
    void sig_EstablishCOMConnection(CCE_NetEngine_TransThread* threadid, QString comName,quint64 extraData);
    //向TransThread发送数据
    void sig_SendData(QObject * objSocket, CCEEnginePackage);
    //向TransThread发送断开连接信号
    void sig_Disconnect(QObject* objSocket); //通知某个socket剔除它的的连接
    //向TransThread发送断开所有连接信号
    void sig_DisconnectAll(CCE_NetEngine_TransThread* threadid);
    //向TransThread发送立即设置为不活动且断块所有连接信号
    void sig_DeactivteImmediately(CCE_NetEngine_TransThread* threadid);

public slots:
    /******************************外部信号响应槽函数********************************/
    //发送数据
    void slot_SendData(QObject * objSocket, CCEEnginePackage);
    //断开某个连接
    void slot_Disconnect(QObject * objSocket);
    //与目标建立连接
    bool slot_ConnectToUDP(const QString & address, quint16 nPort,quint64 extraData);
    bool slot_ConnectToCOM(QString comName,quint64 extraData);
protected:
    int m_nThread = 2;
    int m_nPayLoad;
    QVector<CCE_NetEngine_TransThread*> m_vec_TransThreads;
    QVector<QThread*> m_vec_InternalTransThreads;
};
#endif
