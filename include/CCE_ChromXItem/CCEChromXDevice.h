#ifndef CCECHROMXDEVICE_H
#define CCECHROMXDEVICE_H

#include <CCE_ChromXItem/CCEChromXItemGlobal>
#include <QObject>

#define gChromXDevice           CCEChromXDevice::getInstance()
#define gChromXDetectServer     CCEChromXDevice::getInstance().detectServer()

#define gChromXMainCtrl         CCEChromXDevice::getInstance().mainCtrlDevice()
#define gChromXLEDPanelUnit   CCEChromXDevice::getInstance().LEDPanelUnitDevice()
#define gChromXSingleCtrl       CCEChromXDevice::getInstance().singleCtrlDevice()
#define gChromXSingleStatus     CCEChromXDevice::getInstance().singleStatusDevice()
#define gChromXStatusWarn       CCEChromXDevice::getInstance().statusWarnDevice()
#define gChromXTestData         CCEChromXDevice::getInstance().testDataDevice()
#define gChromXTestParamSet     CCEChromXDevice::getInstance().testParamSetDevice()

class CCEDetectServer;

class CCEMainCtrlDevice;
class CCELEDPanelUnitDevice;
class CCESingleCtrlDevice;
class CCESingleStatusDevice;
class CCEStatusWarnDevice;
class CCETestDataDevice;
class CCETestParamSetDevice;

class CCEChromXDevicePrivate;
class CCE_CHROMXITEM_EXPORT CCEChromXDevice : public QObject
{
    Q_OBJECT
public:
    ~CCEChromXDevice();
    static CCEChromXDevice &getInstance();
    CCEDetectServer& detectServer();

    CCEMainCtrlDevice& mainCtrlDevice();
    CCELEDPanelUnitDevice& LEDPanelUnitDevice();
    CCESingleCtrlDevice& singleCtrlDevice();
    CCESingleStatusDevice& singleStatusDevice();
    CCEStatusWarnDevice& statusWarnDevice();
    CCETestDataDevice& testDataDevice();
    CCETestParamSetDevice& testParamSetDevice();
private:
    bool registerModule();
    bool releaseSubModule();
private:
    CCEChromXDevice();
    CCEChromXDevice(const CCEChromXDevice&) = delete;
    CCEChromXDevice& operator=(const CCEChromXDevice&) = delete;
    QScopedPointer<CCEChromXDevicePrivate> d_ptr;
};

#endif // CCECHROMXDEVICE_H
