#ifndef CCELEDPANELUNITDEVICE_H
#define CCELEDPANELUNITDEVICE_H

#include <CCE_ChromXItem/CCEChromXItemGlobal>
#include <CCE_ChromXItem/CCEAbstractModule.h>

class CCELEDPanelUnitDevicePrivate;
class CCE_CHROMXITEM_EXPORT CCELEDPanelUnitDevice : public CCEAbstractModule
{
    Q_OBJECT
public:
    explicit CCELEDPanelUnitDevice(QObject *parent = nullptr);
    ~CCELEDPanelUnitDevice();

    quint16 writeStartSelfTest(quint8 value, bool sync, int msec);
    quint16 readStartSelfTest(bool sync, int msec);
    quint8  getStartSelfTest();
protected:
    virtual void registerCallBack() override;
    quint16 onParseReadHardwareVersion(const QByteArray& data);
};

#endif // CCELEDPANELUNITDEVICE_H
