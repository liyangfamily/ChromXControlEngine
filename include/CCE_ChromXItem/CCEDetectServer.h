#ifndef CCEDETECTSERVER_H
#define CCEDETECTSERVER_H

#include <CCE_ChromXItem/CCEChromXItemGlobal>
#include <QObject>

class CCEDetectServerPrivate;
class CCE_CHROMXITEM_EXPORT CCEDetectServer : public QObject
{
    Q_OBJECT
public:
    explicit CCEDetectServer(QObject *parent = nullptr);
    ~CCEDetectServer();

    bool isConnect();
    void autoConnect();
    void connectMainCOM(QString comName);
    void connectAssistCOM(QString comName);
    void disConnectCOM(QString comName);
    void disConnectAllCOM();
    QObject* mainCOMSocket();
    QObject* assistCOMSocket();
signals:
    void sig_DeviceConnect();
    void sig_DeviceDisConnect();
private:
    void prepareComDevice();
    bool setCOMInfo(QObject* socket,QString comName);
private:
    QScopedPointer<CCEDetectServerPrivate> d_ptr;
};

#endif // CCEDETECTSERVER_H
