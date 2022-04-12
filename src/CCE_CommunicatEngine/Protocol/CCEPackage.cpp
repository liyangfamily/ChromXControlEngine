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
#include <CCE_Core/CCEUIHelper>
#include <memory>

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

    return *this;
}

QByteArray CCEPackage::getDataToSend() const
{
    return m_data;
}

bool CCEPackage::isValid()
{
    if (m_data.size() < sizeof(SIntegratedCtrlHeader) + sizeof(SIntegratedFrameLimit))
    {
        return false;
    }
    QByteArray arrCpy(m_data.data() + sizeof(SIntegratedFrameLimit), m_data.size() - sizeof(SIntegratedFrameLimit) - sizeof(quint16));
    quint16 tempCheckSum = computCheckSum(arrCpy);
    return (tempCheckSum==getCheckSum());
}

quint8 CCEPackage::getFrameLength() const
{
    QByteArray headerData = getData(m_data, EDataBlock::EDB_Header);
    if (headerData.isEmpty())
    {
        return 0;
    }
    const SIntegratedCtrlHeader *pHeader = (const SIntegratedCtrlHeader*)headerData.constData();
    return pHeader->protocolHeader.frameLength;
}

quint8 CCEPackage::getFrameType() const
{
    QByteArray headerData = getData(m_data, EDataBlock::EDB_Header);
    if (headerData.isEmpty())
    {
        return 0;
    }
    const SIntegratedCtrlHeader *pHeader = (const SIntegratedCtrlHeader*)headerData.constData();
    return pHeader->protocolHeader.frameType;
}

quint8 CCEPackage::getUnitAddr() const
{
    QByteArray headerData = getData(m_data, EDataBlock::EDB_Header);
    if (headerData.isEmpty())
    {
        return 0;
    }
    const SIntegratedCtrlHeader *pHeader = (const SIntegratedCtrlHeader*)headerData.constData();
    return pHeader->unitAddr;
}

quint16 CCEPackage::getCtrlAddr() const
{
    QByteArray headerData = getData(m_data, EDataBlock::EDB_Header);
    if (headerData.isEmpty())
    {
        return 0;
    }
    const SIntegratedCtrlHeader *pHeader = (const SIntegratedCtrlHeader*)headerData.constData();
    return CCEUIHelper::bigLittleSwap16(pHeader->ctrlAddr);
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

quint16 CCEPackage::getCheckSum() const
{
    QByteArray data = getData(m_data, EDataBlock::EDB_CheckSum);
    if (data.isEmpty())
    {
        return 0;
    }
    quint16 checkSum = 0;
    memcpy(&checkSum,data.data(),sizeof(checkSum));
    return CCEUIHelper::bigLittleSwap16(checkSum);
}

quint16 CCEPackage::computCheckSum(const QByteArray & data)
{
    CCEUIHelper::getCRCCode(data);
}


quint16 CCEPackage::genCheckSum()
{
    quint8 tempCheckSum = 0;
    try
    {
        if (m_data.size() < sizeof(SIntegratedCtrlHeader) + 2)
        {
            return tempCheckSum;
        }
        QByteArray arrCpy(m_data.data() + 2, m_data.size() - 2);
        tempCheckSum = computCheckSum(arrCpy);
    }
    catch (std::exception e) {
        qDebug() << "CCEPackageInteCtrl::" << "getCheckSum Error : %s "<< e.what();
    }
    return tempCheckSum;
}


CCEPackage & CCEPackage::build()
{
    m_data.clear();

    SIntegratedCtrlHeader sendHeader;
    sendHeader.protocolHeader.frameType = CmdFrameType();
    sendHeader.unitAddr = CmdUnitAddr();
    sendHeader.ctrlAddr = CCEUIHelper::bigLittleSwap16(CmdCtrlAddr());
    sendHeader.dataLength = CmdContent().size();

    m_data.append((char*)(&sendHeader), sizeof(SIntegratedCtrlHeader));
    if (sendHeader.dataLength > 0)
    {
        //拷贝数据内容
        m_data.append(CmdContent());
    }

    //此时计算组包长度，填入到帧长度，再计算校验和
    sendHeader.protocolHeader.frameLength = CmdFrameLength();

    //计算和
    quint16 tempCheckSum = CCEUIHelper::bigLittleSwap16(genCheckSum());
    m_data.append(tempCheckSum);
    return *this;
}

quint8 CCEPackage::CmdFrameLength() const
{
    return m_data.size();
    //qDebug() << "CCEPackage::you need to implement CmdFrameLength() into Subclass.";
    //return quint8();
}

CCEPackage::EFrameType CCEPackage::CmdFrameType() const
{
    qDebug() << "CCEPackage::you need to implement FrameType() into Subclass.";
    return EFrameType::EFT_NULL;
}

CCEPackage::EUnitAddr CCEPackage::CmdUnitAddr() const
{
    qDebug() << "CCEPackage::you need to implement CmdUnitAddr() into Subclass.";
    return EUnitAddr::EUA_NULL;
}

quint16 CCEPackage::CmdCtrlAddr() const
{
    qDebug() << "CCEPackage::you need to implement CmdCtrlAddr() into Subclass.";
    return quint16();
}

QByteArray CCEPackage::CmdContent() const
{
    qDebug() << "CCEPackage::you need to implement CmdContent() into Subclass.";
    return QByteArray();
}

void CCEPackage::onReceive(const CCEPackage & package)
{
    m_callBack(package.getDataToSend());
}

QByteArray CCEPackage::getData(const QByteArray & data, quint8 index)
{
    QByteArray tempData;
    int checkSumLength = 2;
    quint64 datalen = data.size();
    if (datalen < sizeof(SIntegratedCtrlHeader) + 2)
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
        if (datalen <= (sizeof(SIntegratedCtrlHeader) + checkSumLength))
        {
            return tempData;
        }
        int byteLeft = datalen - sizeof(SIntegratedCtrlHeader) - checkSumLength;
        tempData.append(data.data() + sizeof(SIntegratedCtrlHeader), byteLeft);
    }
    break;
    case CCEPackage::EDB_CheckSum:
    {
        //校验包长度
        if (datalen < (sizeof(SIntegratedCtrlHeader) + checkSumLength))
        {
            return tempData;
        }
        tempData.append(data.cend()-checkSumLength,checkSumLength);
    }
    break;
    default:
        break;
    }
    return tempData;
}
