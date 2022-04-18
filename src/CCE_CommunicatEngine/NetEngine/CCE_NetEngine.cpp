#include "CCE_NetEngine.h"

#include "CCE_NetEngine_UDPTransThread.h"
#include "CCE_NetEngine_COMTransThread.h"

CCE_NetEngine::CCE_NetEngine(int nPayLoad/* = 4096*/, QObject *parent /*= 0*/) :
    QObject(parent)
{
    m_nPayLoad = nPayLoad;
    if (false == QMetaType::isRegistered(QMetaType::type("qintptr")))
        qRegisterMetaType<qintptr>("qintptr");
    if (false == QMetaType::isRegistered(QMetaType::type("QAbstractSocket::SocketError")))
        qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
    if (false == QMetaType::isRegistered(QMetaType::type("QSerialPort::SerialPortError")))
        qRegisterMetaType<QSerialPort::SerialPortError>("QSerialPort::SerialPortError");
    if (false == QMetaType::isRegistered(QMetaType::type("QHostAddress")))
        qRegisterMetaType<QHostAddress>("QHostAddress");
    if (false == QMetaType::isRegistered(QMetaType::type("CCEEnginePackage")))
        qRegisterMetaType<CCEEnginePackage>("CCEEnginePackage");
    creatTransThreads(m_nThread);
}

CCE_NetEngine::~CCE_NetEngine()
{
}

void CCE_NetEngine::creatTransThreads(int nThreads)
{
    //creatUDPTransThreads(nThreads);
    creatCOMTransThreads(nThreads);
}

void CCE_NetEngine::removeTransThreads(int nThreads)
{
    int nsz = m_vec_TransThreads.size();
    if (nThreads < 0)
        nThreads = nsz;
    int nCount = 0;
    for (int i = 0; i < nsz && nCount < nThreads; i++)
    {
        m_vec_TransThreads[i]->slot_Deactivate();
        nCount++;
    }
    //Fire TransThreadDel Immediately
    this->canExit();
}

void CCE_NetEngine::disconnectAll()
{
    int nsz = m_vec_TransThreads.size();
    for (int i = 0; i < nsz; i++)
        emit sig_DisconnectAll(m_vec_TransThreads[i]);
}

void CCE_NetEngine::deactiveImmediately()
{
    int nsz = m_vec_TransThreads.size();
    for (int i = 0; i < nsz; i++)
        emit sig_DeactivteImmediately(m_vec_TransThreads[i]);
}

bool CCE_NetEngine::canExit()
{
    bool res = true;
    int nsz = m_vec_TransThreads.size();
    for (int i = nsz - 1; i >= 0 && res == true; i--)
        res = transThreadDelete(m_vec_TransThreads[i]);

    if (m_vec_TransThreads.size())
        res = false;
    return res;
}

