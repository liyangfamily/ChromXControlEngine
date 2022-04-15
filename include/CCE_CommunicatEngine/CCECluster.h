/*********************************************************************************************************
** This file is part of the CCE_CommunicatEngine module of the CCE Toolkit.
*********************************************************************************************************/
#ifndef CVTE_H_CCE_CLUSTER
#define CVTE_H_CCE_CLUSTER
#pragma once

#include <CCE_CommunicatEngine/CCEEnginePackage>

#include <QObject>
#include <QList>
#include <QMap>
#include <QMutex>
#include <QUuid>
#include <QtNetwork/QAbstractSocket>
#include <QtSerialPort/QSerialPort>

#define gCluster CCECluster::instance()

class CCE_NetEngine;
class CCE_TaskEngine;
class CCE_TaskEngine_TaskBase;
class CCE_COMMUNICATENGINE_EXPORT CCECluster : public QObject
{
    Q_OBJECT

    friend class CCEDetectServer;
    friend class CCEClusterProxy;
public:
    CCECluster(QObject *parent = 0);
    ~CCECluster();

    static CCECluster *instance();

    //cluster status
    CCE_NetEngine * netEngine();
    CCE_TaskEngine * taskEngine();

    int heartBeatingThrdHold();
    void setHeartBeatingThrd(const int n);

    bool isSocketInExclusive(QObject* objSocket);
    QUuid exclusiveKey(QObject* objSocket);

    void readyToExit();
    bool canExit();

    void disconnectAllConnect();
protected:
    int m_nHeartBeatingTime;  //s
    CCE_NetEngine * m_pNetEngine;
    CCE_TaskEngine * m_pTaskEngine;
    //This list hold dead nodes that still in task queue,avoiding crash
    QList<CCE_TaskEngine_TaskBase *> m_nodeToBeDel;
    //十分重要. server name to socket, socket to server name
    QMutex m_hash_mutex;
    QMap<QString, CCE_TaskEngine_TaskBase *> m_hash_Name2node;
    QMap<QObject *, CCE_TaskEngine_TaskBase *> m_hash_sock2node;

    //独占模式相关
    QMap<QObject *, QUuid> m_hash_sockExclusive;
    QMutex m_mutex_ExclusiveLock;
signals:
    /*********************************发往外部信号**********************************/
    //向外部发送消息信号
    void sig_Message(QObject * objSocket, QString);
    //向外部设备socket错误信息信号
    void sig_SocketError(QObject * objSocket, QAbstractSocket::SocketError socketError);
    void sig_SocketError(QObject * objSocket, QSerialPort::SerialPortError serialError);
    //向外部发送socket终止信号
    void sig_SocketAbort(QObject* objSocket);
    //向外部发送发送数据信号
    void sig_Data_Sended(QObject* objSocket, qint64);
    //向外部发送连接建立的信号，信号内容会被替换为结构体
    void sig_NewUDPConnectionEstablish(QObject* objSocket, const QString& addr, quint16 port);
    void sig_NewCOMConnectionEstablish(QObject* objSocket, QString comName);
    //向外部发送Cluster发送的数据
    void sig_SendedDataSteam(QObject *psource, CCEEnginePackage dataSteam);
    //向外部发送Task解析到的数据帧
    void sig_ParsingInteCtrlDataFrame(QObject *psource, CCEEnginePackage dataFrame);
    //向外部发送独占结果信号
    void sig_ExlusiveLocked(QObject * objSocket, bool bStatus, QUuid uuid);

protected slots:
    /******************************内部信号响应槽函数********************************/
    //收到NetEngine发送的连接断开信号
    void slot_SocketAbort(QObject * /*clientHandle*/);
    //收到NetEngine发送的收到数据信号
    void slot_Data_Received(QObject *  /*clientHandle*/, CCEEnginePackage  /*datablock*/);
    //收到NetEngine发送的数据发送信号
    void slot_Data_Sended(QObject *   /*clientHandle*/, qint64 /*bytes sent*/);
    //收到NetEngine发送的新连接建立信号
    void slot_NewUDPConnectionEstablish(QObject* /*clientHandle*/, const QString& addr, quint16 port);
    void slot_NewCOMConnectionEstablish(QObject* /*clientHandle*/, QString comName);

public slots:
    //剔除僵尸客户端
    void slot_KickDeadClients();
    //socket设置独占模式
    void slot_SetSocketExlusive(QObject* objSocket, bool enable);

protected slots :
    /******************************外部信号响应槽函数********************************/
    //发送数据
    bool slot_SendData(QObject * objSocket, CCEEnginePackage);
    //断开某个连接
    void slot_Disconnect(QObject * objSocket);
    //与目标建立连接
    bool slot_ConnectToUDP(const QString & address, quint16 nPort);
    bool slot_ConnectToCOM(QString comName);
    //发送探卡信息,不要再次操作中调用同步锁，独占锁，会造成m_hash_mutex死锁
    void slot_SendHelloPackage();
};
#endif
