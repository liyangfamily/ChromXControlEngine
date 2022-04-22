/*********************************************************************************************************
** This file is part of the CCE_CommunicatEngine module of the CCE Toolkit.
*********************************************************************************************************/
#ifndef CHROMX_H_CCEINTECTRLPACKAGESTRUCT
#define CHROMX_H_CCEINTECTRLPACKAGESTRUCT
#pragma once
#include <QUuid>

#pragma pack(push,1)
typedef struct tagIntegratedFrameLimit
{
    //帧定界符
    quint8 head1;	//0x69
    quint8 head2;	//0xAA

    bool operator==(tagIntegratedFrameLimit &other)
    {
        if ((this->head1 == other.head1 == 0) && (this->head2 == other.head2))
            return true;
        else
            return false;
    }

    tagIntegratedFrameLimit& build()
    {
        this->head1 = 0x69;
        this->head2 = 0xAA;
        return *this;
    }

}SIntegratedFrameLimit;

//控制协议头
typedef struct tagIntegratedCtrlProtocolHeader
{
    SIntegratedFrameLimit frameLimit;

    quint8 frameLength;		//帧长度
    quint8 frameType;       //帧类型

    tagIntegratedCtrlProtocolHeader()
    {
        int i = sizeof(tagIntegratedCtrlProtocolHeader);
        memset(this, 0x00, i);
    }

}SIntegratedCtrlProtocolHeader;

//控制头
typedef struct tagIntegratedCtrlHeader
{
    SIntegratedCtrlProtocolHeader protocolHeader;

    quint8 unitAddr;        //单元地址
    quint16 ctrlAddr;        //写首地址
    quint8 dataLength;      //写字节长度


    tagIntegratedCtrlHeader()
    {
        memset(this, 0x00, sizeof(tagIntegratedCtrlHeader));
        protocolHeader.frameLimit.build();
    }

}SIntegratedCtrlHeader;















//***************************************************1、主控模块所有模块结构体的定义***************************************************************/
typedef struct tagMainCtrl{
    quint8 hardWareVersion;             //0x0001	R/W	主控板硬件版本号：0-255
    quint8 armSoftwareVersion;          //0x0002	R/W	主控板嵌入式软件版本号：0-255
    quint8 selfTestStatus;              //0x0003	R/W	主控板开始自检：0（关闭） 1（开始自检）

    tagMainCtrl()
    {
        Q_ASSERT(sizeof(tagMainCtrl) == 3);
        clear();
    }
    void clear()
    {
        memset(this, 0, sizeof(tagMainCtrl));
    }

    bool setRawData(const QByteArray& rawData,int pos = 0){
        int effectSize = sizeof(tagMainCtrl) - pos;
        if(effectSize<0){
            return false;
        }
        if(rawData.size() > effectSize){
            qWarning("Raw data is too large , Trigger interception.");
            memcpy(this + pos,rawData.constData(),effectSize);
        }
        else{
            memcpy(this + pos,rawData.constData(),rawData.size());
        }
        return true;
    }

}SMainCtrl;










//***************************************************2、LED面板所有模块结构体的定义***************************************************************/
typedef struct tagPressureSensor{
    quint16 carrierGasPressure;         //0x0002-0x0003	R/	LED面板 压力传感器 载气压力1值
    quint16 samplingPumpPressure;       //0x0004-0x0005	R/	LED面板 压力传感器 采样泵压力2值
    quint16 auxGasPressure;             //0x0006-0x0007	R/	LED面板 压力传感器 辅助气压力3值
}SPressureSensor;

typedef struct tagLEDPanelLight{
    quint8 progress;    //0x0010	R/W	LED面板 检测进度条： 0-50 ，最大进度为50
    quint8 light1;      //0x0011	R/W	LED 面板 指示灯1： 0为关，1为开
    quint8 light2;      //0x0012	R/W	LED 面板 指示灯2： 0为关，1为开
    quint8 light3;      //0x0013	R/W	LED 面板 指示灯3： 0为关，1为开
    quint8 light4;      //0x0014	R/W	LED 面板 指示灯4： 0为关，1为开
    quint8 light5;      //0x0015	R/W	LED 面板 指示灯5： 0为关，1为开
}SLEDPanelLight;