bool CCE_NetEngine::transThreadDelete(CCE_NetEngine_TransThread *threadid)
{
    if (threadid->canExit() == false)
        return false;
    int nsz = m_vec_TransThreads.size();
    int idx = -1;
    for (int i = 0; i < nsz && idx < 0; i++)
    {
        if (m_vec_TransThreads[i] == threadid)
            idx = i;
    }
    if (idx >= 0 && idx < nsz)
    {
        CCE_NetEngine_TransThread * clientTH = m_vec_TransThreads[idx];
        disconnect(clientTH, &CCE_NetEngine_TransThread::sig_SocketClosed, this, &CCE_NetEngine::sig_SocketAbort);
        disconnect(clientTH, &CCE_NetEngine_TransThread::sig_Data_Received, this, &CCE_NetEngine::sig_Data_Received);
        disconnect(clientTH, &CCE_NetEngine_TransThread::sig_Data_Sended, this, &CCE_NetEngine::sig_Data_Sended);
        disconnect(clientTH, &CCE_NetEngine_TransThread::sig_Message, this, &CCE_NetEngine::sig_Message);

        if (clientTH->transThreadType() == ECommunicatType::ECT_UDP)
        {
            disconnect(clientTH, QOverload<QObject*, const QString&, quint16,quint64>::of(&CCE_NetEngine_TransThread::sig_NewUDPConnectionEstablish),
                this, QOverload<QObject*, const QString&, quint16,quint64>::of(&CCE_NetEngine::sig_NewUDPConnectionEstablish));
            disconnect(clientTH, QOverload<QObject*, QAbstractSocket::SocketError>::of(&CCE_NetEngine_TransThread::sig_SocketError),
                this, QOverload<QObject*, QAbstractSocket::SocketError>::of(&CCE_NetEngine::sig_SocketError));
            disconnect(this, QOverload<CCE_NetEngine_TransThread*, const QString&, quint16,quint64>::of(&CCE_NetEngine::sig_EstablishUDPConnection),
                clientTH, QOverload<CCE_NetEngine_TransThread*, const QString&, quint16,quint64>::of(&CCE_NetEngine_TransThread::slot_EstablishUDPConnection));
        }
        else if (clientTH->transThreadType() == ECommunicatType::ECT_COM)
        {
            disconnect(clientTH, QOverload<QObject*, QString,quint64>::of(&CCE_NetEngine_TransThread::sig_NewCOMConnectionEstablish),
                this, QOverload<QObject*, QString,quint64>::of(&CCE_NetEngine::sig_NewCOMConnectionEstablish));
            disconnect(clientTH, QOverload<QObject*, QSerialPort::SerialPortError>::of(&CCE_NetEngine_TransThread::sig_SocketError),
                this, QOverload<QObject*, QSerialPort::SerialPortError>::of(&CCE_NetEngine::sig_SocketError));
            disconnect(this, QOverload<CCE_NetEngine_TransThread*, QString,quint64>::of(&CCE_NetEngine::sig_EstablishCOMConnection),
                clientTH, QOverload<CCE_NetEngine_TransThread*, QString,quint64>::of(&CCE_NetEngine_TransThread::slot_EstablishCOMConnection));
        }

        disconnect(this, &CCE_NetEngine::sig_SendData, clientTH, &CCE_NetEngine_TransThread::slot_SendData);
        disconnect(this, &CCE_NetEngine::sig_DisconnectAll, clientTH, &CCE_NetEngine_TransThread::slot_DisconnectAll);
        disconnect(this, &CCE_NetEngine::sig_DeactivteImmediately, clientTH, &CCE_NetEngine_TransThread::slot_DeactivateImmediately);
        disconnect(this, &CCE_NetEngine::sig_Disconnect, clientTH, &CCE_NetEngine_TransThread::slot_Disconnect);

        //最后的清理工作
        m_vec_TransThreads[idx]->emptyRabbishCan(); //先清理垃圾桶
        m_vec_TransThreads[idx]->deleteLater(); //再删除worker，必须要在线程退出前调用，否则worker将不会析构
        m_vec_InternalTransThreads[idx]->quit();
        m_vec_InternalTransThreads[idx]->wait();
        m_vec_InternalTransThreads[idx]->deleteLater();
        m_vec_InternalTransThreads.remove(idx);
        m_vec_TransThreads.remove(idx);

    }
    return true;
}

