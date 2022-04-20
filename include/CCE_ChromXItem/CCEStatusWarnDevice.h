#ifndef CCESTATUSWARNDEVICE_H
#define CCESTATUSWARNDEVICE_H

#include <CCE_ChromXItem/CCEChromXItemGlobal>
#include <CCE_ChromXItem/CCEAbstractModule.h>

class CCEStatusWarnDevicePrivate;
class CCE_CHROMXITEM_EXPORT CCEStatusWarnDevice : public CCEAbstractModule
{
    Q_OBJECT
public:
    explicit CCEStatusWarnDevice(QObject *parent = nullptr);
    ~CCEStatusWarnDevice();
protected:
    virtual void registerCallBack() override;
};

#endif // CCESTATUSWARNDEVICE_H
