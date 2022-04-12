#include "CCE_CommunicatEngine/CCEMainCtrlPackage"

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
