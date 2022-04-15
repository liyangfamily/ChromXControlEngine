#include "CCE_NetEngine_COMTransThread.h"
#include <QThread>

CCE_NetEngine_COMTransThread::CCE_NetEngine_COMTransThread(CCE_NetEngine * pThreadEngine, int nPayLoad, QObject * parent)
    : CCE_NetEngine_TransThread(pThreadEngine, nPayLoad, parent)
{
    m_communicatType = ECommunicatType::ECT_COM;
}

CCE_NetEngine_COMTransThread::~CCE_NetEngine_COMTransThread()
{
}

void CCE_NetEngine_COMTransThread::closeSocket(QObject * objSocket)
{
    QSerialPort* pSerialPort = qobject_cast<QSerialPort*>(objSocket);
    if (pSerialPort)
    {
        disconnect(pSerialPort, &QSerialPort::readyRead, this, &CCE_NetEngine_COMTransThread::slot_New_Data_Recieved);
        void (CCE_NetEngine_COMTransThread:: * displayError)(QSerialPort::SerialPortError) = &CCE_NetEngine_COMTransThread::slot_DisplayError;
        disconnect(pSerialPort, &QSerialPort::errorOccurred, this, displayError);
        disconnect(pSerialPort, &QSerialPort::bytesWritten, this, &CCE_NetEngine_COMTransThread::slot_Some_Data_Sended);

        m_buffer_sending.erase(pSerialPort);
        m_buffer_sending_offset.erase(pSerialPort);
        m_mutex_protect.lock();
        m_clientList.remove(pSerialPort);
        m_mutex_protect.unlock();
        pSerialPort->clear();
        pSerialPort->close();
        emit sig_SocketClosed(pSerialPort);
        emit sig_Message(pSerialPort, "Info>" + QString(tr("Client Closed.")));
        qDebug() << tr("Serial Port (%1)..Closed.").arg((quint64)pSerialPort);
        push_to_rabbish_can(pSerialPort);
    }
}

void CCE_NetEngine_COMTransThread::slot_EstablishCOMConnection(CCE_NetEngine_TransThread* threadid, QString comName)
{
    if (threadid != this)
        return;
    QSerialPort* serial_client = nullptr;
    serial_client = new QSerialPort(this);

    if (serial_client)
    {
        serial_client->setBaudRate(QSerialPort::Baud115200);//设置波特率和读写方向
        serial_client->setDataBits(QSerialPort::Data8);		//数据位为8位
        serial_client->setFlowControl(QSerialPort::HardwareControl);//硬件流控制
        serial_client->setParity(QSerialPort::NoParity);	//无校验位
        serial_client->setStopBits(QSerialPort::OneStop); //一位停止位
        if (serial_client->isOpen())
        {
            serial_client->clear();
            serial_client->close();
        }
        serial_client->setPortName(comName);
        if (!serial_client->open(QIODevice::ReadWrite))//用ReadWrite 的模式尝试打开串口
        {
            qDebug() << tr("SerialPort Open Faild.") << tr(" SerialName:") << comName;
            push_to_rabbish_can(serial_client);
            return;
        }
        serial_client->setDataTerminalReady(true);
        connect(serial_client, &QSerialPort::readyRead, this, &CCE_NetEngine_COMTransThread::slot_New_Data_Recieved/*, Qt::QueuedConnection*/);
        void (CCE_NetEngine_COMTransThread:: * displayError)(QSerialPort::SerialPortError) = &CCE_NetEngine_COMTransThread::slot_DisplayError;
        connect(serial_client, &QSerialPort::errorOccurred, this, displayError, Qt::QueuedConnection);
        connect(serial_client, &QSerialPort::bytesWritten, this, &CCE_NetEngine_COMTransThread::slot_Some_Data_Sended, Qt::QueuedConnection);

        m_mutex_protect.lock();
        m_clientList.insert(serial_client);
        m_mutex_protect.unlock();
        emit sig_NewCOMConnectionEstablish(serial_client, comName);
    }
    else
        Q_ASSERT(false);
}

void CCE_NetEngine_COMTransThread::slot_SendData(QObject * objSocket, CCEEnginePackage package)
{
    m_mutex_protect.lock();
    if (m_clientList.contains(objSocket) == false)
    {
        m_mutex_protect.unlock();
        return;
    }
    m_mutex_protect.unlock();
    CCE_NetEngine_TransThread::slot_SendData(objSocket,package);
    QSerialPort * pSocket = qobject_cast<QSerialPort*>(objSocket);
    if (pSocket)
    {
        if (package.type() != m_communicatType || package.data().size() == 0)
        {
            qDebug() << "CCE_NetEngine_COMTransThread::slot_SendData------packageType can't matched or data is empty.";
            return;
        }
        QList<CCEEnginePackage> & list_sock_data = m_buffer_sending[pSocket];
        QList<qint64> & list_offset = m_buffer_sending_offset[pSocket];
        if (list_sock_data.empty() == true)
        {
            qint64 bytesWritten = pSocket->write(package.data().constData(),
                qMin(package.data().size(), m_nPayLoad));
            //qDebug() << tr("Serial Port Send. Name:") << pSocket->portName() << tr(" Length:") << bytesWritten;
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

#include <CCE_Core/CCEUIHelper.h>
void CCE_NetEngine_COMTransThread::slot_New_Data_Recieved()
{
    QSerialPort* pSocket = qobject_cast<QSerialPort*>(sender());
    if (pSocket)
    {
        CCEEnginePackage comPack(pSocket, m_communicatType, EPackageFromType::EPFT_Receive);
        int avilableCount = pSocket->bytesAvailable();
        if (avilableCount > 0)
        {
            QByteArray recFromData;
            recFromData = pSocket->readAll();
            comPack.setData(recFromData);
            comPack.setComName(pSocket->portName());
            if (comPack.data().isEmpty())
            {
                return;
            }
            else
            {
                emit sig_Data_Received(pSocket, comPack);
            }
        }
    }
}

void CCE_NetEngine_COMTransThread::slot_Some_Data_Sended(qint64 wsended)
{
    QSerialPort* pSocket = qobject_cast<QSerialPort*>(sender());
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
                continue;
            }
            qint64 & currentOffset = *list_offset.begin();
            qint64 nTotalBytes = arraySending.data().size();
            Q_ASSERT(nTotalBytes >= currentOffset);
            qint64 nBytesWritten = pSocket->write(arraySending.data().constData() + currentOffset,
                qMin((int)(nTotalBytes - currentOffset), m_nPayLoad));
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

void CCE_NetEngine_COMTransThread::slot_DisplayError(QSerialPort::SerialPortError serialError)
{
    QSerialPort* pSocket = qobject_cast<QSerialPort*>(sender());
    if (pSocket)
    {
        qDebug() << pSocket->portName() << tr("(%1)..Error :%2.").arg((quint64)pSocket).arg(pSocket->errorString());
        emit sig_SocketError(pSocket, serialError);

        closeSocket(pSocket);
    }
}
