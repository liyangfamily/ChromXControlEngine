#ifndef CCESINGLESTATUSPACKAGE_H
#define CCESINGLESTATUSPACKAGE_H

#include <CCE_CommunicatEngine/CCEPackage>

class CCE_COMMUNICATENGINE_EXPORT CCEAbstractSingleStatusPackage : public CCEPackage
{
    friend class CCEPackageManager;
    friend class CCEPackageDispatcher;

public:
    enum ECommand
    {
        EC_Read_TDCurTemperature = 0x0000,  //TD 当前温度读数值 （ 0.1℃）

        EC_Read_TICurTemperature = 0x0002, //TI 当前温度读数值（0-65535）

        EC_Read_COLUMNTemperature = 0x0004, //COLUMN 当前温度转换值  	(0-65535)

        EC_Read_MicroPIDValue = 0x0006, //PID /HD-PID    ADC 数值

        EC_Read_EPCPressure = 0x000A,   //EPC 压力读数

        EC_NLL = 0xFFFF,
    };

public:
    CCEAbstractSingleStatusPackage();
    CCEAbstractSingleStatusPackage(const QByteArray &data);
    virtual ~CCEAbstractSingleStatusPackage();

protected:
    EUnitAddr CmdUnitAddr() const override {
        return EUnitAddr::EUA_SingleStatus;
    };
};


/*******************************************************TD 当前温度读数值 （ 0.1℃）*************************************************************/
class CCE_COMMUNICATENGINE_EXPORT CCESingleStatusPackage_ReadTDCurTemperature : public CCEAbstractSingleStatusPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCESingleStatusPackage_ReadTDCurTemperature, CCEAbstractSingleStatusPackage)
public:
    quint16 getCurTemperature() const;
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_ReadFrame;
    }
    quint16 CmdCtrlAddr() const override{
        return quint16(ECommand::EC_Read_TDCurTemperature);
    }
    QByteArray CmdContent() const override{
     return QByteArray().fill(0,2);
    }
};

/*******************************************************TI 当前温度读数值（0-65535）*************************************************************/
class CCE_COMMUNICATENGINE_EXPORT CCESingleStatusPackage_ReadTICurTemperature : public CCEAbstractSingleStatusPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCESingleStatusPackage_ReadTICurTemperature, CCEAbstractSingleStatusPackage)
public:
    quint16 getCurTemperature() const;
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_ReadFrame;
    }
    quint16 CmdCtrlAddr() const override{
        return quint16(ECommand::EC_Read_TICurTemperature);
    }
    QByteArray CmdContent() const override{
     return QByteArray().fill(0,2);
    }
};

/*******************************************************COLUMN 当前温度转换值  	(0-65535)*************************************************************/
class CCE_COMMUNICATENGINE_EXPORT CCESingleStatusPackage_ReadCOLUMNTemperature : public CCEAbstractSingleStatusPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCESingleStatusPackage_ReadCOLUMNTemperature, CCEAbstractSingleStatusPackage)
public:
    quint16 getCurTemperature() const;
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_ReadFrame;
    }
    quint16 CmdCtrlAddr() const override{
        return quint16(ECommand::EC_Read_COLUMNTemperature);
    }
    QByteArray CmdContent() const override{
     return QByteArray().fill(0,2);
    }
};

/*******************************************************PID /HD-PID    ADC 数值*************************************************************/
class CCE_COMMUNICATENGINE_EXPORT CCESingleStatusPackage_ReadMicroPIDValue : public CCEAbstractSingleStatusPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCESingleStatusPackage_ReadMicroPIDValue, CCEAbstractSingleStatusPackage)
public:
    quint32 getValue() const;
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_ReadFrame;
    }
    quint16 CmdCtrlAddr() const override{
        return quint16(ECommand::EC_Read_MicroPIDValue);
    }
    QByteArray CmdContent() const override{
     return QByteArray().fill(0,2);
    }
};

/*******************************************************EPC 压力读数*************************************************************/
class CCE_COMMUNICATENGINE_EXPORT CCESingleStatusPackage_ReadEPCPressure : public CCEAbstractSingleStatusPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCESingleStatusPackage_ReadEPCPressure, CCEAbstractSingleStatusPackage)
public:
    quint16 getValue() const;
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_ReadFrame;
    }
    quint16 CmdCtrlAddr() const override{
        return quint16(ECommand::EC_Read_EPCPressure);
    }
    QByteArray CmdContent() const override{
     return QByteArray().fill(0,2);
    }
};

/*******************************************************读取单控状态所有信息*************************************************************/
class CCE_COMMUNICATENGINE_EXPORT CCESingleStatusPackage_ReadAllInfo : public CCEAbstractSingleStatusPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCESingleStatusPackage_ReadAllInfo, CCEAbstractSingleStatusPackage)
public:
    SSingleStatus getInfo() const;
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_ReadFrame;
    }
    quint16 CmdCtrlAddr() const override{
        return quint16(ECommand::EC_Read_TDCurTemperature);
    }
    QByteArray CmdContent() const override{
     return QByteArray().fill(0,sizeof(SSingleStatus));
    }
};

/*******************************************************读取单控状态所有信息*************************************************************/
class CCE_COMMUNICATENGINE_EXPORT CCESingleStatusPackage_ReportAllInfo : public CCEAbstractSingleStatusPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCESingleStatusPackage_ReportAllInfo, CCEAbstractSingleStatusPackage)
public:
    CCESingleStatusPackage_ReportAllInfo(const quint8& ret);
    SSingleStatus getInfo() const;
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_ReportFrame;
    }
    quint16 CmdCtrlAddr() const override{
        return quint16(ECommand::EC_Read_TDCurTemperature);
    }
    QByteArray CmdContent() const override{
     return QByteArray((char*)&m_retValue,sizeof(quint8));
    }
private:
    quint8 m_retValue = 0;
};
#endif // CCESINGLESTATUSPACKAGE_H
