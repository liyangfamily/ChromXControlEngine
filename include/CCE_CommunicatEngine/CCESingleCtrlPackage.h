#ifndef CCESINGLECTRLPACKAGE_H
#define CCESINGLECTRLPACKAGE_H

#include <CCE_CommunicatEngine/CCEPackage>

class CCE_COMMUNICATENGINE_EXPORT CCEAbstractSingleCtrlPackage : public CCEPackage
{
    friend class CCEPackageManager;
    friend class CCEPackageDispatcher;

public:
    enum ECommand
    {
        EC_Write_PumpVoltage = 0x0001,
        EC_Read_PumpVoltage = EC_Write_PumpVoltage,

        EC_Write_SampleValve = 0x0002,
        EC_Read_SampleValve = EC_Write_SampleValve,

        EC_Write_DetectValve = 0x0003,
        EC_Read_DetectValve = EC_Write_DetectValve,

        EC_Write_Fan = 0x0004,
        EC_Read_Fan = EC_Write_Fan,

        EC_Write_TDStartTime = 0x0010,
        EC_Read_TDStartTime = EC_Write_TDStartTime,

        EC_Write_TDPWM = 0x0012,
        EC_Read_TDPWM = EC_Write_TDPWM,

        EC_Write_TDSwitch = 0x0013,
        EC_Read_TDSwitch = EC_Write_TDSwitch,

        EC_Write_TIStartTime = 0x0020,
        EC_Read_TIStartTime = EC_Write_TIStartTime,

        EC_Write_TIPWM = 0x0022,
        EC_Read_TIPWM = EC_Write_TIPWM,

        EC_Write_TISwitch = 0x0023,
        EC_Read_TISwitch = EC_Write_TISwitch,

        EC_Write_COLUMNStartTime = 0x0030,
        EC_Read_COLUMNStartTime = EC_Write_COLUMNStartTime,

        EC_Write_COLUMNPWM = 0x0032,
        EC_Read_COLUMNPWM = EC_Write_COLUMNPWM,

        EC_Write_COLUMNSwitch = 0x0033,
        EC_Read_COLUMNSwitch = EC_Write_COLUMNSwitch,

        EC_Write_PIDBiasVoltage = 0x0040,
        EC_Read_PIDBiasVoltage = EC_Write_PIDBiasVoltage,

        EC_Write_PIDFrequency = 0x0042,
        EC_Read_PIDFrequency = EC_Write_PIDFrequency,

        EC_Write_PIDSwitch = 0x0044,
        EC_Read_PIDSwitch = EC_Write_PIDSwitch,

        EC_Write_EPCVoltage = 0x0050,
        EC_Read_EPCVoltage = EC_Write_EPCVoltage,

        EC_Write_EPCSwitch = 0x0052,
        EC_Read_EPCSwitch = EC_Write_EPCSwitch,

        EC_NLL = 0xFFFF,
    };

public:
    CCEAbstractSingleCtrlPackage();
    CCEAbstractSingleCtrlPackage(const QByteArray &data);
    virtual ~CCEAbstractSingleCtrlPackage();

protected:
    EUnitAddr CmdUnitAddr() const override {
        return EUnitAddr::EUA_SingleCtrl;
    };
};


//写入pump的电压
class CCE_COMMUNICATENGINE_EXPORT CCESingleCtrlPackage_WritePumpVoltage
        : public CCEAbstractSingleCtrlPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCESingleCtrlPackage_WritePumpVoltage, CCEAbstractSingleCtrlPackage)
public:
    CCESingleCtrlPackage_WritePumpVoltage(quint8 voltage);
    quint8 getOperationResult() const {
        DO_GETOPERATIONRESULT();
    }

protected:
    EFrameType CmdFrameType() const override {
        return EFrameType::EFT_WriteFrame;
    }
    quint16 CmdCtrlAddr() const override {
        return quint16(ECommand::EC_Write_PumpVoltage);
    }
    QByteArray CmdContent() const override {
        return QByteArray((char *)&m_voltage, 1);
    }

private:
    quint8 m_voltage = 0;
};