typedef struct tagEnvSensor{
    quint16 envTemperature;             //0x0020-0x0021	R/	LED 面板 HDC1080环境温度值
    quint16 envHumidity;                //0x0022-0x0023	R/	LED 面板 HDC1080环境湿度值
    quint16 ambientAtmosphericPressure; //0x0024-0x0025	R/	LED 面板 BMP388环境大气压力值
}SEnvSensor;

typedef struct tagLEDPanelUnit{

    quint8 version;                     //0x0001	R/W	主控板硬件版本号：0-255
    SPressureSensor pressureSensor;
    quint8 reserved1[8];                //预留 0x0008 - 0x000f
    SLEDPanelLight panelLight;
    quint8 reserved2[10];               //预留 0x0016 - 0x001f
    SEnvSensor envSensor;

    tagLEDPanelUnit()
    {
        Q_ASSERT(sizeof(tagLEDPanelUnit) == 37);
        clear();
    }
    void clear()
    {
        memset(this, 0, sizeof(tagLEDPanelUnit));
    }

    bool setRawData(const QByteArray& rawData,int pos = 0){
        int effectSize = sizeof(tagLEDPanelUnit) - pos;
        if(effectSize<0){
            return false;
        }
        if(rawData.size() > effectSize){
            qWarning("Raw data is too large , Trigger interception.");
            memcpy(this + pos,rawData.constData(),effectSize);
        }
        else{
            memcpy(this + pos,rawData.constData(),rawData.size());
        }
        return true;
    }

}SLEDPanelUnit;









//***************************************************3、单控控制所有模块结构体的定义***************************************************************/
typedef struct tagSingleDeviceCtrl{
    quint16 startTime;
    quint8 PWMValue;
    quint8 startSwitch;
}SSingleDeviceCtrl;

typedef struct tagSingleMicroPIDCtrl{
    quint16 biasVoltage;
    quint16 freq;
    quint8 startSwitch;
}SSingleMicroPIDCtrll;

typedef struct tagSingleCtrl{
    quint8 pumpVoltage;                     //0x0001	R/W	Pump的电压值：0-100%， 0为关，100为12V
    quint8 samplingValveSwitch;             //0x0002	R/W	采样三通阀开关： 0 为关， 1为开
    quint8 testValveSwitch;                 //0x0003	R/W	检测三通阀开关： 0 为关， 1为开
    quint8 fanSwitch;                       //0x0004	R/W	风扇的开关： 0 为关， 1为开

    quint8 reserved1[12];

    SSingleDeviceCtrl TDCtrl;               //0x0010 TD单控

    quint8 reserved2[12];

    SSingleDeviceCtrl TICtrl;               //0x0020 TI单控

    quint8 reserved3[12];

    SSingleDeviceCtrl COLIMNCtrl;           //0x0030 COLUMN 单控

    quint8 reserved4[12];

    SSingleMicroPIDCtrll MicroPIDCtrl;      //0x0040 MicroPID 单控

    quint8 reserved5[11];

    quint16 EPCCtrlVoltage;                 //0x0050-0x0051 	R/W	EPC控制电压
    quint8 EPCSwitch;                       //0x0052	R/W	EPC开关： 0为关，1为开

    tagSingleCtrl()
    {
        Q_ASSERT(sizeof(tagSingleCtrl) == 83);
        clear();
    }
    void clear()
    {
        memset(this, 0, sizeof(tagSingleCtrl));
    }

    bool setRawData(const QByteArray& rawData,int pos = 0){
        int effectSize = sizeof(tagSingleCtrl) - pos;
        if(effectSize<0){
            return false;
        }
        if(rawData.size() > effectSize){
            qWarning("Raw data is too large , Trigger interception.");
            memcpy(this + pos,rawData.constData(),effectSize);
        }
        else{
            memcpy(this + pos,rawData.constData(),rawData.size());
        }
        return true;
    }

}SSingleCtrl;








