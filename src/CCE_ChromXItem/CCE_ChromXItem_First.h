/****************************************************************************
**
** This Interface file is part of the ChromXItem module of the LBusinessLib.
** 这个是LBusinessLib中AbstractChromXItem派生子类设备，该模块不对外开放
**
** 该接口文件为LED系统中First设备对象，用于管理2ndPlus设备的业务和数据
**
****************************************************************************/
#ifndef CVTE_H_CCE_ChromXItem_First
#define CVTE_H_CCE_ChromXItem_First
#pragma once

#include "CCE_ChromXItem/CCEAbstractChromXItem.h"

namespace CCE
{
    namespace ChromXItem
    {
        template<class AbstractChromXItem_t, class ConChromXItem_t>
        class ChromXItemFactory; //前置声明，告诉编译器工厂为模板

        class ChromXItem_FirstPrivate;
        class CCE_CHROMXITEM_EXPORT ChromXItem_First : public CCEAbstractChromXItem
        {
            Q_DECLARE_PRIVATE(ChromXItem_First)
        public:
            ~ChromXItem_First();
            //设备属性
            virtual QString chromXItemTag() const override;
            /*********************************************************************************************************
            **控制接口
            *********************************************************************************************************/
            quint16 writeHardwareVersion(int value, bool sync, int msec) override;
            quint16 readHardwareVersion(bool sync, int msec) override;
            quint8  getHardwareVersion() override;

        protected:
            ChromXItem_First(QObject* parent = 0); //禁用外部创建
            ChromXItem_First(ChromXItem_FirstPrivate& dd, QObject* parent = 0);; // 允许子类通过它们自己的私有结构体来初始化
            bool registerControl() override;
            bool dispatcherPackage(const CCEEnginePackage& pack) override;
            friend class ChromXItemFactory<CCEAbstractChromXItem, ChromXItem_First>; //声明为一对一的好友关系，让工厂可以访问protected构造函数

        protected:
            bool init();
            virtual void registerCallBack();
            quint16 onParseReadHardwareVersion(const QByteArray& data);
        };
    }
}
#endif
