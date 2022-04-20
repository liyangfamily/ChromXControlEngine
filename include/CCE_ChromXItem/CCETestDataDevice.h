#ifndef CCETESTDATADEVICE_H
#define CCETESTDATADEVICE_H

#include <CCE_ChromXItem/CCEChromXItemGlobal>
#include <CCE_ChromXItem/CCEAbstractModule.h>

class CCETestDataDevicePrivate;
class CCE_CHROMXITEM_EXPORT CCETestDataDevice : public CCEAbstractModule
{
    Q_OBJECT
public:
    explicit CCETestDataDevice(QObject *parent = nullptr);
    ~CCETestDataDevice();
protected:
    virtual void registerCallBack() override;
};

#endif // CCETESTDATADEVICE_H
