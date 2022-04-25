﻿#ifndef CCESTATUSWARNPACKAGE_H
#define CCESTATUSWARNPACKAGE_H

#include <CCE_CommunicatEngine/CCEPackage>

class CCE_COMMUNICATENGINE_EXPORT CCEAbstractWarnStatusPackage : public CCEPackage
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
    CCEAbstractWarnStatusPackage();
    CCEAbstractWarnStatusPackage(const QByteArray &data);
    virtual ~CCEAbstractWarnStatusPackage();

protected:
    EUnitAddr CmdUnitAddr() const override {
        return EUnitAddr::EUA_StatusWarn;
    };
};


/*******************************************************是否存在异常： 0 无， 1 有*************************************************************/
class CCE_COMMUNICATENGINE_EXPORT CCEWarnStatusPackage_ReadExistAbnormal : public CCEAbstractWarnStatusPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCEWarnStatusPackage_ReadExistAbnormal, CCEAbstractWarnStatusPackage)
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
class CCE_COMMUNICATENGINE_EXPORT CCEWarnStatusPackage_ReadDeviceStatus : public CCEAbstractWarnStatusPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCEWarnStatusPackage_ReadDeviceStatus, CCEAbstractWarnStatusPackage)
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

/*******************************************************主控板自检完成标志：0 自检中，1自检完成*************************************************************/
class CCE_COMMUNICATENGINE_EXPORT CCEWarnStatusPackage_ReadDeviceSelfTestStatus : public CCEAbstractWarnStatusPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCEWarnStatusPackage_ReadDeviceSelfTestStatus, CCEAbstractWarnStatusPackage)
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
class CCE_COMMUNICATENGINE_EXPORT CCEWarnStatusPackage_ReadDeviceTestComplete : public CCEAbstractWarnStatusPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCEWarnStatusPackage_ReadDeviceTestComplete, CCEAbstractWarnStatusPackage)
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
