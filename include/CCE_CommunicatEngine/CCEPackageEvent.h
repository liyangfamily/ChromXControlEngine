/*********************************************************************************************************
** This file is part of the CCE_CommunicatEngine module of the CCE Toolkit.
*********************************************************************************************************/
#ifndef CVTE_H_CCEPACKAGEEVENT
#define CVTE_H_CCEPACKAGEEVENT
#pragma once

#include <CCE_CommunicatEngine/CCEEnginePackage>
#include <QEvent>

class CCE_COMMUNICATENGINE_EXPORT CCEPackageEvent : public QEvent
{
public:
    CCEPackageEvent(QEvent::Type type) :QEvent(type)
    {
    }

    CCEPackageEvent(QEvent::Type type, quint8 frameType, quint8 unitAddr, quint16 cmdNum) :
        QEvent(type),m_frameType(frameType), m_unitAddr(unitAddr), m_cmdNum(cmdNum)
    {
    }
    ~CCEPackageEvent()
    {
    }

    void setPackage(const CCEEnginePackage &msg)
    {
        m_package = msg;
    }

    const CCEEnginePackage & package()const
    {
        return m_package;
    }

    quint8 frameType() {
        return m_frameType;
    }

    quint8 unitAddr() {
        return m_unitAddr;
    }

    quint16 cmdNum(){
        return m_cmdNum;
    }

    //注册两个事件类型
    static QEvent::Type s_disPatcherPackage_eventType;
    static QEvent::Type s_transitPackage_eventType;

private:
    CCEEnginePackage m_package;
    quint8 m_frameType = 0;
    quint8 m_unitAddr = 0;
    quint16 m_cmdNum = 0;
};
#endif
