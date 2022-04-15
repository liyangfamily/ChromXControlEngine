#include "CCE_TaskEngine_IntegratedCtrlTask.h"
#include "CCE_CommunicatEngine/CCECluster.h"
#include "CCE_CommunicatEngine/CCESocketLock.h"

#include <QSerialPort>
#include <QUdpSocket>

int g_COMParsingFaidCount = 0;
int g_UDPParsingFaidCount = 0;
int g_CheckSumSize = 2;

CCE_TaskEngine_IntegratedCtrlTask::CCE_TaskEngine_IntegratedCtrlTask(CCECluster * pCluster, QObject * pSocket, QObject * parent)
    :CCE_TaskEngine_TaskBase(parent), m_pCluster(pCluster)
{
    m_pSocket = pSocket;
    m_standerFrameLimit.build();
    m_last_Report = QDateTime::currentDateTime();
}

CCE_TaskEngine_IntegratedCtrlTask::~CCE_TaskEngine_IntegratedCtrlTask()
{
}

int CCE_TaskEngine_IntegratedCtrlTask::run()
{
    int nCurrSz = -1;
    //每次处理的消息个数
    int nMessage = m_nMessageBlockSize;
    while (--nMessage >= 0 && nCurrSz != 0)
    {
        CCEEnginePackage block;
        m_mutex_rawData.lock();
        if (m_list_RawData.size())
            block = (*m_list_RawData.begin());
        m_mutex_rawData.unlock();
        if (block.data().isEmpty() == false && block.data().isNull() == false)
        {
            m_currentReadOffset = filter_message(block, m_currentReadOffset);
            if (m_currentReadOffset >= block.data().size())
            {
                m_mutex_rawData.lock();
                if (m_list_RawData.empty() == false)
                    m_list_RawData.pop_front();
                else
                    Q_ASSERT(false);
                m_currentReadOffset = 0;
                m_mutex_rawData.unlock();
            }
        }
        else
        {
            m_mutex_rawData.lock();
            //pop 空消息
            if (m_list_RawData.empty() == false)
                m_list_RawData.pop_front();
            m_mutex_rawData.unlock();
        }
        m_mutex_rawData.lock();
        nCurrSz = m_list_RawData.size();
        m_mutex_rawData.unlock();
    }
    m_mutex_rawData.lock();
    nCurrSz = m_list_RawData.size();
    m_mutex_rawData.unlock();
    if (nCurrSz == 0)
        return 0;
    return -1;
}

void CCE_TaskEngine_IntegratedCtrlTask::sendHelloPackage()
{
    qDebug() << "CCE_TaskEngine_IntegratedCtrlTask::you need to implement sendHelloPackage() into Subclass.";
    return;
}

void CCE_TaskEngine_IntegratedCtrlTask::checkHeartBeating()
{
    QDateTime dtm = QDateTime::currentDateTime();
    qint64 usc = this->m_last_Report.secsTo(dtm);
    int nThredHold = m_pCluster->heartBeatingThrdHold();
    if (usc >= nThredHold)
    {
        emit sig_Message(this, tr("Client ") + QString("%1").arg((unsigned int)((quint64)this)) + tr(" is dead, kick out."));
        emit sig_Disconnect(this->socketObj());
    }
}

