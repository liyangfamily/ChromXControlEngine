#ifndef CCETESTPARAMSETPACKAGE_H
#define CCETESTPARAMSETPACKAGE_H

#include <CCE_CommunicatEngine/CCEPackage>

class CCE_COMMUNICATENGINE_EXPORT CCEAbstractTestParamSetPackage : public CCEPackage
{
    friend class CCEPackageManager;
    friend class CCEPackageDispatcher;

public:
    enum ECommand
    {
        EC_Read_TD_PID_P_Parma = 0x0000,  //TD PID 参数 ， P 数值 ， (定点，6位小数)
        EC_Write_TD_PID_P_Parma = EC_Read_TD_PID_P_Parma,

        EC_Read_TD_PID_I_Parma = 0x0004,  //TD PID 参数 ， P 数值 ， (定点，6位小数)
        EC_Write_TD_PID_I_Parma = EC_Read_TD_PID_I_Parma,

        EC_Read_TD_PID_D_Parma = 0x0008,  //TD PID 参数 ， P 数值 ， (定点，6位小数)
        EC_Write_TD_PID_D_Parma = EC_Read_TD_PID_D_Parma,

        EC_Read_TI_PID_P_Parma = 0x000C,  //TI PID 参数 ， P 数值 ， (定点，6位小数)
        EC_Write_TI_PID_P_Parma = EC_Read_TI_PID_P_Parma,

        EC_Read_TI_PID_I_Parma = 0x0010,  //TI PID 参数 ， P 数值 ， (定点，6位小数)
        EC_Write_TI_PID_I_Parma = EC_Read_TI_PID_I_Parma,

        EC_Read_TI_PID_D_Parma = 0x0014,  //TI PID 参数 ， P 数值 ， (定点，6位小数)
        EC_Write_TI_PID_D_Parma = EC_Read_TI_PID_D_Parma,

        EC_Read_COLUMN_PID_P_Parma = 0x0018,  //COLUMN PID 参数 ， P 数值 ， (定点，6位小数)
        EC_Write_COLUMN_PID_P_Parma = EC_Read_COLUMN_PID_P_Parma,

        EC_Read_COLUMN_PID_I_Parma = 0x001C,  //COLUMN PID 参数 ， P 数值 ， (定点，6位小数)
        EC_Write_COLUMN_PID_I_Parma = EC_Read_COLUMN_PID_I_Parma,

        EC_Read_COLUMN_PID_D_Parma = 0x0020,  //COLUMN PID 参数 ， P 数值 ， (定点，6位小数)
        EC_Write_COLUMN_PID_D_Parma = EC_Read_COLUMN_PID_D_Parma,

        EC_Read_COLUMNFanCloseTemperature = 0x0024, //column风扇关闭条件： column 温度值：0-65536
        EC_Write_COLUMNFanCloseTemperature = EC_Read_COLUMNFanCloseTemperature,

        EC_Read_CleaningTime = 0x0030, //清洗时间 (s)  (0-65535)
        EC_Write_CleaningTime = EC_Read_CleaningTime,

        EC_Read_SamplingTime = 0x0032, //采样时间 (s)  (0-65535)
        EC_Write_SamplingTime = EC_Read_SamplingTime,

        EC_Read_SamplingPumpVoltage = 0x0034, //采样泵电压 （0-100）
        EC_Write_SamplingPumpVoltage = EC_Read_SamplingPumpVoltage,

        EC_Read_EPCControlVoltage = 0x0035, //EPC控制电压
        EC_Write_EPCControlVoltage = EC_Read_EPCControlVoltage,


        //TD
        EC_Read_BeforeTDStartup_TestPCG = 0x003B, //TD 启动测试Pcg 0 不检测， 1 检测
        EC_Write_BeforeTDStartup_TestPCG = EC_Read_BeforeTDStartup_TestPCG,
        EC_Read_TDStart_CarrierPressure_UpLimit = 0x003C, //TD 启动载气压力上限 （0-65535）
        EC_Write_TDStart_CarrierPressure_UpLimit = EC_Read_TDStart_CarrierPressure_UpLimit,
        EC_Read_TDStart_CarrierPressure_LowLimit = 0x003E, //TD 启动载气压力下限 （0-65535）
        EC_Write_TDStart_CarrierPressure_LowLimit = EC_Read_TDStart_CarrierPressure_LowLimit,
        EC_Read_BeforeTDStartup_TestTITemperature = 0x0040, //TD 启动前检测TI温度 0 不检测， 1 检测
        EC_Write_BeforeTDStartup_TestTITemperature = EC_Read_BeforeTDStartup_TestTITemperature,
        EC_Read_BeforeTDStartup_TITemperature_Max = 0x0041, //TD 启动前 TI温度 的最高温度
        EC_Write_BeforeTDStartup_TITemperature_Max = EC_Read_BeforeTDStartup_TITemperature_Max,
        EC_Read_TDControlMode = 0x0043, //TD 控制模式：0 非PID 自控温模式，1  PID 自控温模式
        EC_Write_TDControlMode = EC_Read_TDControlMode,