//***************************************************4、单控状态模块所有模块结构体的定义***************************************************************/
typedef struct tagSingleStatus{
    quint16 TDCurTemperature;       //0x0000-0x0001	R/	TD 当前温度读数值 （ 0.1℃）
    quint16 TICurTemperature;       //0x0002-0x0003	R/	TI 当前温度读数值（0-65535）
    quint16 COLUMNTemperature;      //0x0004-0x0005	R/	COLUMN 当前温度转换值  	(0-65535)
    quint32 MicroPIDValue;          //0x0006-0x0009	R/	PID /HD-PID    ADC 数值
    quint16 EPCPressure;            //0x000a-0x000b	R/	EPC 压力读数

    tagSingleStatus()
    {
        Q_ASSERT(sizeof(tagSingleStatus) == 12);
        clear();
    }
    void clear()
    {
        memset(this, 0, sizeof(tagSingleStatus));
    }

    bool setRawData(const QByteArray& rawData,int pos = 0){
        int effectSize = sizeof(tagSingleStatus) - pos;
        if(effectSize<0){
            return false;
        }
        if(rawData.size() > effectSize){
            qWarning("Raw data is too large , Trigger interception.");
            memcpy(this + pos,rawData.constData(),effectSize);
        }
        else{
            memcpy(this + pos,rawData.constData(),rawData.size());
        }
        return true;
    }

}SSingleStatus;










//***************************************************5、测试参数设置模块所有模块结构体的定义***************************************************************/
typedef struct tagTimeCtrl{
    quint16 timeValue;
    quint8 PWMValue;
}STimeCtrl;

typedef struct tagPIDCtrl{
    quint16 timeValue;
    quint16 temperatureValue;
    quint8 PWMValue_Min;
    quint8 PWMValue_Max;
}SPIDCtrl;

typedef struct tagTDCtrl{
    quint8  BeforeTDStartup_TestPCG;
    quint16 TDStart_CarrierPressure_UpLimit;
    quint16 TDStart_CarrierPressure_LowLimit;
    quint8  BeforeTDStartup_TestTITemperature;
    quint16 BeforeTDStartup_TITemperature_Max;
    quint8  controlMode;

    STimeCtrl timeCtrlArray[5];
    SPIDCtrl PIDTimeCtrlArray[5];
}STDCtrl;

typedef struct tagTICtrl{
    quint8  BeforeTIStartup_TestMicroPID;
    quint32 BeforeTIStartup_MicroPIDValue_Min;
    quint8  controlMode;

    STimeCtrl timeCtrlArray[5];
    SPIDCtrl PIDTimeCtrlArray[5];
}STICtrl;

typedef struct tagCOLUMNCtrl{
    quint8  controlMode;

    STimeCtrl timeCtrlArray[8];
    SPIDCtrl PIDTimeCtrlArray[8];
}SCOLUMNCtrl;

typedef struct tagMicroPIDCtrl{
    quint16 startTime;
    quint8  samplingFreq;
    quint16 plasmaFreq;
    quint16 baseLineVoltage;
}SMicroPIDCtrl;






typedef struct tagTestParamSet{
    quint32 TD_PID_P_Parma;                 //0x0000-0x0003	R/W	TD  PID 参数 ， P 数值 ， (定点，6位小数)
    quint32 TD_PID_I_Parma;                 //0x0004-0x0007	R/W	TD  PID 参数 ， I 数值 ， (定点，6位小数)
    quint32 TD_PID_D_Parma;                 //0x0008-0x000b	R/W	TD  PID 参数 ，D 数值 ，(定点，6位小数)

    quint32 TI_PID_P_Parma;                 //0x000c-0x000f	R/W	TI PID 参数 ， P 数值 ， (定点，6位小数)
    quint32 TI_PID_I_Parma;                 //0x0010-0x0013	R/W	TI PID 参数 ， I 数值 ， (定点，6位小数)
    quint32 TI_PID_D_Parma;                 //0x0014-0x0017	R/W	TI PID 参数 ，D 数值 ，(定点，6位小数)

    quint32 COLUMN_PID_P_Parma;             //0x0018-0x001b	R/W	COLUMN PID 参数 ， P 数值 ， (定点，6位小数)
    quint32 COLUMN_PID_I_Parma;             //0x001c-0x001f	R/W	COLUMN PID 参数 ， I 数值 ， (定点，6位小数)
    quint32 COLUMN_PID_D_Parma;             //0x0020-0x0023	R/W	COLUMN PID 参数 ，D 数值 ，(定点，6位小数)

    quint16 COLUMNFanCloseTemperature;      //0x0024-0x0025	R/W	column风扇关闭条件： column 温度值：0-65536

    quint8 reserved1[10];

    quint16 cleaningTime;                   //0x0030-0x0031	R/W	清洗时间 (s)  (0-65535)
    quint16 samplingTime;                   //0x0032-0x0033	R/W	采样时间 (s)  (0-65535)
    quint8  samplingPumpVoltage;            //0x0034	R/W	采样泵电压 （0-100）
    quint16 EPCControlVoltage;              //0x0035-0x0036	R/W	EPC控制电压

    quint8  reserved2[4];

    STDCtrl TDCtrl;                         //TD 控制
    STICtrl TICtrl;                         //TI 控制
    SCOLUMNCtrl COLUMNCtrl;                 //COLUMN 控制

    quint8  reserved3[3];

    SMicroPIDCtrl microPIDCtrl;             //microPID 控制

    quint8 testData_AutoRepo;               //0x00f7	R/W	测试数据自动上传  0 不自动上传， 1自动上传
    quint8 testStatus;                      //0x00f8	R/W	测试运行/停止  0 停止，1 为运行

    tagTestParamSet()
    {
        Q_ASSERT(sizeof(tagTestParamSet) == 249);
        clear();
    }
    void clear()
    {
        memset(this, 0, sizeof(tagTestParamSet));
    }

    bool setRawData(const QByteArray& rawData,int pos = 0){
        int effectSize = sizeof(tagTestParamSet) - pos;
        if(effectSize<0){
            return false;
        }
        if(rawData.size() > effectSize){
            qWarning("Raw data is too large , Trigger interception.");
            memcpy(this + pos,rawData.constData(),effectSize);
        }
        else{
            memcpy(this + pos,rawData.constData(),rawData.size());
        }
        return true;
    }

}STestParamSet;