void CCE_NetEngine::creatUDPTransThreads(int nThreads)
{

    if (nThreads > 0 && nThreads < 256)
    {
        for (int i = 0; i < nThreads; ++i)
        {
            CCE_NetEngine_TransThread* clientTH = new CCE_NetEngine_UDPTransThread(this, m_nPayLoad);
            QThread *pThread = new QThread(this);
            m_vec_InternalTransThreads.push_back(pThread);
            m_vec_TransThreads.push_back(clientTH);
            pThread->start();

            connect(clientTH, &CCE_NetEngine_TransThread::sig_SocketClosed, this, &CCE_NetEngine::sig_SocketAbort, Qt::QueuedConnection);
            connect(clientTH, &CCE_NetEngine_TransThread::sig_Data_Received, this, &CCE_NetEngine::sig_Data_Received, Qt::QueuedConnection);
            connect(clientTH, &CCE_NetEngine_TransThread::sig_Data_Sended, this, &CCE_NetEngine::sig_Data_Sended, Qt::QueuedConnection);
            connect(clientTH, &CCE_NetEngine_TransThread::sig_Message, this, &CCE_NetEngine::sig_Message, Qt::QueuedConnection);

            connect(clientTH, QOverload<QObject*, const QString&, quint16,quint64>::of(&CCE_NetEngine_TransThread::sig_NewUDPConnectionEstablish),
                this, QOverload<QObject*, const QString&, quint16,quint64>::of(&CCE_NetEngine::sig_NewUDPConnectionEstablish), Qt::QueuedConnection);
            connect(clientTH, QOverload<QObject*, QAbstractSocket::SocketError>::of(&CCE_NetEngine_TransThread::sig_SocketError),
                this, QOverload<QObject*, QAbstractSocket::SocketError>::of(&CCE_NetEngine::sig_SocketError), Qt::QueuedConnection);
            connect(this, QOverload<CCE_NetEngine_TransThread*, const QString&, quint16,quint64>::of(&CCE_NetEngine::sig_EstablishUDPConnection),
                clientTH, QOverload<CCE_NetEngine_TransThread*, const QString&, quint16,quint64>::of(&CCE_NetEngine_TransThread::slot_EstablishUDPConnection), Qt::QueuedConnection);

            connect(this, &CCE_NetEngine::sig_SendData, clientTH, &CCE_NetEngine_TransThread::slot_SendData, Qt::QueuedConnection);
            connect(this, &CCE_NetEngine::sig_DisconnectAll, clientTH, &CCE_NetEngine_TransThread::slot_DisconnectAll, Qt::QueuedConnection);
            connect(this, &CCE_NetEngine::sig_DeactivteImmediately, clientTH, &CCE_NetEngine_TransThread::slot_DeactivateImmediately, Qt::QueuedConnection);
            connect(this, &CCE_NetEngine::sig_Disconnect, clientTH, &CCE_NetEngine_TransThread::slot_Disconnect, Qt::QueuedConnection);

            clientTH->moveToThread(pThread);
        }
    }
}

void CCE_NetEngine::creatCOMTransThreads(int nThreads)
{

    if (nThreads > 0 && nThreads < 256)
    {
        for (int i = 0; i < nThreads; ++i)
        {
            CCE_NetEngine_TransThread* clientTH = new CCE_NetEngine_COMTransThread(this, m_nPayLoad);
            QThread *pThread = new QThread(this);
            m_vec_InternalTransThreads.push_back(pThread);
            m_vec_TransThreads.push_back(clientTH);
            pThread->start();

            connect(clientTH, &CCE_NetEngine_TransThread::sig_SocketClosed, this, &CCE_NetEngine::sig_SocketAbort, Qt::QueuedConnection);
            connect(clientTH, &CCE_NetEngine_TransThread::sig_Data_Received, this, &CCE_NetEngine::sig_Data_Received, Qt::QueuedConnection);
            connect(clientTH, &CCE_NetEngine_TransThread::sig_Data_Sended, this, &CCE_NetEngine::sig_Data_Sended, Qt::QueuedConnection);
            connect(clientTH, &CCE_NetEngine_TransThread::sig_Message, this, &CCE_NetEngine::sig_Message, Qt::QueuedConnection);

            connect(clientTH, QOverload<QObject*, QString,quint64>::of(&CCE_NetEngine_TransThread::sig_NewCOMConnectionEstablish),
                this, QOverload<QObject*, QString,quint64>::of(&CCE_NetEngine::sig_NewCOMConnectionEstablish), Qt::QueuedConnection);
            connect(clientTH, QOverload<QObject*, QSerialPort::SerialPortError>::of(&CCE_NetEngine_TransThread::sig_SocketError),
                this, QOverload<QObject*, QSerialPort::SerialPortError>::of(&CCE_NetEngine::sig_SocketError), Qt::QueuedConnection);
            connect(this, QOverload<CCE_NetEngine_TransThread*, QString,quint64>::of(&CCE_NetEngine::sig_EstablishCOMConnection),
                clientTH, QOverload<CCE_NetEngine_TransThread*, QString,quint64>::of(&CCE_NetEngine_TransThread::slot_EstablishCOMConnection), Qt::QueuedConnection);

            connect(this, &CCE_NetEngine::sig_SendData, clientTH, &CCE_NetEngine_TransThread::slot_SendData, Qt::QueuedConnection);
            connect(this, &CCE_NetEngine::sig_DisconnectAll, clientTH, &CCE_NetEngine_TransThread::slot_DisconnectAll, Qt::QueuedConnection);
            connect(this, &CCE_NetEngine::sig_DeactivteImmediately, clientTH, &CCE_NetEngine_TransThread::slot_DeactivateImmediately, Qt::QueuedConnection);
            connect(this, &CCE_NetEngine::sig_Disconnect, clientTH, &CCE_NetEngine_TransThread::slot_Disconnect, Qt::QueuedConnection);

            clientTH->moveToThread(pThread);
        }
    }
}

