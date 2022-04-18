#include "CCE_ChromXItem/CCEAbstractModule.h"
#include "CCEAbstractModule_p.h"

CCEAbstractModule::CCEAbstractModule(QObject *parent):
    QObject{parent},d_ptr(new CCEAbstractModulePrivate)
{
    d_ptr->q_ptr = this;
    gDispatcher->registerTransitObject(this);
}

CCEAbstractModule::CCEAbstractModule(CCEAbstractModulePrivate &dd, QObject *parent):
    QObject{parent},d_ptr(&dd)
{
    d_ptr->q_ptr = this;
    gDispatcher->registerTransitObject(this);
}

CCEAbstractModule::~CCEAbstractModule()
{

}

bool CCEAbstractModule::setDetectInfo(SDetectItemInfo *detectInfo)
{
    Q_ASSERT(detectInfo);
    d_ptr->m_deviceDetectInfo = detectInfo;
    return true;
}

bool CCEAbstractModule::event(QEvent *e)
{
    if (e->type() == CCEPackageEvent::s_transitPackage_eventType)
    {
        CCEPackageEvent *tempE = static_cast<CCEPackageEvent*>(e);
        d_ptr->m_packageMgr.handle(CCEPackage(tempE->package().data()));
    }
    return QObject::event(e);
}

bool CCEAbstractModule::init(SDetectItemInfo *detectInfo)
{
    if(!detectInfo){
        qDebug()<<"Abstract Module DetectInfo is nullptr...";
        Q_ASSERT(detectInfo);
        return false;
    }
    setDetectInfo(detectInfo);
    registerCallBack();
    return true;
}