//读取pump的电压
class CCE_COMMUNICATENGINE_EXPORT CCESingleCtrlPackage_ReadPumpVoltage
        : public CCEAbstractSingleCtrlPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCESingleCtrlPackage_ReadPumpVoltage, CCEAbstractSingleCtrlPackage)
public:
    quint8 getPumpVoltage() const;

protected:
    EFrameType CmdFrameType() const override {
        return EFrameType::EFT_ReadFrame;
    }
    quint16 CmdCtrlAddr() const override {
        return quint16(ECommand::EC_Read_PumpVoltage);
    }
    QByteArray CmdContent() const override {
        return QByteArray().fill(0, m_dataLength);
    }

private:
    quint8 m_dataLength = 1;
};


//写入sample valve的状态
class CCE_COMMUNICATENGINE_EXPORT CCESingleCtrlPackage_WriteSampleValve
        : public CCEAbstractSingleCtrlPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCESingleCtrlPackage_WriteSampleValve, CCEAbstractSingleCtrlPackage)
public:
    CCESingleCtrlPackage_WriteSampleValve(quint8 onORoff);
    quint8 getOperationResult() const {
        DO_GETOPERATIONRESULT();
    }

protected:
    EFrameType CmdFrameType() const override {
        return EFrameType::EFT_WriteFrame;
    }
    quint16 CmdCtrlAddr() const override {
        return quint16(ECommand::EC_Write_SampleValve);
    }
    QByteArray CmdContent() const override {
        return QByteArray((char *)&m_onORoff, 1);
    }

private:
    quint8 m_onORoff = 0;
};


//读取sample valve的状态
class CCE_COMMUNICATENGINE_EXPORT CCESingleCtrlPackage_ReadSampleValve
        : public CCEAbstractSingleCtrlPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCESingleCtrlPackage_ReadSampleValve, CCEAbstractSingleCtrlPackage)
public:
    quint8 getSampleValveStatus() const;

protected:
    EFrameType CmdFrameType() const override {
        return EFrameType::EFT_ReadFrame;
    }
    quint16 CmdCtrlAddr() const override {
        return quint16(ECommand::EC_Read_SampleValve);
    }
    QByteArray CmdContent() const override {
        return QByteArray().fill(0, m_dataLength);
    }

private:
    quint8 m_dataLength = 1;
};


//写入detect valve的状态
class CCE_COMMUNICATENGINE_EXPORT CCESingleCtrlPackage_WriteDetectValve
        : public CCEAbstractSingleCtrlPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCESingleCtrlPackage_WriteDetectValve, CCEAbstractSingleCtrlPackage)
public:
    CCESingleCtrlPackage_WriteDetectValve(quint8 onORoff);
    quint8 getOperationResult() const {
        DO_GETOPERATIONRESULT();
    }

protected:
    EFrameType CmdFrameType() const override {
        return EFrameType::EFT_WriteFrame;
    }
    quint16 CmdCtrlAddr() const override {
        return quint16(ECommand::EC_Write_DetectValve);
    }
    QByteArray CmdContent() const override {
        return QByteArray((char *)&m_onORoff, 1);
    }

private:
    quint8 m_onORoff = 0;
};


//读取detect valve的状态
class CCE_COMMUNICATENGINE_EXPORT CCESingleCtrlPackage_ReadDetectValve
        : public CCEAbstractSingleCtrlPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCESingleCtrlPackage_ReadDetectValve, CCEAbstractSingleCtrlPackage)
public:
    quint8 getDetectValveStatus() const;

protected:
    EFrameType CmdFrameType() const override {
        return EFrameType::EFT_ReadFrame;
    }
    quint16 CmdCtrlAddr() const override {
        return quint16(ECommand::EC_Read_DetectValve);
    }
    QByteArray CmdContent() const override {
        return QByteArray().fill(0, m_dataLength);
    }

private:
    quint8 m_dataLength = 1;
};


//写入fan的状态
class CCE_COMMUNICATENGINE_EXPORT CCESingleCtrlPackage_WriteFan
        : public CCEAbstractSingleCtrlPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCESingleCtrlPackage_WriteFan, CCEAbstractSingleCtrlPackage)
