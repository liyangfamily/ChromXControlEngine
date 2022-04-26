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
    DO_GETCHARRESULT(getContent());
}

quint8 CCEMainCtrlPackage_ReadARMSoftwareVersion::getVersion() const
{
    DO_GETCHARRESULT(getContent());
}

CCEMainCtrlPackage_WriteARMSoftwareVersion::CCEMainCtrlPackage_WriteARMSoftwareVersion(quint8 ver):
    m_version(ver)
{

}

quint8 CCEMainCtrlPackage_ReadStartSelfTest::getStatus() const
{
    DO_GETCHARRESULT(getContent());
}

CCEMainCtrlPackage_WriteStartSelfTest::CCEMainCtrlPackage_WriteStartSelfTest(quint8 status):
    m_status(status)
{

}
