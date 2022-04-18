/*********************************************************************************************************
** This file is part of the CCE_CommunicatEngine module of the CCE Toolkit.
*********************************************************************************************************/

/*!
\class CCECluster

\inmodule CCE_CommunicatEngine

\brief The class is the cluster management class of the communication library.

\code

\endcode

\note:

*/

#include "CCE_CommunicatEngine/CCECluster.h"
#include "CCE_TaskEngine_IntegratedCtrlTask.h"
#include "../CCE_CommunicatEngine/NetEngine/CCE_NetEngine.h"
#include "../CCE_CommunicatEngine/TaskEngine/CCE_TaskEngine.h"
#include "CCE_CommunicatEngine/CCEClusterProxy.h"

CCECluster::CCECluster(QObject *parent)
    : QObject(parent)
{
    m_pNetEngine = new CCE_NetEngine(4096, this);
    m_pTaskEngine = new CCE_TaskEngine(this);
    connect(m_pNetEngine, &CCE_NetEngine::sig_Message, this, &CCECluster::sig_Message, Qt::QueuedConnection);

    connect(m_pNetEngine, QOverload<QObject*, QAbstractSocket::SocketError>::of(&CCE_NetEngine::sig_SocketError),
        this, QOverload<QObject*, QAbstractSocket::SocketError>::of(&CCECluster::sig_SocketError), Qt::QueuedConnection);
    connect(m_pNetEngine, QOverload<QObject*, QSerialPort::SerialPortError>::of(&CCE_NetEngine::sig_SocketError),
        this, QOverload<QObject*, QSerialPort::SerialPortError>::of(&CCECluster::sig_SocketError), Qt::QueuedConnection);

    connect(m_pNetEngine, &CCE_NetEngine::sig_SendData, this, &CCECluster::sig_SendedDataSteam, Qt::QueuedConnection);
    connect(m_pNetEngine, &CCE_NetEngine::sig_Data_Received, this, &CCECluster::slot_Data_Received, Qt::QueuedConnection);
    connect(m_pNetEngine, &CCE_NetEngine::sig_Data_Sended, this, &CCECluster::slot_Data_Sended, Qt::QueuedConnection);
    connect(m_pNetEngine, &CCE_NetEngine::sig_SocketAbort, this, &CCECluster::slot_SocketAbort, Qt::QueuedConnection);

    connect(m_pNetEngine, QOverload<QObject*, const QString&, quint16,quint64>::of(&CCE_NetEngine::sig_NewUDPConnectionEstablish),
        this, QOverload<QObject*, const QString&, quint16,quint64>::of(&CCECluster::slot_NewUDPConnectionEstablish), Qt::QueuedConnection);
    connect(m_pNetEngine, QOverload<QObject*, QString,quint64>::of(&CCE_NetEngine::sig_NewCOMConnectionEstablish),
        this, QOverload<QObject*, QString,quint64>::of(&CCECluster::slot_NewCOMConnectionEstablish), Qt::QueuedConnection);

    m_nHeartBeatingTime = 20;
}

CCECluster::~CCECluster()
{
    /*if (m_pNetEngine)
        m_pNetEngine->deleteLater();
    if (m_pTaskEngine)
        m_pTaskEngine->deleteLater();*/
}

CCECluster * CCECluster::instance()
{
    static CCECluster m_global_Cluster;
    return &m_global_Cluster;
}

CCE_NetEngine * CCECluster::netEngine()
{
    return m_pNetEngine;
}

CCE_TaskEngine * CCECluster::taskEngine()
{
    return m_pTaskEngine;
}

int CCECluster::heartBeatingThrdHold()
{
    return m_nHeartBeatingTime;
}

void CCECluster::setHeartBeatingThrd(const int n)
{
    m_nHeartBeatingTime = n;
}

bool CCECluster::isSocketInExclusive(QObject* objSocket)
{
    bool bRet = false;
    m_mutex_ExclusiveLock.lock();
    if (m_hash_sockExclusive.contains(objSocket))
    {
        bRet = m_hash_sockExclusive[objSocket].isNull() ? false : true;
    }
    m_mutex_ExclusiveLock.unlock();
    return bRet;
}

QUuid CCECluster::exclusiveKey(QObject* objSocket)
{
    QUuid id;
    m_mutex_ExclusiveLock.lock();
    if (m_hash_sockExclusive.contains(objSocket))
    {
        id = m_hash_sockExclusive[objSocket];
    }
    m_mutex_ExclusiveLock.unlock();
    return id;
}

void CCECluster::readyToExit()
{
    this->netEngine()->deactiveImmediately();
    this->taskEngine()->removeThreads(-1);
}

