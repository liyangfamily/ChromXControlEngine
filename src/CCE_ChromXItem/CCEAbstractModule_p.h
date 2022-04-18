#ifndef CCEABSTRACTMODULE_P_H
#define CCEABSTRACTMODULE_P_H

#include <CCE_CommunicatEngine/CCEPackageManager>
#include <CCE_CommunicatEngine/CCEPackageDispatcher>

class CCEAbstractModule;
class CCEAbstractModulePrivate
{
public:
    CCEAbstractModulePrivate(){}
    virtual ~CCEAbstractModulePrivate(){}
    CCEAbstractModule* q_ptr = nullptr;

    CCEPackageManager m_packageMgr;
    //共享探卡服务探卡信息
    SDetectItemInfo* m_deviceDetectInfo;
};

#endif // CCEABSTRACTMODULE_P_H
