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
    typedef QMap<quint8, std::function<quint16(const QByteArray&)>> CbMap;
    typedef QMap<quint16, CbMap> CmdMap;
    typedef QMap<quint8, CmdMap> UnitMap;
    CCEPackageManager();
    virtual ~CCEPackageManager();

    template <class T>
    bool registerPackage(const T &package, std::function<quint16(const QByteArray&)>cb)
    {
        quint8 unitAddr = package.CmdUnitAddr();
        quint16 cmdNum = package.CmdCtrlAddr();
        quint8 frameType = package.CmdFrameType();
        //查找单元控制Map
        UnitMap::iterator iUnitMap = m_maps.find(unitAddr);
        if (iUnitMap != m_maps.end()) {
            //查找单元控制Map中的控制地址Map
            CmdMap::iterator iCmdNumber = iUnitMap.value().find(cmdNum);
            if (iCmdNumber != iUnitMap.value().end()) {
                //查找控制地址Map中的帧类型CbMap
                CbMap::iterator iCbmap = iCmdNumber.value().find(frameType);
                if (iCbmap != iCmdNumber.value().end()) {
                    qDebug() << "CCEPackageManager" <<
                                QString("registerPackage failed cmd name : %1   cmd number : %2 is existed").arg(unitAddr).arg(QString::number(cmdNum, 16));
                    return false;
                }
            }
        }

        m_maps[unitAddr][cmdNum][frameType] = cb;
        return true;
    }

    template <class T>
    void unregisterPackage(const T &package){
        quint8 unitAddr = package.CmdUnitAddr();
        quint16 cmdNum = package.CmdCtrlAddr();
        quint8 frameType = package.CmdFrameType();

        UnitMap::iterator iUnitMap = m_maps.find(unitAddr);
        if (iUnitMap != m_maps.end()) {
            CmdMap::iterator iCmdNumber = iUnitMap.value().find(cmdNum);
            if (iCmdNumber != iUnitMap.value().end()) {
                CbMap::iterator iCbmap = iCmdNumber.value().find(frameType);
                if (iCbmap != iCmdNumber.value().end()) {
                    //delete iCbmap.value();
                    iCmdNumber.value().erase(iCbmap);
                }
            }
        }
    }
    void unregisterAll();

    quint16 handle(const CCEPackage &package);
private:
    UnitMap m_maps;
};
#endif
