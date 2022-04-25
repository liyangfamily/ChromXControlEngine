#ifndef CCELEDPANELUNITPACKAGE_H
#define CCELEDPANELUNITPACKAGE_H

#include <CCE_CommunicatEngine/CCEPackage>

class CCE_COMMUNICATENGINE_EXPORT CCEAbstractLEDPanelUnitPackage : public CCEPackage
{
    friend class CCEPackageManager;
    friend class CCEPackageDispatcher;
public:
    enum ECommand
    {
        //设备相关
        EC_Read_HardwareVersion = 0x0001,   //LED板硬件版本号
        EC_Write_HardwareVersion = EC_Read_HardwareVersion,

        EC_Read_CarrierGasPressure = 0x0002,        //LED面板 压力传感器 载气压力1值
        EC_Read_SamplingPumpPressure = 0x0004,      //LED面板 压力传感器 采样泵压力2值
        EC_Read_AuxGasPressure = 0x0006,            //LED面板 压力传感器 辅助气压力3值

        EC_Read_Temperature1Pressure = 0x0008,      //LED面板 压力传感器 温度1值
        EC_Read_Temperature2Pressure = 0x000A,      //LED面板 压力传感器 温度2值
        EC_Read_Temperature3Pressure = 0x000C,      //LED面板 压力传感器 温度3值

        EC_Read_TestProgeressBar = 0x0010,         //LED面板 检测进度条： 0-50 ，最大进度为50
        EC_Write_TestProgeressBar = EC_Read_TestProgeressBar,

        EC_Read_TestLight1 = 0x0011,               //LED面板 指示灯1： 0为关，1为开
        EC_Write_TestLight1 = EC_Read_TestLight1,
        EC_Read_TestLight2 = 0x0012,               //LED面板 指示灯2： 0为关，1为开
        EC_Write_TestLight2 = EC_Read_TestLight2,
        EC_Read_TestLight3 = 0x0013,               //LED面板 指示灯3： 0为关，1为开
        EC_Write_TestLight3 = EC_Read_TestLight3,
        EC_Read_TestLight4 = 0x0014,               //LED面板 指示灯4： 0为关，1为开
        EC_Write_TestLight4 = EC_Read_TestLight4,
        EC_Read_TestLight5 = 0x0015,               //LED面板 指示灯5： 0为关，1为开
        EC_Write_TestLight5 = EC_Read_TestLight5,

        EC_Read_EnvironmentTemperature = 0x0020,   //LED 面板 HDC1080环境温度值
        EC_Read_EnvironmentHumidity = 0x0022,      //LED 面板 HDC1080环境湿度值
        EC_Read_AmbientAtmosphericPressure = 0x0024,//LED 面板 BMP388环境大气压力值

        EC_NULL = 0xFFFF,
    };

public:
    CCEAbstractLEDPanelUnitPackage();
    CCEAbstractLEDPanelUnitPackage(const QByteArray& data);
    virtual ~CCEAbstractLEDPanelUnitPackage();

protected:
    /*********************build时需要获取**************************/
    //主控协议，总定义单元地址
    EUnitAddr CmdUnitAddr() const override {
        return EUnitAddr::EUA_LEDPanelUnit;
    };
};

/*******************************************************LED板硬件版本号*************************************************************/
class CCE_COMMUNICATENGINE_EXPORT CCELEDPanelUnitPackage_ReadHardwareVersion : public CCEAbstractLEDPanelUnitPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCELEDPanelUnitPackage_ReadHardwareVersion, CCEAbstractLEDPanelUnitPackage)
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

class CCE_COMMUNICATENGINE_EXPORT CCELEDPanelUnitPackage_WriteHardwareVersion : public CCEAbstractLEDPanelUnitPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCELEDPanelUnitPackage_WriteHardwareVersion, CCEAbstractLEDPanelUnitPackage)
public:
    CCELEDPanelUnitPackage_WriteHardwareVersion(quint8 ver);
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

/*******************************************************LED板压力传感器压力值*************************************************************/
class CCE_COMMUNICATENGINE_EXPORT CCELEDPanelUnitPackage_ReadAllPressureSensor : public CCEAbstractLEDPanelUnitPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCELEDPanelUnitPackage_ReadAllPressureSensor, CCEAbstractLEDPanelUnitPackage)
public:
    quint16 getCarrierGasPressure() const;
    quint16 getSamplingPumpPressure() const;
    quint16 getAuxGasPressure() const;
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_ReadFrame;
    }
    quint16 CmdCtrlAddr() const override{
        return quint16(ECommand::EC_Read_CarrierGasPressure);
    }
    QByteArray CmdContent() const override{
     return QByteArray().fill(0,sizeof(SPressureSensor));
    }
};

/*******************************************************LED板指示灯*************************************************************/
class CCE_COMMUNICATENGINE_EXPORT CCELEDPanelUnitPackage_ReadAllLight : public CCEAbstractLEDPanelUnitPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCELEDPanelUnitPackage_ReadAllLight, CCEAbstractLEDPanelUnitPackage)
public:
    SLEDPanelLight getValue() const;
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_ReadFrame;
    }
    quint16 CmdCtrlAddr() const override{
        return quint16(ECommand::EC_Read_TestProgeressBar);
    }
    QByteArray CmdContent() const override{
     return QByteArray().fill(0,sizeof(SLEDPanelLight));
    }
};

class CCE_COMMUNICATENGINE_EXPORT CCELEDPanelUnitPackage_WriteAllLight : public CCEAbstractLEDPanelUnitPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCELEDPanelUnitPackage_WriteAllLight, CCEAbstractLEDPanelUnitPackage)
public:
    CCELEDPanelUnitPackage_WriteAllLight(SLEDPanelLight light);
    quint8 getOperationResult() const{
        DO_GETOPERATIONRESULT();
    }
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_WriteFrame;
    }
    quint16 CmdCtrlAddr() const override{
        return quint16(ECommand::EC_Write_TestProgeressBar);
    }
    QByteArray CmdContent() const override{
     return QByteArray((char *)&m_light, sizeof(SLEDPanelLight));
    }
private:
    SLEDPanelLight m_light;
};

/*******************************************************LED环境传感器*************************************************************/
class CCE_COMMUNICATENGINE_EXPORT CCELEDPanelUnitPackage_ReadAllEvnSensor : public CCEAbstractLEDPanelUnitPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCELEDPanelUnitPackage_ReadAllEvnSensor, CCEAbstractLEDPanelUnitPackage)
public:
    quint16 getEnvTemperature() const;
    quint16 getEnvHumidity() const;
    quint16 getEnvPressure() const;
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_ReadFrame;
    }
    quint16 CmdCtrlAddr() const override{
        return quint16(ECommand::EC_Read_EnvironmentTemperature);
    }
    QByteArray CmdContent() const override{
     return QByteArray().fill(0,sizeof(SEnvSensor));
    }
};
#endif // CCELEDPANELUNITPACKAGE_H
