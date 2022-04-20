#ifndef CCEPRESSURESENSORDEVICE_H
#define CCEPRESSURESENSORDEVICE_H

#include <CCE_ChromXItem/CCEChromXItemGlobal>
#include <CCE_ChromXItem/CCEAbstractModule.h>

class CCEPressureSensorDevicePrivate;
class CCE_CHROMXITEM_EXPORT CCEPressureSensorDevice : public CCEAbstractModule
{
    Q_OBJECT
public:
    explicit CCEPressureSensorDevice(QObject *parent = nullptr);
    ~CCEPressureSensorDevice();
protected:
    virtual void registerCallBack() override;
};

#endif // CCEPRESSURESENSORDEVICE_H