bool CCECluster::canExit()
{
    if(!this->m_hash_sock2node.isEmpty()){
        return false;
    }
    return m_pTaskEngine->canExit() && m_pNetEngine->canExit();
}

void CCECluster::disconnectAllConnect()
{
    this->netEngine()->disconnectAll();
}

void CCECluster::slot_SocketAbort(QObject * clientHandle)
{
    bool nHashContains = false;

    CCE_TaskEngine_TaskBase * pClientTask = 0;
    m_hash_mutex.lock();
    nHashContains = m_hash_sock2node.contains(clientHandle);
    if (nHashContains)
        pClientTask = m_hash_sock2node[clientHandle];
    if (pClientTask)
    {
        disconnect(pClientTask, &CCE_TaskEngine_TaskBase::sig_SendData, m_pNetEngine, &CCE_NetEngine::sig_SendData);
        disconnect(pClientTask, QOverload<const QString&, quint16,quint64>::of(&CCE_TaskEngine_TaskBase::sig_ConnectToUDP),
            m_pNetEngine, QOverload<const QString&, quint16,quint64>::of(&CCE_NetEngine::slot_ConnectToUDP));
        disconnect(pClientTask, QOverload<QString,quint64>::of(&CCE_TaskEngine_TaskBase::sig_ConnectToCOM),
            m_pNetEngine, QOverload<QString,quint64>::of(&CCE_NetEngine::slot_ConnectToCOM));
        disconnect(pClientTask, &CCE_TaskEngine_TaskBase::sig_Disconnect, m_pNetEngine, &CCE_NetEngine::sig_Disconnect);
        disconnect(pClientTask, &CCE_TaskEngine_TaskBase::sig_Message, this, &CCECluster::sig_Message);
        disconnect(pClientTask, &CCE_TaskEngine_TaskBase::sig_ParsingInteCtrlDataFrame, this, &CCECluster::sig_ParsingInteCtrlDataFrame);

        m_hash_sock2node.remove(clientHandle);
        m_hash_Name2node.remove(pClientTask->hostName());

        m_nodeToBeDel.push_back(pClientTask);
        emit sig_SocketAbort(clientHandle);
    }
    m_hash_mutex.unlock();

    //Try to delete objects
    QList <CCE_TaskEngine_TaskBase *> toBedel;
    foreach(CCE_TaskEngine_TaskBase * pdelobj, m_nodeToBeDel)
    {
        if (pdelobj->ref() == 0) {
            toBedel.push_back(pdelobj);
        }
        else
        {
            qDebug()<<QString("CCE_TaskEngine_TaskBase %1(ref %2) Waiting in del queue.").arg((quint64)pdelobj).arg(pdelobj->ref());
        }
    }
    foreach(CCE_TaskEngine_TaskBase * pdelobj, toBedel)
    {
        m_nodeToBeDel.removeAll(pdelobj);
        qDebug()<<QString("CCE_TaskEngine_TaskBase %1(ref %2) deleting.").arg((quint64)pdelobj).arg(pdelobj->ref());
        pdelobj->deleteLater();
    }
}

void CCECluster::slot_Data_Received(QObject * clientHandle, CCEEnginePackage datablock)
{
    bool nHashContains = false;
    CCE_TaskEngine_TaskBase * pClientTask = 0;
    m_hash_mutex.lock();
    nHashContains = m_hash_sock2node.contains(clientHandle);
    if (false == nHashContains)
    {
        //后续改成工厂模式创建，在此处如果收到不包含在表中socket的内容，就新建一个任务
        CCE_TaskEngine_TaskBase * pnode = new CCE_TaskEngine_IntegratedCtrlTask(this, clientHandle, this);
        //using queued connection of send and revieve;
        connect(pnode, &CCE_TaskEngine_TaskBase::sig_SendData, m_pNetEngine, &CCE_NetEngine::sig_SendData, Qt::QueuedConnection);
        connect(pnode, QOverload<const QString&, quint16,quint64>::of(&CCE_TaskEngine_TaskBase::sig_ConnectToUDP),
            m_pNetEngine, QOverload<const QString&, quint16,quint64>::of(&CCE_NetEngine::slot_ConnectToUDP), Qt::QueuedConnection);
        connect(pnode, QOverload<QString,quint64>::of(&CCE_TaskEngine_TaskBase::sig_ConnectToCOM),
            m_pNetEngine, QOverload<QString,quint64>::of(&CCE_NetEngine::slot_ConnectToCOM), Qt::QueuedConnection);
        connect(pnode, &CCE_TaskEngine_TaskBase::sig_Disconnect, m_pNetEngine, &CCE_NetEngine::sig_Disconnect, Qt::QueuedConnection);
        connect(pnode, &CCE_TaskEngine_TaskBase::sig_Message, this, &CCECluster::sig_Message, Qt::QueuedConnection);
        connect(pnode, &CCE_TaskEngine_TaskBase::sig_ParsingInteCtrlDataFrame, this, &CCECluster::sig_ParsingInteCtrlDataFrame, Qt::QueuedConnection);
        m_hash_sock2node[clientHandle] = pnode;
        nHashContains = true;
        pClientTask = pnode;
    }
    else
    {
        pClientTask = m_hash_sock2node[clientHandle];
    }
    assert(nHashContains != 0 && pClientTask != 0);
    int nblocks = pClientTask->push_new_data(datablock);
    if (nblocks <= 1)
        m_pTaskEngine->slot_pushTask(pClientTask);
    m_hash_mutex.unlock();
}

