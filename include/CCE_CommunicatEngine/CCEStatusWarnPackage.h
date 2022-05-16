#ifndef CCESTATUSWARNPACKAGE_H
#define CCESTATUSWARNPACKAGE_H

#include <CCE_CommunicatEngine/CCEPackage>

class CCE_COMMUNICATENGINE_EXPORT CCEAbstractStatusWarnPackage : public CCEPackage
{
    friend class CCEPackageManager;
    friend class CCEPackageDispatcher;

public:
    enum ECommand
    {
        EC_Read_ExistAbnormal = 0x0000,  //是否存在异常： 0 无， 1 有

        EC_Read_DeviceStatus = 0x0001, //设备状态

        EC_Read_DeviceSelfTestStatus = 0x0002, //主控板自检完成标志：0 自检中，1自检完成

        EC_Read_DeviceTestComplete = 0x000A, //整机测试运行结束  0 无， 1 有

        EC_NLL = 0xFFFF,
    };

public:
    CCEAbstractStatusWarnPackage();
    CCEAbstractStatusWarnPackage(const QByteArray &data);
    virtual ~CCEAbstractStatusWarnPackage();

protected:
    EUnitAddr CmdUnitAddr() const override {
        return EUnitAddr::EUA_StatusWarn;
    };
};


/*******************************************************是否存在异常： 0 无， 1 有*************************************************************/
class CCE_COMMUNICATENGINE_EXPORT CCEStatusWarnPackage_ReadExistAbnormal : public CCEAbstractStatusWarnPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCEStatusWarnPackage_ReadExistAbnormal, CCEAbstractStatusWarnPackage)
public:
    quint8 getValue() const;
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_ReadFrame;
    }
    quint16 CmdCtrlAddr() const override{
        return quint16(ECommand::EC_Read_ExistAbnormal);
    }
    QByteArray CmdContent() const override{
     return QByteArray().fill(0,1);
    }
};

/*******************************************************设备状态*************************************************************/
class CCE_COMMUNICATENGINE_EXPORT CCEStatusWarnPackage_ReadDeviceStatus : public CCEAbstractStatusWarnPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCEStatusWarnPackage_ReadDeviceStatus, CCEAbstractStatusWarnPackage)
public:
    quint8 getValue() const;
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_ReadFrame;
    }
    quint16 CmdCtrlAddr() const override{
        return quint16(ECommand::EC_Read_DeviceStatus);
    }
    QByteArray CmdContent() const override{
     return QByteArray().fill(0,1);
    }
};

/*******************************************************报告设备状态*************************************************************/
class CCE_COMMUNICATENGINE_EXPORT CCEStatusWarnPackage_ReportDeviceStatus : public CCEAbstractStatusWarnPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCEStatusWarnPackage_ReportDeviceStatus, CCEAbstractStatusWarnPackage)
public:
    CCEStatusWarnPackage_ReportDeviceStatus(const quint8& ret);
    quint8 getValue() const;
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_ReportFrame;
    }
    quint16 CmdCtrlAddr() const override{
        return quint16(ECommand::EC_Read_DeviceStatus);
    }
    QByteArray CmdContent() const override{
     return QByteArray((char*)&m_retValue,sizeof(quint8));
    }
private:
    quint8 m_retValue = 0;
};

/*******************************************************主控板自检完成标志：0 自检中，1自检完成*************************************************************/
class CCE_COMMUNICATENGINE_EXPORT CCEStatusWarnPackage_ReadDeviceSelfTestStatus : public CCEAbstractStatusWarnPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCEStatusWarnPackage_ReadDeviceSelfTestStatus, CCEAbstractStatusWarnPackage)
public:
    quint8 getValue() const;
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_ReadFrame;
    }
    quint16 CmdCtrlAddr() const override{
        return quint16(ECommand::EC_Read_DeviceSelfTestStatus);
    }
    QByteArray CmdContent() const override{
     return QByteArray().fill(0,1);
    }
};

/*******************************************************整机测试运行结束  0 无， 1 有*************************************************************/
class CCE_COMMUNICATENGINE_EXPORT CCEStatusWarnPackage_ReadDeviceTestComplete : public CCEAbstractStatusWarnPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCEStatusWarnPackage_ReadDeviceTestComplete, CCEAbstractStatusWarnPackage)
public:
    quint8 getValue() const;
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_ReadFrame;
    }
    quint16 CmdCtrlAddr() const override{
        return quint16(ECommand::EC_Read_DeviceTestComplete);
    }
    QByteArray CmdContent() const override{
     return QByteArray().fill(0,1);
    }
};
#endif // CCESTATUSWARNPACKAGE_H
