/*********************************************************************************************************
** This file is part of the CCE_CommunicatEngine module of the CCE Toolkit.
*********************************************************************************************************/
#ifndef CVTE_H_CCEPACKAGEDISPATCHER
#define CVTE_H_CCEPACKAGEDISPATCHER
#pragma once
#include <CCE_CommunicatEngine/CCEMainCtrlPackage>
#include <CCE_CommunicatEngine/CCEPackageEvent>

#include <QByteArray>
#include <QObject>
#include <QMap>
#include <QList>
#include <QMutex>
#include <QMutexLocker>

#define gDispatcher CCEPackageDispatcher::instance()

class CCE_COMMUNICATENGINE_EXPORT CCEPackageDispatcher : public QObject
{
    Q_OBJECT

public:
    typedef QMap<quint16, QList<QObject *>> CmdMap;
    typedef QMap<quint8, CmdMap> UnitMap;
    CCEPackageDispatcher(QObject *parent = nullptr);
    ~CCEPackageDispatcher();

    static CCEPackageDispatcher *instance();

    //register CMD
    template <class T>
    bool registerDispatcherPackage(const T &package, QObject* obj)
    {
        QMutexLocker locker(&m_mutex_protect);
        quint8 unitAddr = package.CmdUnitAddr();
        quint16 cmdNum = package.CmdCtrlAddr();
        UnitMap::iterator iUnitMap = m_maps.find(unitAddr);
        if (iUnitMap != m_maps.end()) {
            CmdMap::iterator icmdNumber = iUnitMap.value().find(cmdNum);
            if (icmdNumber != iUnitMap.value().end()) {
                qDebug() << "CCEPackageManager" <<
                            QString("registerPackage failed cmd name : %1   cmd number : %2 is existed").arg(unitAddr).arg(QString::number(cmdNum, 16));
                return false;
            }
        }

        m_maps[unitAddr][cmdNum].append(obj);
        return true;
    }

    template <class T>
    void unregisterDispatcherPackage(const T &package, QObject* obj)
    {
        QMutexLocker locker(&m_mutex_protect);
        quint8 unitAddr = package.CmdUnitAddr();
        quint16 cmdNum = package.CmdCtrlAddr();
        UnitMap::iterator iUnitMap = m_maps.find(unitAddr);
        if (iUnitMap != m_maps.end()) {
            CmdMap::iterator iCmdNumber = iUnitMap.value().find(cmdNum);
            if (iCmdNumber != iUnitMap.value().end()) {
                iCmdNumber->removeOne(obj);
            }
        }
    }
    void unregisterAllDispatcherPackage();

    //register Object
    bool registerTransitObject(QObject* transitObj);
    void unregisterTransitObject(QObject* transitObj);
    void unregisterAllTransitObject();

protected:
    bool dispatcherPackage(const CCEEnginePackage &package);
    bool transitPackage(const CCEEnginePackage &package);
protected slots:
    void slot_ParsingInteCtrlDataFrame(QObject* objSocket, CCEEnginePackage pack);
private:
    QMutex m_mutex_protect;
    //用于储存按协议号和指令号注册的通知对象
    UnitMap m_maps;
    //用于储存中转通知对象
    QList<QObject*> m_transitObjList;
};
#endif