void CCECluster::slot_Data_Sended(QObject * clientHandle, qint64 bytesSend)
{
    emit sig_Data_Sended(clientHandle, bytesSend);
}

void CCECluster::slot_NewUDPConnectionEstablish(QObject* clientHandle, const QString& addr, quint16 port,quint64 extraData)
{
    bool nHashContains = false;
    CCE_TaskEngine_TaskBase * pClientTask = 0;
    m_hash_mutex.lock();
    nHashContains = m_hash_sock2node.contains(clientHandle);
    if (false == nHashContains)
    {
        //后续根据端口号不同new不同的Task，使用简单工厂即可
        CCE_TaskEngine_IntegratedCtrlUDPTask * pnode = new CCE_TaskEngine_IntegratedCtrlUDPTask(this, clientHandle, this);
        QString hostName = CCEEnginePackage::genHostName(addr, port);
        pnode->setHostName(hostName);
        qDebug() << "New Connection. IP:" << addr << " Port:" << port;
        connect(pnode, &CCE_TaskEngine_TaskBase::sig_SendData, m_pNetEngine, &CCE_NetEngine::sig_SendData, Qt::QueuedConnection);
        connect(pnode, QOverload<const QString&, quint16,quint64>::of(&CCE_TaskEngine_TaskBase::sig_ConnectToUDP),
            m_pNetEngine, QOverload<const QString&, quint16,quint64>::of(&CCE_NetEngine::slot_ConnectToUDP), Qt::QueuedConnection);
        /*connect(pnode, QOverload<QString>::of(&CCE_TaskEngine_TaskBase::sig_ConnectToCOM),
            m_pNetEngine, QOverload<QString>::of(&CCE_NetEngine::slot_ConnectToCOM), Qt::QueuedConnection);*/
        connect(pnode, &CCE_TaskEngine_TaskBase::sig_Disconnect, m_pNetEngine, &CCE_NetEngine::sig_Disconnect, Qt::QueuedConnection);
        connect(pnode, &CCE_TaskEngine_TaskBase::sig_Message, this, &CCECluster::sig_Message, Qt::QueuedConnection);
        connect(pnode, &CCE_TaskEngine_TaskBase::sig_ParsingInteCtrlDataFrame, this, &CCECluster::sig_ParsingInteCtrlDataFrame, Qt::QueuedConnection);
        m_hash_sock2node[clientHandle] = pnode;
        m_hash_Name2node[hostName] = pnode;
        nHashContains = true;
        pClientTask = pnode;
    }
    else
    {
        pClientTask = m_hash_sock2node[clientHandle];
    }
    m_hash_mutex.unlock();
    Q_ASSERT(nHashContains != 0 && pClientTask != 0);
    emit sig_NewUDPConnectionEstablish(clientHandle, addr, port,extraData);
}

