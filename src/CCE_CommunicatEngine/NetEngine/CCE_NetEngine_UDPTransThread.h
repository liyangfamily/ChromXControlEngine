#ifndef CVTE_H_CCE_NETENGINE_UDPTRANSTHREAD
#define CVTE_H_CCE_NETENGINE_UDPTRANSTHREAD
#pragma once
#include "CCE_NetEngine_TransThread.h"

class CCE_NetEngine_UDPTransThread : public CCE_NetEngine_TransThread
{
    Q_OBJECT

public:
    explicit CCE_NetEngine_UDPTransThread(CCE_NetEngine* pThreadEngine, int nPayLoad = 4096, QObject *parent = 0);
    ~CCE_NetEngine_UDPTransThread();

private:
    //socket终止后响应
    void closeSocket(QObject* objSocket) override;

public slots:
    /******************************Engine信号响应槽函数********************************/
    //建立连接
    void slot_EstablishUDPConnection(CCE_NetEngine_TransThread* threadid, const QString& addr, quint16 port) override;
    //发送数据
    void slot_SendData(QObject* objSocket, CCEEnginePackage) override;

    /******************************内部响应槽函数********************************/
protected slots:
    //socket收到数据后响应
    void slot_New_Data_Recieved() override;
    //socket发送数据后响应
    void slot_Some_Data_Sended(qint64) override;
    //socket发生错误后响应
    void slot_DisplayError(QAbstractSocket::SocketError socketError) override;

};
#endif