int CCE_TaskEngine_IntegratedCtrlTask::filter_message(const CCEEnginePackage& block, int offset)
{
    const int blocklen = block.data().length();
    //! [0]
    while (blocklen > offset)
    {
        const char * dataptr = block.data().constData();

        //开始解析
        while (m_currentMessageSize<sizeof(SIntegratedFrameLimit) && blocklen>offset)
        {
            m_currentBlock.push_back(dataptr[offset++]);
            m_currentMessageSize++;
        }
        if (m_currentMessageSize < sizeof(SIntegratedFrameLimit)) //帧头未完成
            continue;

        if (m_currentMessageSize == sizeof(SIntegratedFrameLimit))
        {
            const char * headerptr = m_currentBlock.constData();
            memcpy((void *)&m_currentFrameLimit, headerptr, sizeof(SIntegratedFrameLimit));
        }

        if (m_currentFrameLimit == m_standerFrameLimit)
            //可用的帧
            //! [1]
        {
            offset = filter_identifyProtocolHeader(block,offset);
#if(0)
            if (m_currentMessageSize< sizeof(SIntegratedCtrlHeader) && blocklen>offset)
            {
                int nCpy = int(sizeof(SIntegratedCtrlHeader) - m_currentMessageSize);
                if (nCpy > blocklen - offset)
                    nCpy = blocklen - offset;
                QByteArray arrCpy(dataptr + offset, nCpy);
                m_currentBlock.push_back(arrCpy);
                offset += nCpy;
                m_currentMessageSize += nCpy;
            }
            //! [2]
            if (m_currentMessageSize < sizeof(SIntegratedCtrlHeader)) //包头未完成
                continue;
            else if (m_currentMessageSize == sizeof(SIntegratedCtrlHeader))//包头刚刚完成
            {
                const char * headerptr = m_currentBlock.constData();
                memcpy((void *)&m_currentHeader, headerptr, sizeof(SIntegratedCtrlHeader));

                //如果有数据剩下则继续读
                if (block.data().length() > offset)
                {
                    qint32 byteLeft = quint32(m_currentHeader.dataLength + sizeof(SIntegratedCtrlHeader) + 2
                                              - m_currentMessageSize);
                    if (byteLeft > 0 && blocklen > offset)
                    {
                        int nCpy = byteLeft;
                        if (nCpy > blocklen - offset)
                            nCpy = blocklen - offset;
                        QByteArray arrCpy(dataptr + offset, nCpy);
                        m_currentBlock.push_back(arrCpy);
                        offset += nCpy;
                        m_currentMessageSize += nCpy;
                        byteLeft -= nCpy;
                    }
                    //尽快处理数据块
                    deal_current_message_block(block);
                    if (byteLeft > 0)
                        continue;

                    //帧处理完毕，开始处理下一个
                    m_currentMessageSize = 0;
                    m_currentBlock = QByteArray();
                    continue;
                }
            }
            else
            {
                //如果有数据剩下则继续读
                if (block.data().length() > offset)
                {
                    qint32 byteLeft = quint32(m_currentHeader.dataLength + sizeof(SIntegratedCtrlHeader) + 2
                                              - m_currentMessageSize);
                    if (byteLeft > 0 && blocklen > offset)
                    {
                        int nCpy = byteLeft;
                        if (nCpy > blocklen - offset)
                            nCpy = blocklen - offset;
                        QByteArray arrCpy(dataptr + offset, nCpy);
                        m_currentBlock.push_back(arrCpy);
                        offset += nCpy;
                        m_currentMessageSize += nCpy;
                        byteLeft -= nCpy;
                    }
                    //尽快处理数据块
                    deal_current_message_block(block);
                    if (byteLeft > 0)
                        continue;
                    //帧处理完毕，开始处理下一个
                    m_currentMessageSize = 0;
                    m_currentBlock = QByteArray();
                    continue;
                }
            } //! [2]
#endif
        } //! [1]
        else
        {
            if (block.type() == ECommunicatType::ECT_COM)
            {
                qDebug() << "COM ParsingFaid Count: " << ++g_COMParsingFaidCount;
            }
            else
            {
                qDebug() << "UDP ParsingFaid Count: " << ++g_UDPParsingFaidCount;
            }
            m_currentMessageSize = 0;
            m_currentBlock = QByteArray();
            offset = blocklen;
        }
    } //! [0]

    return offset;
}

int CCE_TaskEngine_IntegratedCtrlTask::filter_identifyProtocolHeader(const CCEEnginePackage& block, int offset)
{
    const int blocklen = block.data().length();
    const char * dataptr = block.data().constData();
    //先检测是否满足协议头
    if (m_currentMessageSize< sizeof(SIntegratedCtrlProtocolHeader) && blocklen>offset)
    {
        int nCpy = int(sizeof(SIntegratedCtrlProtocolHeader) - m_currentMessageSize);
        if (nCpy > blocklen - offset)
            nCpy = blocklen - offset;
        QByteArray arrCpy(dataptr + offset, nCpy);
        m_currentBlock.push_back(arrCpy);
        offset += nCpy;
        m_currentMessageSize += nCpy;
    }
    //! [2]
    if (m_currentMessageSize < sizeof(SIntegratedCtrlProtocolHeader)) //协议头未完成
        return offset;
    else{
        //协议头刚刚完成
        SIntegratedCtrlProtocolHeader _currentProtocolHeader;
        const char * headerptr = m_currentBlock.constData();
        memcpy((void *)&_currentProtocolHeader, headerptr, sizeof(SIntegratedCtrlProtocolHeader));

        //如果有数据剩下则继续读
        if (block.data().length() > offset)
        {
            return filter_identifyStandardHeader(block,offset);
        }
    }
    return offset;
}

