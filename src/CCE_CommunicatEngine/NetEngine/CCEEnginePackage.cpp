#include "CCE_CommunicatEngine/CCEEnginePackage.h"
#include "CCEEnginePackage_p.h"

CCEEnginePackage::CCEEnginePackage()
{
    //qDebug() << ("1SPackage()");
}

CCEEnginePackage::CCEEnginePackage(QObject *socketObj, ECommunicatType packType, EPackageFromType fromType)
{
    //qDebug() << ("2SPackage()");
    m_packType = packType;
    m_fromType = fromType;
    m_socketObj = socketObj;
}

CCEEnginePackage::CCEEnginePackage(const CCEEnginePackage&other)
{
    *this = other;
    //qDebug() << ("3SPackage()");
}

CCEEnginePackage::~CCEEnginePackage()
{
    //qDebug() << ("~SPackage()");
}

ECommunicatType CCEEnginePackage::type() const
{
    return m_packType;
}

void CCEEnginePackage::setType(ECommunicatType value)
{
    m_packType = value;
}

EPackageFromType CCEEnginePackage::fromType() const
{
    return m_fromType;
}

void CCEEnginePackage::setFromType(EPackageFromType value)
{
    m_fromType = value;
}

QObject* CCEEnginePackage::socketObj() const
{
    return m_socketObj;
}

void CCEEnginePackage::setSocketObj(QObject * value)
{
    m_socketObj = value;
}

QUuid CCEEnginePackage::exclusiveKey() const
{
    return m_exclusiveKey;
}

void CCEEnginePackage::setExClusiveKey(QUuid uuid)
{
    m_exclusiveKey = uuid;
}

QByteArray CCEEnginePackage::data() const
{
    return m_dataArray;
}

void CCEEnginePackage::setData(const QByteArray &value)
{
    m_dataArray = value;
}

QString CCEEnginePackage::hostAddress() const
{
    return m_hostAddress;
}

void CCEEnginePackage::setHostAddres(const QString &value)
{
    m_hostAddress = value;
}

quint16 CCEEnginePackage::hostPort() const
{
    return m_hostPort;
}

void CCEEnginePackage::setHostPort(const quint16 &value)
{
    m_hostPort = value;
}

void CCEEnginePackage::setNetInfo(const QString &addr, const quint16 &port)
{
    setHostAddres(addr);
    setHostPort(port);
}

void CCEEnginePackage::setComName(QString comName)
{
    m_comName = comName;
}

QString CCEEnginePackage::comName() const
{
    return m_comName;
}

QString CCEEnginePackage::hostName() const
{
    QString hostName;
    //if (m_fromType == EPackageFromType::EPFT_Receive)
    {
        switch (m_packType)
        {
        case ECT_NULL:
            break;
        case ECT_UDP:
        case ECT_TCP:
            hostName = genHostName(m_hostAddress, m_hostPort);
            break;
        case ECT_COM:
            hostName = genHostName(m_comName);
            break;
        default:
            break;
        }
    }
    //else
    {
        //qDebug() << "Send Package Can't Get Hostname.";
    }
    return hostName;
}

bool CCEEnginePackage::isEmpty() const
{
    return m_dataArray.isEmpty();
}

QString CCEEnginePackage::genHostName(const QString & addr, const quint16 &port)
{
    return QString(addr + ":" + QString::number(port));
}

QString CCEEnginePackage::genHostName(QString comName)
{
    return comName;
}
#include <QDebug>
bool CCEEnginePackage::initByDetectInfo(const SDetectItemInfo* info)
{
    if(!info){
        qDebug()<<"EnginePackage Init fail...DetectInfo is nullptr.";
        Q_ASSERT(info);
        return false;
    }
    if(!info->socketObj){
        qDebug()<<"EnginePackage Init fail...socketObj is nullptr.";
        Q_ASSERT(info->socketObj);
        return false;
    }
    this->setSocketObj(info->socketObj);
    this->setType(ECommunicatType::ECT_COM);
    this->setFromType(EPackageFromType::EPFT_Send);
    if (info->communType == ECommunicatType::ECT_TCP || info->communType == ECommunicatType::ECT_UDP)
    {
        this->setNetInfo(info->netInfo.ipAddr, info->netInfo.port);
    }
    else if(info->communType==ECommunicatType::ECT_COM)
    {
        this->setComName(info->comInfo.comName);
    }
    return true;
}

//QVariant SPackage::exData(int role) const
//{
//	for (int i = 0; i < values.count(); ++i)
//		if (values.at(i).role == role)
//			return values.at(i).value;
//	return QVariant();
//}
//
//void SPackage::setExData(int role, const QVariant & value)
//{
//	bool found = false;
//	for (int i = 0; i < values.count(); ++i) {
//		if (values.at(i).role == role) {
//			if (values.at(i).value == value)
//				return;
//			values[i].value = value;
//			found = true;
//			break;
//		}
//	}
//	if (!found)
//		values.append(SPackageData(role, value));
//}

CCEEnginePackage & CCEEnginePackage::operator=(const CCEEnginePackage & other)
{
    m_packType = other.m_packType;
    m_fromType = other.m_fromType;
    m_socketObj = other.m_socketObj;
    m_dataArray = other.m_dataArray;

    m_hostAddress = other.m_hostAddress;
    m_hostPort = other.m_hostPort;
    m_comName = other.m_comName;

    m_exclusiveKey = other.m_exclusiveKey;
    //values = other.values;

    return *this;
}
