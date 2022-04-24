#ifndef CCELEDPANELUNITDEVICE_H
#define CCELEDPANELUNITDEVICE_H

#include <CCE_ChromXItem/CCEChromXItemGlobal>
#include <CCE_ChromXItem/CCEAbstractModule.h>

class CCELEDPanelUnitDevicePrivate;
class CCE_CHROMXITEM_EXPORT CCELEDPanelUnitDevice : public CCEAbstractModule
{
    Q_DECLARE_PRIVATE(CCELEDPanelUnitDevice)
    Q_OBJECT
public:
    explicit CCELEDPanelUnitDevice(QObject *parent = nullptr);
    ~CCELEDPanelUnitDevice();

    quint16 writeHardwareVersion(quint8 value, bool sync, int msec);
    quint16 readHardwareVersion(bool sync, int msec);
    quint8  getHardwareVersion();
protected:
    virtual void registerCallBack() override;
    quint16 onParseWriteHardwareVersion(const QByteArray& data);
    quint16 onParseReadHardwareVersion(const QByteArray& data);
};

#endif // CCELEDPANELUNITDEVICE_H
