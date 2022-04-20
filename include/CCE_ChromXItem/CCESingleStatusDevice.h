#ifndef CCESINGLESTATUSDEVICE_H
#define CCESINGLESTATUSDEVICE_H

#include <CCE_ChromXItem/CCEChromXItemGlobal>
#include <CCE_ChromXItem/CCEAbstractModule.h>

class CCESingleStatusDevicePrivate;
class CCE_CHROMXITEM_EXPORT CCESingleStatusDevice : public CCEAbstractModule
{
    Q_OBJECT
public:
    explicit CCESingleStatusDevice(QObject *parent = nullptr);
    ~CCESingleStatusDevice();
protected:
    virtual void registerCallBack() override;
};

#endif // CCESINGLESTATUSDEVICE_H
