#include "CCE_NetEngine_TransThread.h"
#include <QThread>
#include <QUdpSocket>

int CCE_NetEngine_TransThread::RUBBISH_CAN_SIZE = 256;

CCE_NetEngine_TransThread::CCE_NetEngine_TransThread(CCE_NetEngine* pThreadEngine, int nPayLoad /*= 4096*/, QObject *parent /*= 0*/)
    : QObject(parent)
{
    m_bActivated = true;
    m_pThreadPool = pThreadEngine;
    m_nPayLoad = nPayLoad;
    Q_ASSERT(m_nPayLoad >= 256 && m_nPayLoad <= 16 * 1024 * 1024);
}

CCE_NetEngine_TransThread::~CCE_NetEngine_TransThread()
{
}

QList<QObject*> CCE_NetEngine_TransThread::clientsList()
{
    QList<QObject*> lists;
    m_mutex_protect.lock();
    lists = m_clientList.values();
    m_mutex_protect.unlock();
    return lists;
}

int CCE_NetEngine_TransThread::currentClients()
{
    int  nres = 0;
    m_mutex_protect.lock();
    nres = m_clientList.size();
    m_mutex_protect.unlock();
    return nres;
}

void CCE_NetEngine_TransThread::setPayLoad(int nPayLoad)
{
    m_nPayLoad = nPayLoad;
    Q_ASSERT(m_nPayLoad >= 256 && m_nPayLoad <= 16 * 1024 * 1024);
}

bool CCE_NetEngine_TransThread::isActive()
{
    return m_bActivated;
}

bool CCE_NetEngine_TransThread::canExit()
{
    if (m_bActivated)
        return false;
    if (currentClients())
        return false;
    return true;
}

void CCE_NetEngine_TransThread::emptyRabbishCan()
{
    m_mutex_rabbish_can.lock();
    foreach(QObject* pDel, m_rabbish_can)
        pDel->deleteLater();
    m_rabbish_can.clear();
    m_set_rabbish_can.clear();
    m_mutex_rabbish_can.unlock();
}

ECommunicatType CCE_NetEngine_TransThread::transThreadType()
{
    return m_communicatType;
}

void CCE_NetEngine_TransThread::push_to_rabbish_can(QObject * deleteObjSocket)
{
    m_mutex_rabbish_can.lock();
    if (m_set_rabbish_can.contains(deleteObjSocket) == false)
    {
        m_rabbish_can.push_back(deleteObjSocket);
        m_set_rabbish_can.insert(deleteObjSocket);
    }
    if (RUBBISH_CAN_SIZE < 16)
        RUBBISH_CAN_SIZE = 16;
    if (RUBBISH_CAN_SIZE > 65536)
        RUBBISH_CAN_SIZE = 65536;
    if (m_rabbish_can.size() >= RUBBISH_CAN_SIZE)
        qDebug() << "Delete old objects from rubbish can.";
    while (m_rabbish_can.size() >= RUBBISH_CAN_SIZE)
    {
        m_rabbish_can.first()->deleteLater();
        m_set_rabbish_can.remove(m_rabbish_can.first());
        m_rabbish_can.pop_front();
    }
    m_mutex_rabbish_can.unlock();
}

//基类不实现，各个子类负责去关闭自己的socket
void CCE_NetEngine_TransThread::closeSocket(QObject * objSocket)
{
    Q_UNUSED(objSocket)
    return;
}

//基类不实现，各个子类负责钱建立自己的连接，该槽函数给UDP连接使用
void CCE_NetEngine_TransThread::slot_EstablishUDPConnection(CCE_NetEngine_TransThread* threadid, const QString& addr, quint16 port)
{
    Q_UNUSED(threadid)
    Q_UNUSED(addr)
    Q_UNUSED(port)
    return;
}

//基类不实现，各个子类负责钱建立自己的连接，该槽函数给COM连接使用
void CCE_NetEngine_TransThread::slot_EstablishCOMConnection(CCE_NetEngine_TransThread * threadid, QString comName)
{
    Q_UNUSED(threadid)
    Q_UNUSED(comName)
    return;
}

//基类不实现，各子类负责对应socket的数据下发
#include <QTime>
#include <CCE_Core/CCEUIHelper>
void CCE_NetEngine_TransThread::slot_SendData(QObject * objSocket, CCEEnginePackage package)
{
    Q_UNUSED(objSocket)
    Q_UNUSED(package)
    if(CCEUIHelper::enableCommunicatLog()){
        QString frame;
        frame = CCEUIHelper::byteArrayToHexStr(package.data());
        qInfo()<<QString("TX:Host:%2, Length:%3, Data:%4").arg(package.hostName()).arg(package.data().size()).arg(frame);
    }
    return;
}

void CCE_NetEngine_TransThread::slot_Deactivate()
{
    m_bActivated = false;
}

void CCE_NetEngine_TransThread::slot_DeactivateImmediately(CCE_NetEngine_TransThread *threadid)
{
    if (threadid != this)
        return;
    m_bActivated = false;
    this->slot_DisconnectAll(threadid);
}

void CCE_NetEngine_TransThread::slot_DisconnectAll(CCE_NetEngine_TransThread *threadid)
{
    if (threadid != this)
        return;
    m_mutex_protect.lock();
    QList<QObject *> clientList = m_clientList.values();
    m_mutex_protect.unlock();
    foreach(QObject * obj, clientList)
    {
        if (obj)
        {
            closeSocket(obj);
        }
    }
}

void CCE_NetEngine_TransThread::slot_Disconnect(QObject *objSocket)
{
    m_mutex_protect.lock();
    if (m_clientList.contains(objSocket) == false)
    {
        m_mutex_protect.unlock();
        return;
    }
    m_mutex_protect.unlock();
    if (objSocket)
    {
        closeSocket(objSocket);
    }
}

//基类不实现，各子类负责处理收到数据后的组包处理
void CCE_NetEngine_TransThread::slot_New_Data_Recieved()
{
    return;
}

//基类不实现，各子类负责处理发送数据后的逻辑处理
void CCE_NetEngine_TransThread::slot_Some_Data_Sended(qint64 wsended)
{
    Q_UNUSED(wsended)
    return;
}

//基类不实现，各子磊负责各socket的错误信息
void CCE_NetEngine_TransThread::slot_DisplayError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError)
    return;
}

void CCE_NetEngine_TransThread::slot_DisplayError(QSerialPort::SerialPortError serialError)
{
    Q_UNUSED(serialError)
    return;
}