        EC_Read_TDTimeCtrl1 = 0x0044, //TD 时间控制1
        EC_Write_TDTimeCtrl1 = EC_Read_TDTimeCtrl1,
        EC_Read_TDPIDTimeCtrl1 = 0x0053, //TD PID时间控制1
        EC_Write_TDPIDTimeCtrl1 = EC_Read_TDPIDTimeCtrl1,

        //TI
        EC_Read_BeforeTIStartup_TestMicroPID = 0x0071, //TI 启动前检测PID/ HD-PID值 0 不检测，1 检测
        EC_Write_BeforeTIStartup_TestMicroPID = EC_Read_BeforeTIStartup_TestMicroPID,
        EC_Read_BeforeTIStartup_MicroPIDValue_Min = 0x0072, //TI 启动前PID/ HD-PID最低值
        EC_Write_BeforeTIStartup_MicroPIDValue_Min = EC_Read_BeforeTIStartup_MicroPIDValue_Min,
        EC_Read_TIControlMode = 0x0076, //TI 控制模式：0 非PID 自控温模式，1  PID 自控温模式
        EC_Write_TIControlMode = EC_Read_TIControlMode,

        EC_Read_TITimeCtrl1 = 0x0077, //TI 时间控制1
        EC_Write_TITimeCtrl1 = EC_Read_TITimeCtrl1,
        EC_Read_TIPIDTimeCtrl1 = 0x0086, //TI PID时间控制1
        EC_Write_TIPIDTimeCtrl1 = EC_Read_TIPIDTimeCtrl1,

        //COLUMN
        EC_Read_COLUMNControlMode = 0x00A4, //COLUMN 控制模式：0 非PID 自控温模式，1  PID 自控温模式
        EC_Write_COLUMNControlMode = EC_Read_TIControlMode,

        EC_Read_COLUMNTimeCtrl1 = 0x00A5, //COLUMN 时间控制1
        EC_Write_COLUMNTimeCtrl1 = EC_Read_COLUMNTimeCtrl1,
        EC_Read_COLUMNPIDTimeCtrl1 = 0x00BD, //COLUMN PID时间控制1
        EC_Write_COLUMNPIDTimeCtrl1 = EC_Read_COLUMNPIDTimeCtrl1,

        //MicroPID
        EC_Read_MicroPIDStartTime = 0x00F0, //PID/HD-PID 启动时间（s）
        EC_Write_MicroPIDStartTime = EC_Read_MicroPIDStartTime,
        EC_Read_MicroPIDSamplingFreq = 0x00F2, //PID/HD-PID 采样频率 （1-100）
        EC_Write_MicroPIDSamplingFreq = EC_Read_MicroPIDSamplingFreq,
        EC_Read_MicroPIDPlasmaFreq = 0x00F3, //HD-PID  plasma的频率 （100HZ）
        EC_Write_MicroPIDPlasmaFreq = EC_Read_MicroPIDPlasmaFreq,
        EC_Read_MicroPIDBaseLineVoltage = 0x00F5, //PID/HD-PID  Baseline Voltage (0-65535)
        EC_Write_MicroPIDBaseLineVoltage = EC_Read_MicroPIDBaseLineVoltage,


        EC_Read_TestData_AutoRepo = 0x00F7, //测试数据自动上传  0 不自动上传， 1自动上传
        EC_Write_TestData_AutoRepo = EC_Read_TestData_AutoRepo,

        EC_Read_TestStatus = 0x00F8, //测试运行/停止  0 停止，1 为运行
        EC_Write_TestStatus = EC_Read_TestStatus,

        EC_NLL = 0xFFFF,
    };

public:
    CCEAbstractTestParamSetPackage();
    CCEAbstractTestParamSetPackage(const QByteArray &data);
    virtual ~CCEAbstractTestParamSetPackage();

protected:
    EUnitAddr CmdUnitAddr() const override {
        return EUnitAddr::EUA_TestParamSet;
    };
};

