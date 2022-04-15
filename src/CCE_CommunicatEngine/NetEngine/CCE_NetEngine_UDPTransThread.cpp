#include "CCE_NetEngine_UDPTransThread.h"
#include <QThread>
#include <QUdpSocket>
#include <QTime>

CCE_NetEngine_UDPTransThread::CCE_NetEngine_UDPTransThread(CCE_NetEngine* pThreadEngine, int nPayLoad /*= 4096*/, QObject *parent /*= 0*/)
    : CCE_NetEngine_TransThread(pThreadEngine, nPayLoad, parent)
{
    m_communicatType = ECommunicatType::ECT_UDP;
}

CCE_NetEngine_UDPTransThread::~CCE_NetEngine_UDPTransThread()
{
}

void CCE_NetEngine_UDPTransThread::closeSocket(QObject * objSocket)
{
    QUdpSocket* pSocket = qobject_cast<QUdpSocket*>(objSocket);
    if (pSocket)
    {
        disconnect(pSocket, &QUdpSocket::readyRead, this, &CCE_NetEngine_UDPTransThread::slot_New_Data_Recieved);
        disconnect(pSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &CCE_NetEngine_UDPTransThread::slot_DisplayError);
        disconnect(pSocket, &QUdpSocket::bytesWritten, this, &CCE_NetEngine_UDPTransThread::slot_Some_Data_Sended);

        m_buffer_sending.erase(pSocket);
        m_buffer_sending_offset.erase(pSocket);
        m_mutex_protect.lock();
        m_clientList.remove(pSocket);
        m_mutex_protect.unlock();
        pSocket->abort();
        pSocket->close();
        emit sig_SocketClosed(pSocket);
        emit sig_Message(pSocket, "Info>" + QString(tr("Client Closed.")));
        qDebug() << tr("Socket (%1)..Closed.").arg((quint64)pSocket);
        push_to_rabbish_can(pSocket);
    }
}

void CCE_NetEngine_UDPTransThread::slot_EstablishUDPConnection(CCE_NetEngine_TransThread* threadid, const QString& addr, quint16 port)
{
    if (threadid != this)
        return;
    QUdpSocket* socket_client = nullptr;
    socket_client = new QUdpSocket(this);

    if (socket_client)
    {
        if (socket_client->state() == socket_client->BoundState)
        {
            qDebug() << tr("UDP Socket Already Bound. IP:") << addr << tr(" Port:") << port;
            push_to_rabbish_can(socket_client);
            return;
        }

        if (socket_client->bind(QHostAddress(addr), port))
        {
            connect(socket_client, &QUdpSocket::readyRead, this, &CCE_NetEngine_UDPTransThread::slot_New_Data_Recieved/*, Qt::DirectConnection*/);
            connect(socket_client, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &CCE_NetEngine_UDPTransThread::slot_DisplayError, Qt::QueuedConnection);
            connect(socket_client, &QUdpSocket::bytesWritten, this, &CCE_NetEngine_UDPTransThread::slot_Some_Data_Sended, Qt::QueuedConnection);
            m_mutex_protect.lock();
            m_clientList.insert(socket_client);
            m_mutex_protect.unlock();
            emit sig_NewUDPConnectionEstablish(socket_client, addr, port);
        }
        else
        {
            qDebug() << tr("UDP Socket Bound Faild. IP:") << addr << tr(" Port:") << port;
            push_to_rabbish_can(socket_client);
            return;
        }
    }
    else
        Q_ASSERT(false);
}

