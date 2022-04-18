#ifndef CCEDETECTSERVER_H
#define CCEDETECTSERVER_H

#include <CCE_ChromXItem/CCEChromXItemGlobal>
#include <CCE_CommunicatEngine/CCECommunicatEngineDef.h>
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
    SDetectItemInfo* getMainDetectInfo();
    SDetectItemInfo* getAssistDetectInfo();
signals:
    void sig_DeviceConnect();
    void sig_DeviceDisConnect();
protected slots:
    void slot_NewCOMConnectionEstablish(QObject* objSocket, QString comName,quint64 extraData);
private:
    void prepareComDevice();
private:
    QScopedPointer<CCEDetectServerPrivate> d_ptr;
};

#endif // CCEDETECTSERVER_H