int CCE_TaskEngine_IntegratedCtrlTask::filter_identifyStandardHeader(const CCEEnginePackage& block, int offset)
{
    const int blocklen = block.data().length();
    const char * dataptr = block.data().constData();
    //再检测是否满足标准头
    if (m_currentMessageSize< sizeof(SIntegratedCtrlHeader) && blocklen>offset)
    {
        int nCpy = int(sizeof(SIntegratedCtrlHeader) - m_currentMessageSize);
        if (nCpy > blocklen - offset)
            nCpy = blocklen - offset;
        QByteArray arrCpy(dataptr + offset, nCpy);
        m_currentBlock.push_back(arrCpy);
        offset += nCpy;
        m_currentMessageSize += nCpy;
    }
    //! [2]
    if (m_currentMessageSize < sizeof(SIntegratedCtrlHeader)) //包头未完成
        return offset;
    else if (m_currentMessageSize == sizeof(SIntegratedCtrlHeader))//包头刚刚完成
    {
        const char * headerptr = m_currentBlock.constData();
        memcpy((void *)&m_currentHeader, headerptr, sizeof(SIntegratedCtrlHeader));

        //如果有数据剩下则继续读
        if (block.data().length() > offset)
        {
            qint32 byteLeft = quint32(m_currentHeader.dataLength + sizeof(SIntegratedCtrlHeader) + g_CheckSumSize
                - m_currentMessageSize);
            if (byteLeft > 0 && blocklen > offset)
            {
                int nCpy = byteLeft;
                if (nCpy > blocklen - offset)
                    nCpy = blocklen - offset;
                QByteArray arrCpy(dataptr + offset, nCpy);
                m_currentBlock.push_back(arrCpy);
                offset += nCpy;
                m_currentMessageSize += nCpy;
                byteLeft -= nCpy;
            }
            //尽快处理数据块
            deal_current_message_block(block);
            if (byteLeft > 0)
                return offset;

            //帧处理完毕，开始处理下一个
            m_currentMessageSize = 0;
            m_currentBlock = QByteArray();
            offset = blocklen;
        }
    }
    else
    {
        //如果有数据剩下则继续读
        if (block.data().length() > offset)
        {
            qint32 byteLeft = quint32(m_currentHeader.dataLength + sizeof(SIntegratedCtrlHeader) + g_CheckSumSize
                - m_currentMessageSize);
            if (byteLeft > 0 && blocklen > offset)
            {
                int nCpy = byteLeft;
                if (nCpy > blocklen - offset)
                    nCpy = blocklen - offset;
                QByteArray arrCpy(dataptr + offset, nCpy);
                m_currentBlock.push_back(arrCpy);
                offset += nCpy;
                m_currentMessageSize += nCpy;
                byteLeft -= nCpy;
            }
            //尽快处理数据块
            deal_current_message_block(block);
            if (byteLeft > 0)
                return offset;
            //帧处理完毕，开始处理下一个
            m_currentMessageSize = 0;
            m_currentBlock = QByteArray();
            offset = blocklen;
        }
    } //! [2]
    return offset;
}

int CCE_TaskEngine_IntegratedCtrlTask::deal_current_message_block(const CCEEnginePackage& block)
{
    Q_UNUSED(block)
    qint32 byteLeft = quint32(m_currentHeader.dataLength + sizeof(SIntegratedCtrlHeader) + g_CheckSumSize
        - m_currentMessageSize);

    if (byteLeft == 0)
    {
        qDebug() << "CCE_TaskEngine_IntegratedCtrlTask::you need to implement deal_current_message_block() into Subclass.";
        CCEEnginePackage pack(socketObj(), ECommunicatType::ECT_NULL, EPackageFromType::EPFT_Receive);
        emit sig_ParsingInteCtrlDataFrame(socketObj(), pack);
    }

    return 0;
}

/*********************************************************************************************************
*网络集控任务
*********************************************************************************************************/

