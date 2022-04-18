#ifndef CCEABSTRACTMODULE_H
#define CCEABSTRACTMODULE_H

#include <CCE_ChromXItem/CCEChromXItemGlobal>
#include <CCE_CommunicatEngine/CCECommunicatEngineDef.h>
#include <QObject>


class CCEAbstractModulePrivate;
class CCE_CHROMXITEM_EXPORT CCEAbstractModule  : public QObject
{
    Q_OBJECT
public:
    explicit CCEAbstractModule(QObject *parent = nullptr);
    CCEAbstractModule(CCEAbstractModulePrivate& dd, QObject* parent = 0); // 允许子类通过它们自己的私有结构体来初始化
    virtual ~CCEAbstractModule();

    bool init(SDetectItemInfo *detectInfo);
    bool setDetectInfo(SDetectItemInfo *detectInfo);
protected:
    bool event(QEvent* e) override;
    virtual void registerCallBack() = 0;
protected:
    QScopedPointer<CCEAbstractModulePrivate> d_ptr;
};

#endif // CCEABSTRACTMODULE_H
