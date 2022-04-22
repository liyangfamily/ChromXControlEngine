/*********************************************************************************************************
** This file is part of the CCE_CommunicatEngine module of the CCE Toolkit.
*********************************************************************************************************/

/*!
\class CCEPackageDispatcher

\inmodule CCE_CommunicatEngine

\brief The CCEPackageDispatcher class responsible for distributing the data packets parsed by the communication library to all registered objects.

\code
    qDispatcher->registerTransitObject(this);
    or
    CCEPackageInteCtrl_DetectInfo pack;
    qDispatcher->registerDispatcherPackage(pack,this);
\endcode

\note:
CCEPackageDispatcher use QCoreApplication::postEvent pose CCEPackageEvent, packge data in a event.
CCEPackageDispatcher::dispatcherPackage() this function will determine the protocol number and CMD number in the package to find corresponding registered objcets.
CCEPackageDispatcher::transitPackage this function will directly forwards the package data to the corresponding objects.
*/

#include "CCE_CommunicatEngine/CCEPackageDispatcher.h"
#include "CCE_CommunicatEngine/CCECluster.h"

#include <QCoreApplication>

CCEPackageDispatcher::CCEPackageDispatcher(QObject *parent)
    : QObject(parent)
{
    connect(gCluster, &CCECluster::sig_ParsingInteCtrlDataFrame, this, &CCEPackageDispatcher::slot_ParsingInteCtrlDataFrame);
}

CCEPackageDispatcher::~CCEPackageDispatcher()
{
}

CCEPackageDispatcher * CCEPackageDispatcher::instance()
{
    static CCEPackageDispatcher m_global_dispatcher;
    return &m_global_dispatcher;
}

void CCEPackageDispatcher::unregisterAllDispatcherPackage()
{
    QMutexLocker locker(&m_mutex_protect);
    UnitMap::iterator iMaps = m_maps.begin();
    while (iMaps != m_maps.end()) {
        CmdMap::iterator iCmdNumber = iMaps.value().begin();
        while (iCmdNumber != iMaps.value().end()) {
            iCmdNumber->clear();
            iMaps.value().erase(iCmdNumber++);
        }
        m_maps.erase(iMaps++);
    }
}

bool CCEPackageDispatcher::registerTransitObject(QObject* transitObj)
{
    QMutexLocker locker(&m_mutex_protect);
    if (m_transitObjList.contains(transitObj))
    {
        return false;
    }
    else
    {
        m_transitObjList.append(transitObj);
        return true;
    }
}

void CCEPackageDispatcher::unregisterTransitObject(QObject* transitObj)
{
    QMutexLocker locker(&m_mutex_protect);
    if (m_transitObjList.contains(transitObj))
    {
        m_transitObjList.removeOne(transitObj);
    }
}

void CCEPackageDispatcher::unregisterAllTransitObject()
{
    QMutexLocker locker(&m_mutex_protect);
    m_transitObjList.clear();
}

bool CCEPackageDispatcher::dispatcherPackage(const CCEEnginePackage &package)
{
    CCEPackage tempPackage(package.data());

    quint8 unitAddr = tempPackage.getUnitAddr();
    quint16 cmdNum = tempPackage.getCtrlAddr();
    quint8 frameType = tempPackage.getFrameType();

    UnitMap::iterator iMaps = m_maps.find(unitAddr);
    if (iMaps != m_maps.end()) {
        CmdMap::iterator iCmdNumber = iMaps.value().find(cmdNum);
        if (iCmdNumber != iMaps.value().end()) {
            CbMap::iterator iCbmap = iCmdNumber.value().find(frameType);
            if (iCbmap != iCmdNumber.value().end()) {
                QList<QObject*>& objList = iCbmap.value();
                foreach(QObject* item, objList)
                {
                    CCEPackageEvent *event = new CCEPackageEvent(CCEPackageEvent::s_disPatcherPackage_eventType, unitAddr, cmdNum);
                    event->setPackage(package);
                    QCoreApplication::postEvent(item, event);
                }
                //qDebug() << "CCEPackageDispatcher" << QString("handle cmd number : %1 .").arg(QString::number(cmdNum, 16));
                return true;
            }
        }
        else {
            //qDebug() << "CCEPackageDispatcher" << QString("unknown cmd number : %1 ").arg(QString::number(cmdNum, 16));
            return false;
        }
    }
    else {
        //qDebug() << "CCEPackageDispatcher" << QString("unknown protocol name : %1 ").arg(protocolNum);
        return false;
    }
    return false;
}

bool CCEPackageDispatcher::transitPackage(const CCEEnginePackage &package)
{
    foreach(QObject* item, m_transitObjList)
    {
        CCEPackageEvent *event = new CCEPackageEvent(CCEPackageEvent::s_transitPackage_eventType);
        event->setPackage(package);
        QCoreApplication::postEvent(item, event);
    }
    return true;
}
#include <QTime>
#include <CCE_Core/CCEUIHelper>
void CCEPackageDispatcher::slot_ParsingInteCtrlDataFrame(QObject* objSocket, CCEEnginePackage pack)
{
    if(CCEUIHelper::enableCommunicatLog()){
        QString frame;
        frame = CCEUIHelper::byteArrayToHexStr(pack.data());
        qInfo()<<QString("RX:Host:%2, Length:%3, Data:%4").arg(pack.hostName()).arg(pack.data().size()).arg(frame);
    }
    Q_UNUSED(objSocket)
    //转发包，让对应的对象去处理
    this->transitPackage(pack);
    //分发包，处理后分发给关注的object
    this->dispatcherPackage(pack);
}

