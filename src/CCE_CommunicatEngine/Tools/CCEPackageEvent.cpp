/*********************************************************************************************************
** This file is part of the CCE_CommunicatEngine module of the CCE Toolkit.
*********************************************************************************************************/

/*!
\class CCEPackageEvent

\inmodule CCE_CommunicatEngine

\brief The CCE_CommunicatEngine class is a custom registration event of Qt system, used to dispatcher communication data package.

\code
    CCEPackageEvent *event = new CCEPackageEvent(CCEPackageEvent::s_disPatcherPackage_eventType);
    event->setPackage(package);
    QCoreApplication::postEvent(item, event);
\endcode

\note:

*/

#include "CCE_CommunicatEngine/CCEPackageEvent.h"

QEvent::Type CCEPackageEvent::s_disPatcherPackage_eventType = QEvent::Type(QEvent::registerEventType());
QEvent::Type CCEPackageEvent::s_transitPackage_eventType = QEvent::Type(QEvent::registerEventType());
