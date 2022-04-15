#include "CCE_ChromXItem_First.h"
#include "CCE_ChromXItem_First_p.h"
#include <CCE_CommunicatEngine/CCEClusterProxy>

#define CCE_TAG_SENDERCARDFirst "First"
namespace CCE
{
    namespace ChromXItem
    {

        ChromXItem_First::ChromXItem_First(QObject* parent/* = 0*/):
            CCEAbstractChromXItem(*new ChromXItem_FirstPrivate(), parent)
        {
            Q_D(ChromXItem_First);
            Q_UNUSED(d)
            d_ptr->q_ptr = this;
            init();
        }


        ChromXItem_First::ChromXItem_First(ChromXItem_FirstPrivate& dd, QObject* parent) :
            CCEAbstractChromXItem(dd, parent)
        {
            Q_D(ChromXItem_First);
            Q_UNUSED(d)
            d_ptr->q_ptr = this;
            init();
        }

        ChromXItem_First::~ChromXItem_First()
        {
        }

        QString ChromXItem_First::chromXItemTag() const
        {
            return CCE_TAG_SENDERCARDFirst;
        }

        quint16 ChromXItem_First::writeHardwareVersion(int value, bool sync, int msec)
        {
            Q_D(ChromXItem_First);
            return quint16();
        }

        quint16 ChromXItem_First::readHardwareVersion(bool sync, int msec)
        {
            Q_D(ChromXItem_First);
            CCEMainCtrlPackage_ReadHardwareVersion detectInfo;
            detectInfo.build();
            QByteArray writeData = detectInfo.getDataToSend();
            CCEEnginePackage enginePack;
            enginePack.initByDetectInfo(&d->m_detectInfo);
            enginePack.setData(writeData);

            if (sync) {
                CCEEnginePackage recEnginePack;
                if (!CCEClusterProxy::syncSend(enginePack, recEnginePack, msec)) {
                    return CCEAPI::EResult::ER_SyncSendTimeOut;
                }
                quint16 ret = d->m_packageMgr.handle(CCEPackage(recEnginePack.data()));
                return ret;
            }
            else {
                return CCEClusterProxy::asyncSend(enginePack);
            }
        }

        quint8 ChromXItem_First::getHardwareVersion()
        {
            Q_D(ChromXItem_First);
            return quint8();
        }

        bool ChromXItem_First::registerControl()
        {
            Q_D(ChromXItem_First);
            //创建控制接口

            return true;
        }

        bool ChromXItem_First::dispatcherPackage(const CCEEnginePackage& pack)
        {
            if (pack.isEmpty() || pack.hostName() != this->hostName())
            {
                return false;
            }
            Q_D(ChromXItem_First);
            CCEPackage tempPackage(pack.data());
            d->m_packageMgr.handle(tempPackage);
            CCEPackage::EUnitAddr dataSourceDevice = CCEPackage::EUnitAddr(tempPackage.getUnitAddr());
            switch (dataSourceDevice)
            {
            case CCEPackage::EUA_NULL:
                break;
            case CCEPackage::EUA_MainCtrl:
                break;
            case CCEPackage::EUA_PressureSensor:
                break;
            case CCEPackage::EUA_SingleCtrl:
                break;
            case CCEPackage::EUA_SingleStatus:
                break;
            case CCEPackage::EUA_TestParamSet:
                break;
            case CCEPackage::EUA_TestData:
                break;
            case CCEPackage::EUA_StatusWarn:
                break;
            default:
                break;
            }
            return false;
        }

        bool ChromXItem_First::init()
        {
            registerCallBack();
            return true;
        }

        void ChromXItem_First::registerCallBack()
        {
            Q_D(ChromXItem_First);
            d->m_packageMgr.registerPackage(CCEMainCtrlPackage_ReadHardwareVersion(),
                                            std::bind(&ChromXItem_First::onParseReadHardwareVersion, this, std::placeholders::_1));
        }

        quint16 ChromXItem_First::onParseReadHardwareVersion(const QByteArray &data)
        {
            qDebug()<<"Got it!"<<CCEUIHelper::byteArrayToHexStr(data);
            return CCEAPI::EResult::ER_Success;
        }

    }
}