//***************************************************6、测试数据模块所有模块结构体的定义***************************************************************/
typedef struct tagTestData{
    quint16 TDCurTemperature;       //0x0000-0x0001	R/	TD 当前温度数值 (0.1℃) 	(0-65535)
    quint16 TICurTemperature;       //0x0002-0x0003	R/	TI 当前温度数值 	(0-65535)
    quint32 curTestRunTime;         //0x0004-0x0007	R/	当前测试运行的时间 （0.01s）	(32bit)
    quint16 COLUMNTemperature;      //0x0008-0x0009	R/	COLUMN 温度转换数值  	(0-65535)
    quint16 MicroPIDValue;          //0x000a-0x000d	R/	PID/HDPID 当前的ADC读数 	(32bit)

    tagTestData()
    {
        Q_ASSERT(sizeof(tagTestData) == 12);
        clear();
    }
    void clear()
    {
        memset(this, 0, sizeof(tagTestData));
    }

    bool setRawData(const QByteArray& rawData,int pos = 0){
        int effectSize = sizeof(tagTestData) - pos;
        if(effectSize<0){
            return false;
        }
        if(rawData.size() > effectSize){
            qWarning("Raw data is too large , Trigger interception.");
            memcpy(this + pos,rawData.constData(),effectSize);
        }
        else{
            memcpy(this + pos,rawData.constData(),rawData.size());
        }
        return true;
    }

}STestData;









//***************************************************7、状态报警模块所有模块结构体的定义***************************************************************/
typedef struct tagStatusWarn{
    quint8 existAbnormal;           //0x0000	R/	是否存在异常： 0 无， 1 有
    quint8 deviceStatus;            //0x0001	R/	bit0: 载气即将耗尽；bit1:无法维持载气压力；bit2: 采样压力异常；bit3:TD 故障;bit4: TI故障； bit5: Column 故障;bit6: PID故障;  bit7 超温报警
    quint8 mainCtrlSelfTestStatus;  //0x0002	R/	主控板自检完成标志：0 自检中，1自检完成

    tagStatusWarn()
    {
        Q_ASSERT(sizeof(tagStatusWarn) == 3);
        clear();
    }
    void clear()
    {
        memset(this, 0, sizeof(tagStatusWarn));
    }

    bool setRawData(const QByteArray& rawData,int pos = 0){
        int effectSize = sizeof(tagStatusWarn) - pos;
        if(effectSize<0){
            return false;
        }
        if(rawData.size() > effectSize){
            qWarning("Raw data is too large , Trigger interception.");
            memcpy(this + pos,rawData.constData(),effectSize);
        }
        else{
            memcpy(this + pos,rawData.constData(),rawData.size());
        }
        return true;
    }

}SStatusWarn;

#pragma pack(pop)
#endif
