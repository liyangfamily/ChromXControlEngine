#ifndef CCEMAINCTRLPACKAGE_H
#define CCEMAINCTRLPACKAGE_H

#include <CCE_CommunicatEngine/CCEPackage>

class CCE_COMMUNICATENGINE_EXPORT CCEAbstractMainCtrlPackage : public CCEPackage
{
    friend class CCEPackageManager;
    friend class CCEPackageDispatcher;
public:
    enum ECommand
    {
        //发送卡相关
        EC_Read_HardwareVersion = 0x0001,   //主控板硬件版本号
        EC_Write_HardwareVersion = EC_Read_HardwareVersion,

        EC_Read_ARMSoftwareVersion = 0x0002,    //主控板嵌入式软件版本号
        EC_Write_ARMSoftwareVersion = EC_Read_ARMSoftwareVersion,

        EC_Read_CtrlMode = 0x0005,    //主控板控制模式，0：整机测试，1：单控模式
        EC_Write_CtrlMode = EC_Read_CtrlMode,

        EC_NULL = 0xFFFF,
    };

public:
    CCEAbstractMainCtrlPackage();
    CCEAbstractMainCtrlPackage(const QByteArray& data);
    virtual ~CCEAbstractMainCtrlPackage();

protected:
    /*********************build时需要获取**************************/
    //主控协议，总定义单元地址
    EUnitAddr CmdUnitAddr() const override {
        return EUnitAddr::EUA_MainCtrl;
    };
};

class CCE_COMMUNICATENGINE_EXPORT CCEMainCtrlPackage_ReadHardwareVersion : public CCEAbstractMainCtrlPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCEMainCtrlPackage_ReadHardwareVersion, CCEAbstractMainCtrlPackage)
public:
    quint8 getVersion() const;
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_ReadFrame;
    }
    quint16 CmdCtrlAddr() const override{
        return quint16(ECommand::EC_Read_HardwareVersion);
    }
    QByteArray CmdContent() const override{
     return QByteArray();
    }
};

class CCE_COMMUNICATENGINE_EXPORT CCEMainCtrlPackage_WriteHardwareVersion : public CCEAbstractMainCtrlPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCEMainCtrlPackage_WriteHardwareVersion, CCEAbstractMainCtrlPackage)
public:
    CCEMainCtrlPackage_WriteHardwareVersion(quint8 ver);
    quint8 getOperationResult() const{
        DO_GETOPERATIONRESULT();
    }
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_WriteFrame;
    }
    quint16 CmdCtrlAddr() const override{
        return quint16(ECommand::EC_Write_HardwareVersion);
    }
    QByteArray CmdContent() const override{
     return QByteArray((char *)&m_version, 1);
    }
private:
    quint8 m_version = 0;
};

class CCE_COMMUNICATENGINE_EXPORT CCEMainCtrlPackage_WriteControlPump : public CCEAbstractMainCtrlPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCEMainCtrlPackage_WriteControlPump, CCEAbstractMainCtrlPackage)
public:
    CCEMainCtrlPackage_WriteControlPump(quint8 status):m_status(status){}
    quint8 getOperationResult() const{
        DO_GETOPERATIONRESULT();
    }
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_WriteFrame;
    }
    quint16 CmdCtrlAddr() const override{
        return quint16(0x0001);
    }
    QByteArray CmdContent() const override{
     return QByteArray((char *)&m_status, 1);
    }
private:
    quint8 m_status = 0;
};
#endif // CCEMAINCTRLPACKAGE_H