void CCE_NetEngine_UDPTransThread::slot_SendData(QObject * objSocket, CCEEnginePackage package)
{
    m_mutex_protect.lock();
    if (m_clientList.contains(objSocket) == false)
    {
        m_mutex_protect.unlock();
        return;
    }
    m_mutex_protect.unlock();
    CCE_NetEngine_TransThread::slot_SendData(objSocket,package);
    QUdpSocket * pSocket = qobject_cast<QUdpSocket*>(objSocket);
    if (pSocket)
    {
        if (package.type() != m_communicatType || package.data().size() == 0)
        {
            return;
        }
        QList<CCEEnginePackage> & list_sock_data = m_buffer_sending[pSocket];
        QList<qint64> & list_offset = m_buffer_sending_offset[pSocket];
        if (list_sock_data.empty() == true)
        {
            qint64 bytesWritten = pSocket->writeDatagram(package.data().constData(),
                qMin(package.data().size(), m_nPayLoad), QHostAddress(package.hostAddress()), package.hostPort());
            //qDebug() << tr("UDP Socket Send. IP:") << package.hostAddress() << tr(" Port:")
                //<< package.hostPort() << tr(" Length:") << bytesWritten;
            if (bytesWritten < package.data().size())
            {
                list_sock_data.push_back(package);
                list_offset.push_back(bytesWritten);
            }
        }
        else
        {
            list_sock_data.push_back(package);
            list_offset.push_back(0);
        }
    }
}

void CCE_NetEngine_UDPTransThread::slot_New_Data_Recieved()
{
    QUdpSocket* pSocket = qobject_cast<QUdpSocket*>(sender());
    if (pSocket)
    {
        CCEEnginePackage udpPack(pSocket, m_communicatType, EPackageFromType::EPFT_Receive);
        if(pSocket->hasPendingDatagrams())
        {
            QByteArray recFromData;
            QHostAddress recFromAddr;
            quint16 recFromPort;
            recFromData.resize(pSocket->pendingDatagramSize());
            pSocket->readDatagram(recFromData.data(), recFromData.size(), &recFromAddr, &recFromPort);

            udpPack.setNetInfo(recFromAddr.toString(), recFromPort);
            udpPack.setData(recFromData);
            QString ip = recFromAddr.toString();
            ip = ip.replace("::ffff:", "");
            if (ip.isEmpty())
            {
                return;
            }
        }
        if (udpPack.data().size() != 0)
        {
            QString hostName = udpPack.hostName();
            //qDebug() << "slot_New_Data_Recieved form " << hostName;
            emit sig_Data_Received(pSocket, udpPack);
        }
    }
}

void CCE_NetEngine_UDPTransThread::slot_Some_Data_Sended(qint64 wsended)
{
    QUdpSocket* pSocket = qobject_cast<QUdpSocket*>(sender());
    if (pSocket)
    {
        QList<CCEEnginePackage> & list_sock_data = m_buffer_sending[pSocket];
        QList<qint64> & list_offset = m_buffer_sending_offset[pSocket];

        emit sig_Data_Sended(pSocket, wsended);
        while (list_sock_data.empty() == false)
        {
            CCEEnginePackage & arraySending = *list_sock_data.begin();
            if (arraySending.type() != m_communicatType || arraySending.data().size() == 0)
            {
                continue;;
            }
            qint64 & currentOffset = *list_offset.begin();
            qint64 nTotalBytes = arraySending.data().size();
            Q_ASSERT(nTotalBytes >= currentOffset);
            qint64 nBytesWritten = pSocket->writeDatagram(arraySending.data().constData() + currentOffset,
                qMin((int)(nTotalBytes - currentOffset), m_nPayLoad), QHostAddress(arraySending.hostAddress()), arraySending.hostPort());
            currentOffset += nBytesWritten;
            if (currentOffset >= nTotalBytes)
            {
                list_offset.pop_front();
                list_sock_data.pop_front();
            }
            else
                break;
        }
    }
}

void CCE_NetEngine_UDPTransThread::slot_DisplayError(QAbstractSocket::SocketError socketError)
{
    QUdpSocket* pSocket = qobject_cast<QUdpSocket*>(sender());
    if (pSocket)
    {
        qDebug() << pSocket->peerAddress().toString() <<
            pSocket->peerPort() << tr("(%1)..Error :%2.").arg((quint64)pSocket).arg(pSocket->errorString());
        emit sig_SocketError(pSocket, socketError);

        closeSocket(pSocket);
    }
}