CCE_TaskEngine_IntegratedCtrlUDPTask::CCE_TaskEngine_IntegratedCtrlUDPTask(CCECluster * pCluster, QObject * pSocket, QObject * parent)
    :CCE_TaskEngine_IntegratedCtrlTask(pCluster, pSocket, parent)
{
    QUdpSocket* pUdpSocket = qobject_cast<QUdpSocket*>(socketObj());
    if (pUdpSocket)
    {
        QString socketAddress = pUdpSocket->localAddress().toString();
        m_targetPort = pUdpSocket->localPort();

        QList<QNetworkInterface> _interfaceList = QNetworkInterface::allInterfaces();
        foreach(QNetworkInterface _interface, _interfaceList) {
            QString str = _interface.humanReadableName();
            if (_interface.flags().testFlag(QNetworkInterface::IsUp)
                && _interface.flags().testFlag(QNetworkInterface::IsRunning)
                && _interface.flags().testFlag(QNetworkInterface::CanBroadcast)
                && _interface.flags().testFlag(QNetworkInterface::CanMulticast)
                && !_interface.flags().testFlag(QNetworkInterface::IsLoopBack)) {
                QList<QNetworkAddressEntry> _entryList = _interface.addressEntries();
                foreach(QNetworkAddressEntry _entry, _entryList) {
                    if (_entry.ip().protocol() == QAbstractSocket::IPv4Protocol) {
                        QString tempIP = _entry.ip().toString();
                        if (tempIP == socketAddress) {
                            QString broadCastIP = _entry.broadcast().toString();
                            if (broadCastIP.isEmpty()) {
                                continue;
                            }

                            m_broadCastIP = broadCastIP;
                        }
                    }
                }
            }
        }
    }
}

CCE_TaskEngine_IntegratedCtrlUDPTask::~CCE_TaskEngine_IntegratedCtrlUDPTask()
{
}

void CCE_TaskEngine_IntegratedCtrlUDPTask::sendHelloPackage()
{
    //替换为读取版本命令
    CCEMainCtrlPackage_ReadHardwareVersion detectInfo;
    detectInfo.build();
    QByteArray writeData = detectInfo.getDataToSend();
    CCEEnginePackage pack(socketObj(), ECommunicatType::ECT_UDP);
    pack.setNetInfo(m_broadCastIP, m_targetPort);
    pack.setData(writeData);

    emit sig_SendData(socketObj(), pack);
}

int CCE_TaskEngine_IntegratedCtrlUDPTask::deal_current_message_block(const CCEEnginePackage& block)
{
    qint32 byteLeft = quint32(m_currentHeader.dataLength + sizeof(SIntegratedCtrlHeader) + g_CheckSumSize
        - m_currentMessageSize);
    if (byteLeft == 0)
    {
        CCEEnginePackage pack(socketObj(), ECommunicatType::ECT_UDP, EPackageFromType::EPFT_Receive);
        pack.setNetInfo(block.hostAddress(), block.hostPort());
        pack.setData(m_currentBlock);
        //qDebug() << "ParsingDataFrame form " << pack.hostName();
        emit sig_ParsingInteCtrlDataFrame(socketObj(), pack);
    }
    return byteLeft;
}

/*********************************************************************************************************
*串口集控任务
*********************************************************************************************************/

CCE_TaskEngine_IntegratedCtrlCOMTask::CCE_TaskEngine_IntegratedCtrlCOMTask(CCECluster* pCluster, QObject* pSocket, QObject * parent /*= 0*/)
    :CCE_TaskEngine_IntegratedCtrlTask(pCluster, pSocket, parent)
{
}

CCE_TaskEngine_IntegratedCtrlCOMTask::~CCE_TaskEngine_IntegratedCtrlCOMTask()
{
}

#include <QUuid>
void CCE_TaskEngine_IntegratedCtrlCOMTask::sendHelloPackage()
{
    CCEMainCtrlPackage_ReadHardwareVersion detectInfo;
    detectInfo.build();
    QByteArray writeData = detectInfo.getDataToSend();

    CCEEnginePackage pack(socketObj(), ECommunicatType::ECT_COM);
    QSerialPort* pSocket = qobject_cast<QSerialPort*>(socketObj());
    if (pSocket)
    {
        pack.setComName(pSocket->portName());
        pack.setData(writeData);

        emit sig_SendData(socketObj(), pack);
    }
}

int CCE_TaskEngine_IntegratedCtrlCOMTask::deal_current_message_block(const CCEEnginePackage &block)
{
    qint32 byteLeft = quint32(m_currentHeader.dataLength + sizeof(SIntegratedCtrlHeader) + g_CheckSumSize
        - m_currentMessageSize);
    if (byteLeft == 0)
    {
        CCEEnginePackage pack(socketObj(), ECommunicatType::ECT_COM, EPackageFromType::EPFT_Receive);
        pack.setComName(block.comName());
        pack.setData(m_currentBlock);
        emit sig_ParsingInteCtrlDataFrame(socketObj(), pack);
    }
    return byteLeft;
}