public:
    CCESingleCtrlPackage_WriteFan(quint8 onORoff);
    quint8 getOperationResult() const {
        DO_GETOPERATIONRESULT();
    }

protected:
    EFrameType CmdFrameType() const override {
        return EFrameType::EFT_WriteFrame;
    }
    quint16 CmdCtrlAddr() const override {
        return quint16(ECommand::EC_Write_Fan);
    }
    QByteArray CmdContent() const override {
        return QByteArray((char *)&m_onORoff, 1);
    }

private:
    quint8 m_onORoff = 0;
};


//读取fan的状态
class CCE_COMMUNICATENGINE_EXPORT CCESingleCtrlPackage_ReadFan
        : public CCEAbstractSingleCtrlPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCESingleCtrlPackage_ReadFan, CCEAbstractSingleCtrlPackage)
public:
    quint8 getFanStatus() const;

protected:
    EFrameType CmdFrameType() const override {
        return EFrameType::EFT_ReadFrame;
    }
    quint16 CmdCtrlAddr() const override {
        return quint16(ECommand::EC_Read_Fan);
    }
    QByteArray CmdContent() const override {
        return QByteArray().fill(0, m_dataLength);
    }

private:
    quint8 m_dataLength = 1;
};


//写入TD状态
class CCE_COMMUNICATENGINE_EXPORT CCESingleCtrlPackage_WriteTDModule
        : public CCEAbstractSingleCtrlPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCESingleCtrlPackage_WriteTDModule, CCEAbstractSingleCtrlPackage)

public:
    enum TDParaType
    {
        TD_StartTime,
        TD_PWM,
        TD_Switch,
        TD_AllData,
    }TDParaTypeValue;

    CCESingleCtrlPackage_WriteTDModule(enum TDParaType TDParaType, quint16 TDParaValue);
    CCESingleCtrlPackage_WriteTDModule(quint16 TD_StartTime, quint8 TD_PWM, bool TD_Switch);

protected:
    EFrameType CmdFrameType() const override {
        return EFrameType::EFT_WriteFrame;
    };
    quint16 CmdCtrlAddr() const override;
    QByteArray CmdContent() const override;

private:
    quint16 m_TDStartTime = 0;
    quint8 m_TDPWM = 0;
    bool m_TDSwitch = 0;
};


//读取TD所有或部分设置
class CCE_COMMUNICATENGINE_EXPORT CCESingleCtrlPackage_ReadTDModule
        : public CCEAbstractSingleCtrlPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCESingleCtrlPackage_ReadTDModule, CCEAbstractSingleCtrlPackage)

public:
    SSingleDeviceCtrl getTDAllData() const;
    quint16 getTDStartTime() const;
    quint8 getTDPWM() const;
    quint8 getTDSwitch() const;

protected:
    EFrameType CmdFrameType() const override {
        return EFrameType::EFT_ReadFrame;
    }
    quint16 CmdCtrlAddr() const override {
        return quint16(ECommand::EC_Read_TDStartTime);
    }
    QByteArray CmdContent() const override {
        return QByteArray().fill(0, sizeof(SSingleDeviceCtrl));
    }

private:
    quint8 m_dataLength = 4;
};


//写入TI状态
class CCE_COMMUNICATENGINE_EXPORT CCESingleCtrlPackage_WriteTIModule
        : public CCEAbstractSingleCtrlPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCESingleCtrlPackage_WriteTIModule, CCEAbstractSingleCtrlPackage)

public:
    enum TIParaType
    {
        TI_StartTime,
        TI_PWM,
        TI_Switch,
        TI_AllData,
    }TIParaTypeValue;

    CCESingleCtrlPackage_WriteTIModule(enum TIParaType TIParaType, quint16 TIParaValue);
    CCESingleCtrlPackage_WriteTIModule(quint16 TI_StartTime, quint8 TI_PWM, bool TI_Switch);

protected:
    EFrameType CmdFrameType() const override {
        return EFrameType::EFT_WriteFrame;
    };
    quint16 CmdCtrlAddr() const override;
    QByteArray CmdContent() const override;

private:
    quint16 m_TIStartTime = 0;
    quint8 m_TIPWM = 0;
    bool m_TISwitch = 0;
};