void CCE_NetEngine::slot_SendData(QObject * objSocket, CCEEnginePackage datarray)
{
    emit sig_SendData(objSocket, datarray);
}

void CCE_NetEngine::slot_Disconnect(QObject * objSocket)
{
    emit sig_Disconnect(objSocket);
}

bool CCE_NetEngine::slot_ConnectToUDP(const QString & address, quint16 nPort,quint64 extraData)
{
    bool res = false;
    //m_mutex_trans.lock();
    int nsz = m_vec_TransThreads.size();
    if (0 == nsz) {
        creatTransThreads(m_nThread);
    }
    int nMinPay = 0x7fffffff;
    int nMinIdx = -1;

    for (int i = 0; i < nsz && nMinPay != 0; i++)
    {
        if (m_vec_TransThreads[i]->isActive() == false || m_vec_TransThreads[i]->transThreadType() != ECommunicatType::ECT_UDP)
            continue;
        int nPat = m_vec_TransThreads[i]->currentClients();

        if (nPat < nMinPay)
        {
            nMinPay = nPat;
            nMinIdx = i;
        }
        //qDebug()<<i<<" "<<nPat<<" "<<nMinIdx;
    }
    //remove old threads
    for (int i = 0; i < nsz; i++)
        if (m_vec_TransThreads[i]->isActive() == false)
            transThreadDelete(m_vec_TransThreads[i]);

    if (nMinIdx >= 0 && nMinIdx < nsz)
    {
        res = true;
        emit sig_EstablishUDPConnection(m_vec_TransThreads[nMinIdx], address, nPort,extraData);
    }
    else
    {
        emit sig_Message(this, "Warning>" + QString(tr("Need Trans Thread Object for clients.")));
    }
    return res;
}

bool CCE_NetEngine::slot_ConnectToCOM(QString comName,quint64 extraData)
{
    bool res = false;
    //m_mutex_trans.lock();
    int nsz = m_vec_TransThreads.size();
    int nMinPay = 0x7fffffff;
    int nMinIdx = -1;

    for (int i = 0; i < nsz && nMinPay != 0; i++)
    {
        if (m_vec_TransThreads[i]->isActive() == false || m_vec_TransThreads[i]->transThreadType() != ECommunicatType::ECT_COM)
            continue;
        int nPat = m_vec_TransThreads[i]->currentClients();

        if (nPat < nMinPay)
        {
            nMinPay = nPat;
            nMinIdx = i;
        }
        //qDebug()<<i<<" "<<nPat<<" "<<nMinIdx;
    }
    //remove old threads
    for (int i = 0; i < nsz; i++)
        if (m_vec_TransThreads[i]->isActive() == false)
            transThreadDelete(m_vec_TransThreads[i]);

    if (nMinIdx >= 0 && nMinIdx < nsz)
    {
        res = true;
        emit sig_EstablishCOMConnection(m_vec_TransThreads[nMinIdx], comName,extraData);
    }
    else
    {
        emit sig_Message(this, "Warning>" + QString(tr("Need Trans Thread Object for clients.")));
    }
    return res;
}
