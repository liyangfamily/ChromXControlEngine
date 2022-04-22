#include "CCE_CommunicatEngine/CCEMainCtrlPackage.h"

CCEAbstractMainCtrlPackage::CCEAbstractMainCtrlPackage()
{
}

CCEAbstractMainCtrlPackage::CCEAbstractMainCtrlPackage(const QByteArray &data):
    CCEPackage(data)
{

}

CCEAbstractMainCtrlPackage::~CCEAbstractMainCtrlPackage()
{

}

CCEMainCtrlPackage_WriteHardwareVersion::CCEMainCtrlPackage_WriteHardwareVersion(quint8 ver):
    m_version(ver)
{

}

quint8 CCEMainCtrlPackage_ReadHardwareVersion::getVersion() const
{
    QByteArray buffer = getContent();
    if (buffer.size() < 1) {
        return 0;
    }
    return buffer.front();
}

quint8 CCEMainCtrlPackage_ReadARMSoftwareVersion::getVersion() const
{
    QByteArray buffer = getContent();
    if (buffer.size() < 1) {
        return 0;
    }
    return buffer.front();
}

CCEMainCtrlPackage_WriteARMSoftwareVersion::CCEMainCtrlPackage_WriteARMSoftwareVersion(quint8 ver):
    m_version(ver)
{

}

quint8 CCEMainCtrlPackage_ReadStartSelfTest::getStatus() const
{
    QByteArray buffer = getContent();
    if (buffer.size() < 1) {
        return 0;
    }
    return buffer.front();
}

CCEMainCtrlPackage_WriteStartSelfTest::CCEMainCtrlPackage_WriteStartSelfTest(quint8 status):
    m_status(status)
{

}