/*******************************************************所有PID*************************************************************/
class CCE_COMMUNICATENGINE_EXPORT CCETestParamSetPackage_ReadAllPID : public CCEAbstractTestParamSetPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCETestParamSetPackage_ReadAllPID, CCEAbstractTestParamSetPackage)
public:
    SPIDAll getValue() const;
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_ReadFrame;
    }
    quint16 CmdCtrlAddr() const override{
        return quint16(ECommand::EC_Read_TD_PID_P_Parma);
    }
    QByteArray CmdContent() const override{
     return QByteArray().fill(0,sizeof(SPIDAll));
    }
};

class CCE_COMMUNICATENGINE_EXPORT CCETestParamSetPackage_WriteAllPID : public CCEAbstractTestParamSetPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCETestParamSetPackage_WriteAllPID, CCEAbstractTestParamSetPackage)
public:
    CCETestParamSetPackage_WriteAllPID(const SPIDAll& PIDAll);
    quint8 getOperationResult() const{
        DO_GETOPERATIONRESULT();
    }
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_WriteFrame;
    }
    quint16 CmdCtrlAddr() const override{
        return quint16(ECommand::EC_Write_TD_PID_P_Parma);
    }
    QByteArray CmdContent() const override{
     return QByteArray((char *)&m_PIDAll, sizeof(SPIDAll));
    }
private:
    SPIDAll m_PIDAll;
};

/*******************************************************测试参数*************************************************************/
class CCE_COMMUNICATENGINE_EXPORT CCETestParamSetPackage_ReadRunParam : public CCEAbstractTestParamSetPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCETestParamSetPackage_ReadRunParam, CCEAbstractTestParamSetPackage)
public:
    //在读取不同偏移时用
    CCETestParamSetPackage_ReadRunParam(quint16 offsetPos,quint8 readLenght);
    //在解析不同偏移时用
    CCETestParamSetPackage_ReadRunParam(quint16 offsetPos,const QByteArray& data);
    QByteArray getValue() const;
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_ReadFrame;
    }
    quint16 CmdCtrlAddr() const override{
        return m_address;
    }
    QByteArray CmdContent() const override{
     return QByteArray().fill(0,m_readLenght);
    }
private:
    quint16 m_address = ECommand::EC_Read_COLUMNFanCloseTemperature;
    quint8 m_readLenght = 0;
};

class CCE_COMMUNICATENGINE_EXPORT CCETestParamSetPackage_WriteRunParam : public CCEAbstractTestParamSetPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCETestParamSetPackage_WriteRunParam, CCEAbstractTestParamSetPackage)
public:
    //在写入不同偏移时用
    CCETestParamSetPackage_WriteRunParam(quint16 offsetPos, const QByteArray& writeData);
    //在解析不同偏移时用
    CCETestParamSetPackage_WriteRunParam(const QByteArray& parseData,quint16 offsetPos);
    quint8 getOperationResult() const{
        DO_GETOPERATIONRESULT();
    }
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_WriteFrame;
    }
    quint16 CmdCtrlAddr() const override{
        return m_address;
    }
    QByteArray CmdContent() const override{
     return m_writeData;
    }
private:
    quint16 m_address = ECommand::EC_Write_COLUMNFanCloseTemperature;
    QByteArray m_writeData;
};

/*******************************************************测试运行/停止*************************************************************/
class CCE_COMMUNICATENGINE_EXPORT CCETestParamSetPackage_ReadTestStatus : public CCEAbstractTestParamSetPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCETestParamSetPackage_ReadTestStatus, CCEAbstractTestParamSetPackage)
public:
    quint8 getValue() const;
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_ReadFrame;
    }
    quint16 CmdCtrlAddr() const override{
        return quint16(ECommand::EC_Read_TestStatus);
    }
    QByteArray CmdContent() const override{
     return QByteArray().fill(0,1);
    }
};

class CCE_COMMUNICATENGINE_EXPORT CCETestParamSetPackage_WriteTestStatus : public CCEAbstractTestParamSetPackage
{
    CCE_DECLARE_PACKAGECONSTRUCTOR(CCETestParamSetPackage_WriteTestStatus, CCEAbstractTestParamSetPackage)
public:
    CCETestParamSetPackage_WriteTestStatus(quint8 value);
    quint8 getOperationResult() const{
        DO_GETOPERATIONRESULT();
    }
protected:
    EFrameType CmdFrameType () const override {
        return EFrameType::EFT_WriteFrame;
    }
    quint16 CmdCtrlAddr() const override {
        return quint16(ECommand::EC_Write_TestStatus);
    }
    QByteArray CmdContent() const override {
     return QByteArray((char *)&m_value, 1);
    }
private:
    quint8 m_value = 0;
};
#endif // CCETESTPARAMSETPACKAGE_H
