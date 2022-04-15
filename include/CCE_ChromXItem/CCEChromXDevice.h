#ifndef CCECHROMXDEVICE_H
#define CCECHROMXDEVICE_H

#include <CCE_ChromXItem/CCEChromXItemGlobal>
#include <QObject>

#define gChromXDevice CCEChromXDevice::getInstance()
#define gChromXDetectServer CCEChromXDevice::getInstance().detectServer()
#define gChromXMainCtrl CCEChromXDevice::getInstance().mainCtrlDevice()
#define gChromXSingleCtrl CCEChromXDevice::getInstance().detectServer()

class CCEDetectServer;
class CCEMainCtrlDevice;

class CCEChromXDevicePrivate;
class CCE_CHROMXITEM_EXPORT CCEChromXDevice : public QObject
{
    Q_OBJECT
public:
    ~CCEChromXDevice();
    static CCEChromXDevice &getInstance();
    CCEDetectServer& detectServer();
    CCEMainCtrlDevice& mainCtrlDevice();
private:
    bool initSubModule();
    bool releaseSubModule();
private:
    CCEChromXDevice();
    CCEChromXDevice(const CCEChromXDevice&) = delete;
    CCEChromXDevice& operator=(const CCEChromXDevice&) = delete;
    QScopedPointer<CCEChromXDevicePrivate> d_ptr;
};

#endif // CCECHROMXDEVICE_H
