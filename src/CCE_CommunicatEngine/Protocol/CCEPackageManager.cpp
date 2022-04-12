﻿/*********************************************************************************************************
** This file is part of the CCE_CommunicatEngine module of the CCE Toolkit.
*********************************************************************************************************/

/*!
\class CCEPackageManager

\inmodule CCE_CommunicatEngine

\brief The class is mainly responsible for the analysis function management of protocol data packets.
It will look up the registered callback parsing function based on the protocol number and command number.

\code
    CCEPackageManager manager;
    manager.registerPackage(CCEPackageInteCtrl_DetectInfo(), std::bind(&CCEDetectServer::onParsingInteCtrlDetectInfo, this, std::placeholders::_1));
\endcode

\note:
when UI or other services need to parse specific data content, they can be used in conjunction with class CCEPackageEvent.
*/

#include "CCE_CommunicatEngine/CCEPackageManager.h"

CCEPackageManager::CCEPackageManager()
{
}


CCEPackageManager::~CCEPackageManager()
{
    unregisterAll();
}

void CCEPackageManager::unregisterPackage(CCEPackage package)
{
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

void CCEPackageManager::unregisterAll()
{
    UnitMap::iterator iMaps = m_maps.begin();
    while (iMaps != m_maps.end()) {
        CmdMap::iterator iCmdNumber = iMaps.value().begin();
        while (iCmdNumber != iMaps.value().end()) {
            //delete iCmdNumber.value();
            iMaps.value().erase(iCmdNumber++);
        }
        m_maps.erase(iMaps++);
    }
}

quint16 CCEPackageManager::handle(const CCEPackage & package)
{
    quint8 unitAddr = package.getUnitAddr();
    quint16 cmdNum = package.getCtrlAddr();

    UnitMap::iterator iMaps = m_maps.find(unitAddr);
    if (iMaps != m_maps.end()) {
        CmdMap::iterator iCmdNumber = iMaps.value().find(cmdNum);
        if (iCmdNumber != iMaps.value().end()) {
            auto cb = iCmdNumber.value();
            quint16 ret = cb(package.getDataToSend());
            //iCmdNumber.value()->onReceive(package);
            //qDebug() << "CCEPackageManager" << QString("handle cmd number : %1 .").arg(QString::number(cmdNum, 16));
            return ret;
        }
        else {
            //qDebug() << "CCEPackageManager" << QString("unknown cmd number : %1 ").arg(QString::number(cmdNum, 16));
            return 0;
        }
    }
    else {
        //qDebug() << "CCEPackageManager" << QString("unknown cmd name : %1 ").arg(unitAddr);
        return 0;
    }
    return 0;
}
