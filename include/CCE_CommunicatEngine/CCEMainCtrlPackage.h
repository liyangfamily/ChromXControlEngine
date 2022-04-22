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
        //设备相关
        EC_Read_HardwareVersion = 0x0001,   //主控板硬件版本号
        EC_Write_HardwareVersion = EC_Read_HardwareVersion,

        EC_Read_ARMSoftwareVersion = 0x0002,    //主控板嵌入式软件版本号
        EC_Write_ARMSoftwareVersion = EC_Read_ARMSoftwareVersion,

        EC_Read_StartSelfTest = 0x0003,    //主控板开始自检：0（关闭） 1（开始自检）
        EC_Write_StartSelfTest = EC_Read_StartSelfTest,

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

/*******************************************************主控板硬件版本号*************************************************************/
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
     return QByteArray().fill(0,1);
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

/*******************************************************主控板嵌入式软件版本号*************************************************************/
class CCE_COMMUNICATENGINE_EXPORT CCEMainCtrlPackage_ReadARMSoftwareVersion : public CCEAbstractMainCtrlPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCEMainCtrlPackage_ReadARMSoftwareVersion, CCEAbstractMainCtrlPackage)
public:
    quint8 getVersion() const;
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_ReadFrame;
    }
    quint16 CmdCtrlAddr() const override{
        return quint16(ECommand::EC_Read_ARMSoftwareVersion);
    }
    QByteArray CmdContent() const override{
     return QByteArray().fill(0,1);
    }
};

class CCE_COMMUNICATENGINE_EXPORT CCEMainCtrlPackage_WriteARMSoftwareVersion : public CCEAbstractMainCtrlPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCEMainCtrlPackage_WriteARMSoftwareVersion, CCEAbstractMainCtrlPackage)
public:
    CCEMainCtrlPackage_WriteARMSoftwareVersion(quint8 ver);
    quint8 getOperationResult() const{
        DO_GETOPERATIONRESULT();
    }
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_WriteFrame;
    }
    quint16 CmdCtrlAddr() const override{
        return quint16(ECommand::EC_Write_ARMSoftwareVersion);
    }
    QByteArray CmdContent() const override{
     return QByteArray((char *)&m_version, 1);
    }
private:
    quint8 m_version = 0;
};

/*******************************************************主控板开始自检*************************************************************/
class CCE_COMMUNICATENGINE_EXPORT CCEMainCtrlPackage_ReadStartSelfTest : public CCEAbstractMainCtrlPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCEMainCtrlPackage_ReadStartSelfTest, CCEAbstractMainCtrlPackage)
public:
    quint8 getStatus() const;
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_ReadFrame;
    }
    quint16 CmdCtrlAddr() const override{
        return quint16(ECommand::EC_Read_StartSelfTest);
    }
    QByteArray CmdContent() const override{
     return QByteArray().fill(0,1);
    }
};

class CCE_COMMUNICATENGINE_EXPORT CCEMainCtrlPackage_WriteStartSelfTest : public CCEAbstractMainCtrlPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCEMainCtrlPackage_WriteStartSelfTest, CCEAbstractMainCtrlPackage)
public:
    CCEMainCtrlPackage_WriteStartSelfTest(quint8 status);
    quint8 getOperationResult() const{
        DO_GETOPERATIONRESULT();
    }
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_WriteFrame;
    }
    quint16 CmdCtrlAddr() const override{
        return quint16(ECommand::EC_Write_StartSelfTest);
    }
    QByteArray CmdContent() const override{
     return QByteArray((char *)&m_status, 1);
    }
private:
    quint8 m_status = 0;
};

#endif // CCEMAINCTRLPACKAGE_H
