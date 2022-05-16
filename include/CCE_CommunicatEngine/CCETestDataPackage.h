#ifndef CCETESTDATAPACKAGE_H
#define CCETESTDATAPACKAGE_H

#include <CCE_CommunicatEngine/CCEPackage>

class CCE_COMMUNICATENGINE_EXPORT CCEAbstractTestDataPackage : public CCEPackage
{
    friend class CCEPackageManager;
    friend class CCEPackageDispatcher;

public:
    enum ECommand
    {
        EC_Read_TDCurTemperature = 0x0000,  //TD 当前温度读数值 （ 0.1℃）

        EC_Read_TICurTemperature = 0x0002, //TI 当前温度读数值（0-65535）

        EC_Read_CurTestRunTime = 0x0004, //当前测试运行的时间 （0.01s）	(32bit)

        EC_Read_COLUMNTemperature = 0x0008, //COLUMN 当前温度转换值  	(0-65535)

        EC_Read_MicroPIDValue = 0x000A, //PID /HD-PID    ADC 数值

        EC_NLL = 0xFFFF,
    };

public:
    CCEAbstractTestDataPackage();
    CCEAbstractTestDataPackage(const QByteArray &data);
    virtual ~CCEAbstractTestDataPackage();

protected:
    EUnitAddr CmdUnitAddr() const override {
        return EUnitAddr::EUA_TestData;
    };
};


/*******************************************************TD 当前温度读数值 （ 0.1℃）*************************************************************/
class CCE_COMMUNICATENGINE_EXPORT CCETestDataPackage_ReadTDCurTemperature : public CCEAbstractTestDataPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCETestDataPackage_ReadTDCurTemperature, CCEAbstractTestDataPackage)
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
class CCE_COMMUNICATENGINE_EXPORT CCETestDataPackage_ReadTICurTemperature : public CCEAbstractTestDataPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCETestDataPackage_ReadTICurTemperature, CCEAbstractTestDataPackage)
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


/*******************************************************当前测试运行的时间 （0.01s）	(32bit)*************************************************************/
class CCE_COMMUNICATENGINE_EXPORT CCETestDataPackage_ReadCurTestRunTime : public CCEAbstractTestDataPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCETestDataPackage_ReadCurTestRunTime, CCEAbstractTestDataPackage)
public:
    quint32 getValue() const;
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_ReadFrame;
    }
    quint16 CmdCtrlAddr() const override{
        return quint16(ECommand::EC_Read_CurTestRunTime);
    }
    QByteArray CmdContent() const override{
     return QByteArray().fill(0,4);
    }
};


/*******************************************************COLUMN 当前温度转换值  	(0-65535)*************************************************************/
class CCE_COMMUNICATENGINE_EXPORT CCETestDataPackage_ReadCOLUMNTemperature : public CCEAbstractTestDataPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCETestDataPackage_ReadCOLUMNTemperature, CCEAbstractTestDataPackage)
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
class CCE_COMMUNICATENGINE_EXPORT CCETestDataPackage_ReadMicroPIDValue : public CCEAbstractTestDataPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCETestDataPackage_ReadMicroPIDValue, CCEAbstractTestDataPackage)
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
     return QByteArray().fill(0,4);
    }
};

/*******************************************************读取单控状态所有信息*************************************************************/
class CCE_COMMUNICATENGINE_EXPORT CCETestDataPackage_ReadAllInfo : public CCEAbstractTestDataPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCETestDataPackage_ReadAllInfo, CCEAbstractTestDataPackage)
public:
    STestData getInfo() const;
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_ReadFrame;
    }
    quint16 CmdCtrlAddr() const override{
        return quint16(ECommand::EC_Read_TDCurTemperature);
    }
    QByteArray CmdContent() const override{
     return QByteArray().fill(0,sizeof(STestData));
    }
};

/*******************************************************报告单控状态所有信息*************************************************************/
class CCE_COMMUNICATENGINE_EXPORT CCETestDataPackage_ReportAllInfo : public CCEAbstractTestDataPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCETestDataPackage_ReportAllInfo, CCEAbstractTestDataPackage)
public:
    CCETestDataPackage_ReportAllInfo(const quint8& ret);
    STestData getInfo() const;
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_ChartFrame;
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
#endif // CCETESTDATAPACKAGE_H
