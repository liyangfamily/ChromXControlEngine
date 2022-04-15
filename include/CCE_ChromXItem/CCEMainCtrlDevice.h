#ifndef CCEMAINCTRLDEVICE_H
#define CCEMAINCTRLDEVICE_H

#include <CCE_ChromXItem/CCEChromXItemGlobal>
#include <QObject>
#include <QScopedPointer>

class CCEMainCtrlDevicePrivate;
class CCE_CHROMXITEM_EXPORT CCEMainCtrlDevice : public QObject
{
    Q_OBJECT
public:
    explicit CCEMainCtrlDevice(QObject *parent = nullptr);
    ~CCEMainCtrlDevice();
    void setSocket(QObject* socket);
    /*********************************************************************************************************
    **主控设备控制
    *********************************************************************************************************/
    quint16 writeHardwareVersion(int value, bool sync, int msec);
    quint16 readHardwareVersion(bool sync, int msec);
    quint8  getHardwareVersion();
protected:
    virtual bool event(QEvent* e) override;
    bool init();
    void registerCallBack();
    quint16 onParseReadHardwareVersion(const QByteArray& data);
private:
    QScopedPointer<CCEMainCtrlDevicePrivate> d_ptr;
};

#endif // CCEMAINCTRLDEVICE_H
