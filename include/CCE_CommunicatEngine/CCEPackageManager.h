/*********************************************************************************************************
** This file is part of the CCE_CommunicatEngine module of the CCE Toolkit.
*********************************************************************************************************/
#ifndef CHROMX_H_CCEPACKAGEMANAGER
#define CHROMX_H_CCEPACKAGEMANAGER
#pragma once

#include <CCE_CommunicatEngine/CCEMainCtrlPackage>

#include <QMap>

class CCE_COMMUNICATENGINE_EXPORT CCEPackageManager
{
public:
    typedef QMap<quint16, std::function<quint16(const QByteArray&)>> CmdMap;
    typedef QMap<quint8, CmdMap> UnitMap;
    CCEPackageManager();
    virtual ~CCEPackageManager();

    template <class T>
    bool registerPackage(const T &package, std::function<quint16(const QByteArray&)>cb)
    {
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

        /*T *p_t = new T();
        qDebug() << "CCEPackageManager" << QString("registerPackage cmd name : %1   cmd number : %2.").arg(unitAddr).arg(QString::number(cmdNum, 16));
        p_t->setPackageCallBack(cb);*/

        m_maps[unitAddr][cmdNum] = cb;
        return true;
    }

    template <class T>
    void unregisterPackage(const T &package){
        quint8 unitAddr = package.CmdUnitAddr();
        quint16 cmdNum = package.CmdCtrlAddr();
        UnitMap::iterator iUnitMap = m_maps.find(unitAddr);
        if (iUnitMap != m_maps.end()) {
            CmdMap::iterator iCmdNumber = iUnitMap.value().find(cmdNum);
            if (iCmdNumber != iUnitMap.value().end()) {
                //delete iCmdNumber.value();
                iUnitMap.value().erase(iCmdNumber);
            }
        }
    }
    void unregisterAll();

    quint16 handle(const CCEPackage &package);
private:
    UnitMap m_maps;
};
#endif
