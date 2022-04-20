#ifndef CCESINGLECTRLDEVICE_H
#define CCESINGLECTRLDEVICE_H

#include <CCE_ChromXItem/CCEChromXItemGlobal>
#include <CCE_ChromXItem/CCEAbstractModule.h>

class CCESingleCtrlDevicePrivate;
class CCE_CHROMXITEM_EXPORT CCESingleCtrlDevice : public CCEAbstractModule
{
    Q_OBJECT
public:
    explicit CCESingleCtrlDevice(QObject *parent = nullptr);
    ~CCESingleCtrlDevice();
protected:
    virtual void registerCallBack() override;
};

#endif // CCESINGLECTRLDEVICE_H