//读取TI所有或部分设置
class CCE_COMMUNICATENGINE_EXPORT CCESingleCtrlPackage_ReadTIModule
        : public CCEAbstractSingleCtrlPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCESingleCtrlPackage_ReadTIModule, CCEAbstractSingleCtrlPackage)

public:
    SSingleDeviceCtrl getTIAllData() const;
    quint16 getTIStartTime() const;
    quint8 getTIPWM() const;
    quint8 getTISwitch() const;

protected:
    EFrameType CmdFrameType() const override {
        return EFrameType::EFT_ReadFrame;
    }
    quint16 CmdCtrlAddr() const override {
        return quint16(ECommand::EC_Read_TIStartTime);
    }
    QByteArray CmdContent() const override {
        return QByteArray().fill(0, m_dataLength);
    }

private:
    quint8 m_dataLength = 4;
};


//写入COLUNN状态
class CCE_COMMUNICATENGINE_EXPORT CCESingleCtrlPackage_WriteCOLUMNModule
        : public CCEAbstractSingleCtrlPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCESingleCtrlPackage_WriteCOLUMNModule, CCEAbstractSingleCtrlPackage)

public:
    enum COLUMNParaType
    {
        COLUMN_StartTime,
        COLUMN_PWM,
        COLUMN_Switch,
        COLUMN_AllData,
    }COLUMNParaTypeValue;

    CCESingleCtrlPackage_WriteCOLUMNModule(enum COLUMNParaType COLUMNParaType, quint16 COLUMNParaValue);
    CCESingleCtrlPackage_WriteCOLUMNModule(quint16 COLUMN_StartTime, quint8 COLUMN_PWM, bool COLUMN_Switch);

protected:
    EFrameType CmdFrameType() const override {
        return EFrameType::EFT_WriteFrame;
    };
    quint16 CmdCtrlAddr() const override;
    QByteArray CmdContent() const override;

private:
    quint16 m_COLUMNStartTime = 0;
    quint8 m_COLUMNPWM = 0;
    bool m_COLUMNSwitch = 0;
};


//读取COLUMN所有或部分设置
class CCE_COMMUNICATENGINE_EXPORT CCESingleCtrlPackage_ReadCOLUMNModule
        : public CCEAbstractSingleCtrlPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCESingleCtrlPackage_ReadCOLUMNModule, CCEAbstractSingleCtrlPackage)

public:
    SSingleDeviceCtrl getCOLUMNAllData() const;
    quint16 getCOLUMNStartTime() const;
    quint8 getCOLUMNPWM() const;
    quint8 getCOLUMNSwitch() const;

protected:
    EFrameType CmdFrameType() const override {
        return EFrameType::EFT_ReadFrame;
    }
    quint16 CmdCtrlAddr() const override {
        return quint16(ECommand::EC_Read_COLUMNStartTime);
    }
    QByteArray CmdContent() const override {
        return QByteArray().fill(0, m_dataLength);
    }

private:
    quint8 m_dataLength = 4;
};


//写入PID的状态
class CCE_COMMUNICATENGINE_EXPORT CCESingleCtrlPackage_WritePIDModule
        : public CCEAbstractSingleCtrlPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCESingleCtrlPackage_WritePIDModule, CCEAbstractSingleCtrlPackage)

public:
    enum PIDParaType
    {
        PID_BiasVoltage,
        PID_Frequency,
        PID_Switch,
        PID_AllData,
    }PIDParaTypeValue;

    CCESingleCtrlPackage_WritePIDModule(enum PIDParaType PIDParaType, quint16 PIDParaValue);
    CCESingleCtrlPackage_WritePIDModule(quint16 PID_BiasVoltage, quint16 PID_Frequency, bool PID_Switch);

protected:
    EFrameType CmdFrameType() const override {
        return EFrameType::EFT_WriteFrame;
    };
    quint16 CmdCtrlAddr() const override;
    QByteArray CmdContent() const override;

private:
    quint16 m_PIDBiasVoltage = 0;
    quint16 m_PIDFrequency = 0;
    bool m_PIDSwitch = 0;
};


