#ifndef CCETESTPARAMSETDEVICE_H
#define CCETESTPARAMSETDEVICE_H

#include <CCE_ChromXItem/CCEChromXItemGlobal>
#include <CCE_ChromXItem/CCEAbstractModule.h>

class CCETestParamSetDevicePrivate;
class CCE_CHROMXITEM_EXPORT CCETestParamSetDevice : public CCEAbstractModule
{
    Q_OBJECT
public:
    explicit CCETestParamSetDevice(QObject *parent = nullptr);
    ~CCETestParamSetDevice();
protected:
    virtual void registerCallBack() override;
};

#endif // CCETESTPARAMSETDEVICE_H
