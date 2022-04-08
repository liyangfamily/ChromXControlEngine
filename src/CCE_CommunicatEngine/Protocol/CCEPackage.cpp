/*********************************************************************************************************
** This file is part of the CCE_CommunicatEngine module of the CCE Toolkit.
*********************************************************************************************************/

/*!
\class CCEPackage

\inmodule CCE_CommunicatEngine

\brief The class is an abstract class of intelCtrl protocol packages.

CCEPackage::build(): it is responsible for constructing data packets in accordance with the protocol.

\code

\endcode

\note:
This class is the base class of all protocol packets and is generally not use.
*/

#include "CCE_CommunicatEngine/CCEPackage.h"

static quint16 g_serialNum = 0;

CCEPackage::CCEPackage()
{
}

CCEPackage::CCEPackage(const QByteArray & data) :m_data(data)
{
}

CCEPackage::~CCEPackage()
{
}

CCEPackage::CCEPackage(const CCEPackage & package)
{
    *this = package;
}

CCEPackage & CCEPackage::operator=(const CCEPackage & package)
{
    if (this == &package)
    {
        return *this;
    }
    m_data = package.m_data;

    m_targetDeviceType = package.m_targetDeviceType;
    m_sourceDeviceType = package.m_sourceDeviceType;
    m_uuidType = package.m_uuidType;
    m_uuid = package.m_uuid;
    m_sendCardIndex = package.m_sendCardIndex;
    return *this;
}

QByteArray CCEPackage::getDataToSend() const
{
    return m_data;
}

bool CCEPackage::initByDetectInfo(const SDetectItemInfo* info)
{
    if (!info)
    {
        return false;
    }
    this->m_uuidType = info->uuidType;
    this->m_uuid = info->uuid;
    this->m_sendCardIndex = info->senderCardIndex;
    return true;
}

void CCEPackage::SetCmdTargetDevice(quint16 n)
{
    m_targetDeviceType = n;
}

void CCEPackage::SetCmdSourceDevice(quint16 n)
{
    m_sourceDeviceType = n;
}

void CCEPackage::SetCmdUuidType(quint8 n)
{
    m_uuidType = n;
}

void CCEPackage::SetCmdUuid(QUuid n)
{
    m_uuid = n;
}

void CCEPackage::SetCmdSenderIndex(quint8 n)
{
    m_sendCardIndex = n;
}

quint8 CCEPackage::getProtocolNum() const
{
    QByteArray headerData = getData(m_data, EDataBlock::EDB_Header);
    if (headerData.isEmpty())
    {
        return 0;
    }
    const SIntegratedCtrlHeader *pHeader = (const SIntegratedCtrlHeader*)headerData.constData();
    return pHeader->protocolHeader.protocolNum;
}

quint8 CCEPackage::getProtocolVersion() const
{
    QByteArray headerData = getData(m_data, EDataBlock::EDB_Header);
    if (headerData.isEmpty())
    {
        return 0;
    }
    const SIntegratedCtrlHeader *pHeader = (const SIntegratedCtrlHeader*)headerData.constData();
    return pHeader->protocolHeader.protocolVersion;
}

quint16 CCEPackage::getCmdNum() const
{
    QByteArray headerData = getData(m_data, EDataBlock::EDB_Header);
    if (headerData.isEmpty())
    {
        return 0;
    }
    const SIntegratedCtrlHeader *pHeader = (const SIntegratedCtrlHeader*)headerData.constData();
    return pHeader->cmd;
}

QByteArray CCEPackage::getContent() const
{
    QByteArray data = getData(m_data, EDataBlock::EDB_Content);
    if (data.isEmpty())
    {
        return QByteArray();
    }
    return data;
}

quint16 CCEPackage::getSerialNum() const
{
    QByteArray headerData = getData(m_data, EDataBlock::EDB_Header);
    if (headerData.isEmpty())
    {
        return 0;
    }
    const SIntegratedCtrlHeader *pHeader = (const SIntegratedCtrlHeader*)headerData.constData();
    return pHeader->serialNumber;
}

quint8 CCEPackage::getCheckSum() const
{
    QByteArray data = getData(m_data, EDataBlock::EDB_CheckSum);
    if (data.isEmpty())
    {
        return 0;
    }
    return data.front();
}

quint16 CCEPackage::getTargetDevice() const
{
    QByteArray headerData = getData(m_data, EDataBlock::EDB_Header);
    if (headerData.isEmpty())
    {
        return 0;
    }
    const SIntegratedCtrlHeader *pHeader = (const SIntegratedCtrlHeader*)headerData.constData();
    return pHeader->targetDeviceType;
}

quint16 CCEPackage::getSourceDevice() const
{
    QByteArray headerData = getData(m_data, EDataBlock::EDB_Header);
    if (headerData.isEmpty())
    {
        return 0;
    }
    const SIntegratedCtrlHeader *pHeader = (const SIntegratedCtrlHeader*)headerData.constData();
    return pHeader->sourceDeviceType;
}

quint8 CCEPackage::getUuidType() const
{
    QByteArray headerData = getData(m_data, EDataBlock::EDB_Header);
    if (headerData.isEmpty())
    {
        return 0;
    }
    const SIntegratedCtrlHeader *pHeader = (const SIntegratedCtrlHeader*)headerData.constData();
    return pHeader->uuidType;
}

