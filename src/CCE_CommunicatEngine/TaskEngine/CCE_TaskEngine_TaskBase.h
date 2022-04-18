#ifndef CVTE_H_CCE_TASKENGINE_TASKBASE
#define CVTE_H_CCE_TASKENGINE_TASKBASE
#pragma once
#include <CCE_CommunicatEngine/CCEEnginePackage>

#include <QObject>
#include <QDateTime>
#include <QMutex>
#include <QMutexLocker>
#include <QHostAddress>
#include <QNetworkInterface>

class CCE_TaskEngine_TaskBase :public QObject
{
    Q_OBJECT
public:
    explicit CCE_TaskEngine_TaskBase(QObject *parent = 0);
    virtual ~CCE_TaskEngine_TaskBase();

    virtual int run() = 0;
    virtual void sendHelloPackage() = 0;

    virtual void checkHeartBeating() = 0;

    int push_new_data(const CCEEnginePackage& dataArray);

    QObject * socketObj();
    void setHostName(QString); //绑定匹配cluster中的map
    QString hostName();

    int addRef();
    int delRef();

    int ref();

    bool lockRun();
    void unlockRun();

protected:
    QObject* m_pSocket;
    QString m_strTaskName;		//Task任务的名字，可以给到应用程序列出

    //给到任务每次最多处理的原始数据包个数
    static const int m_nMessageBlockSize = 8;

    //数据处理
    //原始数据队列和其锁
    QList<CCEEnginePackage> m_list_RawData;
    QMutex m_mutex_rawData;
    //当前读取数据的偏移，从原始数据队列开始，读完一个包就置0
        int m_currentReadOffset = 0;
    //当前消息的大小，解析完完整一包就置0
        quint64 m_currentMessageSize = 0;
    //当前正在处理的数据，此处和当前正在处理的包不一样，如果是串口通信或者TCP通信，则可能包内数据不完整
    QByteArray m_currentBlock;

    QDateTime m_last_Report;
private:
    int m_refCount = 0;
        QMutex m_mutex_ref;
    QMutex m_mutex_run;

signals:
    //Task主动发送数据信号
    void sig_SendData(QObject * objClient, CCEEnginePackage  dataArray);
    //Task接收到数据后，解析到是我们的设备，则与目标建立连接
    bool sig_ConnectToUDP(const QString & address, quint16 nPort,quint64 extraData);
    bool sig_ConnectToCOM(QString comName,quint64 extraData);
    //Task会主动检测在线状态，如果超时没有回复就主动断开连接
    void sig_Disconnect(QObject * objClient);
    //Task向外部发送消息
    void sig_Message(QObject * psource, QString);
    //Task发送解析到的数据帧
    void sig_ParsingInteCtrlDataFrame(QObject *psource, CCEEnginePackage dataFrame);
public slots:

};
#endif