//读取PID所有或部分设置
class CCE_COMMUNICATENGINE_EXPORT CCESingleCtrlPackage_ReadPIDModule
        : public CCEAbstractSingleCtrlPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCESingleCtrlPackage_ReadPIDModule, CCEAbstractSingleCtrlPackage)

public:
    SSingleMicroPIDCtrl getPIDAllData() const;
    quint16 getPIDBiasVoltage() const;
    quint8 getPIDFrequency() const;
    quint8 getPIDSwitch() const;

protected:
    EFrameType CmdFrameType() const override {
        return EFrameType::EFT_ReadFrame;
    }
    quint16 CmdCtrlAddr() const override {
        return quint16(ECommand::EC_Read_PIDBiasVoltage);
    }
    QByteArray CmdContent() const override {
        return QByteArray().fill(0, m_dataLength);
    }

private:
    quint8 m_dataLength = 5;
};


//写入EPC的控制电压
class CCE_COMMUNICATENGINE_EXPORT CCESingleCtrlPackage_WriteEPCVoltage
        : public CCEAbstractSingleCtrlPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCESingleCtrlPackage_WriteEPCVoltage, CCEAbstractSingleCtrlPackage)
public:
    CCESingleCtrlPackage_WriteEPCVoltage(quint16 EPC_Voltage);
    quint8 getOperationResult() const {
        DO_GETOPERATIONRESULT();
    }

protected:
    EFrameType CmdFrameType() const override {
        return EFrameType::EFT_WriteFrame;
    }
    quint16 CmdCtrlAddr() const override {
        return quint16(ECommand::EC_Write_EPCVoltage);
    }
    QByteArray CmdContent() const override {
        return QByteArray((char *)&m_EPCVoltage, 2);
    }

private:
    quint16 m_EPCVoltage = 0;
};


//读取EPC控制电压
class CCE_COMMUNICATENGINE_EXPORT CCESingleCtrlPackage_ReadEPCVoltage
        : public CCEAbstractSingleCtrlPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCESingleCtrlPackage_ReadEPCVoltage, CCEAbstractSingleCtrlPackage)

public:
    quint16 getEPCVoltage() const;

protected:
    EFrameType CmdFrameType() const override {
        return EFrameType::EFT_ReadFrame;
    }
    quint16 CmdCtrlAddr() const override {
        return quint16(ECommand::EC_Read_EPCVoltage);
    }
    QByteArray CmdContent() const override {
        return QByteArray().fill(0, m_dataLength);
    }

private:
    quint8 m_dataLength = 2;
};


//写入EPC的开关状态
class CCE_COMMUNICATENGINE_EXPORT CCESingleCtrlPackage_WriteEPCSwitch
        : public CCEAbstractSingleCtrlPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCESingleCtrlPackage_WriteEPCSwitch, CCEAbstractSingleCtrlPackage)
public:
    CCESingleCtrlPackage_WriteEPCSwitch(quint8 EPC_Switch);
    quint8 getOperationResult() const {
        DO_GETOPERATIONRESULT();
    }

protected:
    EFrameType CmdFrameType() const override {
        return EFrameType::EFT_WriteFrame;
    }
    quint16 CmdCtrlAddr() const override {
        return quint16(ECommand::EC_Write_EPCSwitch);
    }
    QByteArray CmdContent() const override {
        return QByteArray((char *)&m_EPCSwitch, 1);
    }

private:
    quint8 m_EPCSwitch = 0;
};


//读取EPC开关状态
class CCE_COMMUNICATENGINE_EXPORT CCESingleCtrlPackage_ReadEPCSwitch
        : public CCEAbstractSingleCtrlPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCESingleCtrlPackage_ReadEPCSwitch, CCEAbstractSingleCtrlPackage)

public:
    quint8 getEPCSwitch() const;

protected:
    EFrameType CmdFrameType() const override {
        return EFrameType::EFT_ReadFrame;
    }
    quint16 CmdCtrlAddr() const override {
        return quint16(ECommand::EC_Read_EPCSwitch);
    }
    QByteArray CmdContent() const override {
        return QByteArray().fill(0, m_dataLength);
    }

private:
    quint8 m_dataLength = 1;
};

#endif // CCESINGLECTRLPACKAGE_H