QUuid CCEPackage::getUuid() const
{
    QByteArray headerData = getData(m_data, EDataBlock::EDB_Header);
    if (headerData.isEmpty())
    {
        return 0;
    }
    const SIntegratedCtrlHeader *pHeader = (const SIntegratedCtrlHeader*)headerData.constData();
    return pHeader->uuid;
}

quint8 CCEPackage::getSenderCardIndex() const
{
    QByteArray headerData = getData(m_data, EDataBlock::EDB_Header);
    if (headerData.isEmpty()) {
        return 0;
    }
    const SIntegratedCtrlHeader *pHeader = (const SIntegratedCtrlHeader*)headerData.constData();
    return pHeader->sendCardIndex;
}

quint16 CCEPackage::getReplayDataLength() const
{
    QByteArray headerData = getData(m_data, EDataBlock::EDB_Header);
    if (headerData.isEmpty()) {
        return 0;
    }
    const SIntegratedCtrlHeader *pHeader = (const SIntegratedCtrlHeader*)headerData.constData();
    return pHeader->dataLength;
}

quint8 CCEPackage::genCheckSum()
{
    quint8 tempCheckSum = 0;
    try
    {
        if (m_data.size() < 9)
        {
            return tempCheckSum;
        }
        QByteArray arrCpy(m_data.data() + 8, m_data.size() - 8);
        tempCheckSum = getCheckSum(arrCpy);
    }
    catch (std::exception e) {
        qDebug() << "CCEPackageInteCtrl::" << "getCheckSum Error : %s "<< e.what();
    }
    return tempCheckSum;
}

quint8 CCEPackage::getCheckSum(const QByteArray & data)
{
    //计算和
    if (data.isEmpty() || data.isNull())
    {
        return 0;
    }

    unsigned char sum = 0;
    for (int i = 0; i < data.size(); i++)
    {
        sum += data.at(i);
    }
    return sum;
}

CCEPackage & CCEPackage::build(quint16 serialNum)
{
    Q_UNUSED(serialNum)
    m_data.clear();

    SIntegratedCtrlHeader sendHeader;
    sendHeader.protocolHeader.protocolNum = CmdProtocolNum();
    sendHeader.protocolHeader.protocolVersion = CmdProtocolVersion();
    sendHeader.targetDeviceType = CmdTargetDevice();
    sendHeader.sourceDeviceType = CmdSourceDevice();
    sendHeader.cmd = CmdNum();
    sendHeader.serialNumber = g_serialNum++;
    sendHeader.uuidType = CmdUuidType();
    sendHeader.uuid = CmdUuid();
    sendHeader.sendCardIndex = CmdSenderIndex();
    sendHeader.dataLength = CmdContent().size();
    m_data.append((char*)(&sendHeader), sizeof(SIntegratedCtrlHeader));
    if (sendHeader.dataLength > 0)
    {
        //拷贝数据内容
        m_data.append(CmdContent());
    }
    //计算和
    quint8 tempCheckSum = genCheckSum();
    m_data.append(tempCheckSum);
    return *this;
}


quint8 CCEPackage::CmdProtocolNum() const
{
    qDebug() << "CCEPackage::you need to implement ProtocolNum(const QByteArray & data) into Subclass.";
    return quint8();
}

quint8 CCEPackage::CmdProtocolVersion() const
{
    qDebug() << "CCEPackage::you need to implement ProtocolVersion() into Subclass.";
    return quint8();
}

quint16 CCEPackage::CmdNum() const
{
    qDebug() << "CCEPackage::you need to implement CmdNum() into Subclass.";
    return quint16();
}

quint16 CCEPackage::CmdRetNum() const
{
    qDebug() << "CCEPackage::you need to implement CmdRetNum() into Subclass.";
    return quint16();
}

QByteArray CCEPackage::CmdContent() const
{
    qDebug() << "CCEPackage::you need to implement CmdContent() into Subclass.";
    return QByteArray();
}

quint16 CCEPackage::CmdTargetDevice() const
{
    return m_targetDeviceType;
}

quint16 CCEPackage::CmdSourceDevice() const
{
    return m_sourceDeviceType;
}

quint8 CCEPackage::CmdUuidType() const
{
    return m_uuidType;
}

QUuid CCEPackage::CmdUuid() const
{
    return m_uuid;
}

quint8 CCEPackage::CmdSenderIndex() const
{
    return m_sendCardIndex;
}

void CCEPackage::onReceive(const CCEPackage & package)
{
    m_callBack(package.getDataToSend());
}

QByteArray CCEPackage::getData(const QByteArray & data, quint8 index)
{
    QByteArray tempData;
    quint64 datalen = data.size();
    if (datalen < sizeof(SIntegratedCtrlHeader))
    {
        return tempData;
    }
    switch (EDataBlock(index))
    {
    case CCEPackage::EDB_Header:
    {
        //头数据
        tempData.append(data.data(), sizeof(SIntegratedCtrlHeader));
    }
    break;
    case CCEPackage::EDB_Content:
    {
        //校验包长度
        if (datalen <= (sizeof(SIntegratedCtrlHeader) + 1))
        {
            return tempData;
        }
        int byteLeft = datalen - sizeof(SIntegratedCtrlHeader) - 1;
        tempData.append(data.data() + sizeof(SIntegratedCtrlHeader), byteLeft);
    }
    break;
    case CCEPackage::EDB_CheckSum:
    {
        //校验包长度
        if (datalen <= (sizeof(SIntegratedCtrlHeader) + 1))
        {
            return tempData;
        }
        tempData.append(data.back());
    }
    break;
    default:
        break;
    }
    return tempData;
}