void CCECluster::slot_NewCOMConnectionEstablish(QObject* clientHandle, QString comName,quint64 extraData)
{
    bool nHashContains = false;
    CCE_TaskEngine_TaskBase * pClientTask = 0;
    m_hash_mutex.lock();
    nHashContains = m_hash_sock2node.contains(clientHandle);
    if (false == nHashContains)
    {
        CCE_TaskEngine_TaskBase * pnode = new CCE_TaskEngine_IntegratedCtrlCOMTask(this, clientHandle, this);
        QString hostName = CCEEnginePackage::genHostName(comName);
        pnode->setHostName(hostName);
        qDebug() << "New Connection. COM:" << comName;
        //using queued connection of send and revieve;
        connect(pnode, &CCE_TaskEngine_TaskBase::sig_SendData, m_pNetEngine, &CCE_NetEngine::sig_SendData, Qt::QueuedConnection);
        /*connect(pnode, QOverload<const QHostAddress&, quint16>::of(&CCE_TaskEngine_TaskBase::sig_ConnectToUDP),
            m_pNetEngine, QOverload<const QHostAddress&, quint16>::of(&CCE_NetEngine::slot_ConnectToUDP), Qt::QueuedConnection);*/
        connect(pnode, QOverload<QString,quint64>::of(&CCE_TaskEngine_TaskBase::sig_ConnectToCOM),
            m_pNetEngine, QOverload<QString,quint64>::of(&CCE_NetEngine::slot_ConnectToCOM), Qt::QueuedConnection);
        connect(pnode, &CCE_TaskEngine_TaskBase::sig_Disconnect, m_pNetEngine, &CCE_NetEngine::sig_Disconnect, Qt::QueuedConnection);
        connect(pnode, &CCE_TaskEngine_TaskBase::sig_Message, this, &CCECluster::sig_Message, Qt::QueuedConnection);
        connect(pnode, &CCE_TaskEngine_TaskBase::sig_ParsingInteCtrlDataFrame, this, &CCECluster::sig_ParsingInteCtrlDataFrame, Qt::QueuedConnection);
        m_hash_sock2node[clientHandle] = pnode;
        m_hash_Name2node[hostName] = pnode;
        nHashContains = true;
        pClientTask = pnode;
    }
    else
    {
        pClientTask = m_hash_sock2node[clientHandle];
    }
    m_hash_mutex.unlock();
    Q_ASSERT(nHashContains != 0 && pClientTask != 0);
    emit sig_NewCOMConnectionEstablish(clientHandle, comName,extraData);
}

bool CCECluster::slot_SendData(QObject * objSocket, CCEEnginePackage pack)
{
    m_hash_mutex.lock();
    if (m_hash_sock2node.contains(objSocket))
    {
        if (this->isSocketInExclusive(objSocket))
        {
            QUuid id = exclusiveKey(objSocket);
            if (id == pack.exclusiveKey())
            {
                netEngine()->slot_SendData(objSocket, pack);
                m_hash_mutex.unlock();
                return true;
            }
            else
            {
                qDebug() << tr("(%1)..is in Exclusive.").arg((quint64)objSocket);
                m_hash_mutex.unlock();
                return false;
            }
        }
        else
        {
            netEngine()->slot_SendData(objSocket, pack);
            m_hash_mutex.unlock();
            return true;
        }
    }
    m_hash_mutex.unlock();
    return false;
}

void CCECluster::slot_Disconnect(QObject * objSocket)
{
    m_hash_mutex.lock();
    if (m_hash_sock2node.contains(objSocket))
        netEngine()->slot_Disconnect(objSocket);
    m_hash_mutex.unlock();
}

bool CCECluster::slot_ConnectToUDP(const QString & address, quint16 nPort,quint64 extraData)
{
    QString hostName = CCEEnginePackage::genHostName(address, nPort);
    if (m_hash_Name2node.contains(hostName))
    {
        qDebug() << hostName << ", connection already existing.";
        return false;
    }
    return netEngine()->slot_ConnectToUDP(address, nPort,extraData);
}

bool CCECluster::slot_ConnectToCOM(QString comName,quint64 extraData)
{
    QString hostName = CCEEnginePackage::genHostName(comName);
    if (m_hash_Name2node.contains(hostName))
    {
        qDebug() << hostName << ", connection already existing.";
        return false;
    }
    return netEngine()->slot_ConnectToCOM(comName,extraData);
}

void CCECluster::slot_SendHelloPackage()
{
    m_hash_mutex.lock();
    for (QMap<QObject *, CCE_TaskEngine_TaskBase *>::iterator p = m_hash_sock2node.begin();
        p != m_hash_sock2node.end(); p++)
    {
        if (!isSocketInExclusive(p.key()) && !CCEClusterProxy::isItemExlusive(m_hash_Name2node.key(p.value())))
            p.value()->sendHelloPackage();
    }
    m_hash_mutex.unlock();
}

void CCECluster::slot_KickDeadClients()
{
    m_hash_mutex.lock();
    for (QMap<QObject *, CCE_TaskEngine_TaskBase *>::iterator p = m_hash_sock2node.begin();
        p != m_hash_sock2node.end(); p++)
    {
        p.value()->checkHeartBeating();
    }
    m_hash_mutex.unlock();
}

void CCECluster::slot_SetSocketExlusive(QObject* objSocket, bool enable)
{
    m_hash_mutex.lock();
    if (m_hash_sock2node.contains(objSocket))
    {
        m_mutex_ExclusiveLock.lock();
        QUuid id;
        if (enable)
        {
            id = QUuid::createUuid();
            m_hash_sockExclusive[objSocket] = id;
        }
        else
        {
            id = QUuid();
            m_hash_sockExclusive[objSocket] = id;
        }
        m_mutex_ExclusiveLock.unlock();
        emit sig_ExlusiveLocked(objSocket, enable, id);
    }
    m_hash_mutex.unlock();
}
