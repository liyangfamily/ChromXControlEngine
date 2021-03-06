#include "CCE_CommunicatEngine/CCESingleCtrlPackage.h"

CCEAbstractSingleCtrlPackage::CCEAbstractSingleCtrlPackage()
{

}

CCEAbstractSingleCtrlPackage::CCEAbstractSingleCtrlPackage(const QByteArray &data)
    : CCEPackage(data)
{

}

CCEAbstractSingleCtrlPackage::~CCEAbstractSingleCtrlPackage()
{

}


//写入pump的电压值
CCESingleCtrlPackage_WritePumpVoltage::CCESingleCtrlPackage_WritePumpVoltage(quint8 voltage)
    : m_voltage(voltage)
{

}


//读取pump的电压值
quint8 CCESingleCtrlPackage_ReadPumpVoltage::getPumpVoltage() const
{
    DO_GETCHARRESULT(getContent());
}


//写入sample valve的状态
CCESingleCtrlPackage_WriteSampleValve::CCESingleCtrlPackage_WriteSampleValve(quint8 onORoff)
    : m_onORoff(onORoff)
{

}


//读取sample valve的状态
quint8 CCESingleCtrlPackage_ReadSampleValve::getSampleValveStatus() const
{
    DO_GETCHARRESULT(getContent());
}


//写入detect valve的状态
CCESingleCtrlPackage_WriteDetectValve::CCESingleCtrlPackage_WriteDetectValve(quint8 onORoff)
    : m_onORoff(onORoff)
{

}


//读取detect valve的状态
quint8 CCESingleCtrlPackage_ReadDetectValve::getDetectValveStatus() const
{
    DO_GETCHARRESULT(getContent());
}


//写入fan的状态
CCESingleCtrlPackage_WriteFan::CCESingleCtrlPackage_WriteFan(quint8 onORoff)
    : m_onORoff(onORoff)
{

}


//读取fan的状态
quint8 CCESingleCtrlPackage_ReadFan::getFanStatus() const
{
    DO_GETCHARRESULT(getContent());
}


//写入TD状态
CCESingleCtrlPackage_WriteTDModule
    ::CCESingleCtrlPackage_WriteTDModule(enum TDParaType TDParaType, quint16 TDParaValue)
{
    switch (TDParaType) {
    case TD_StartTime:
        m_TDStartTime = TDParaValue;
        break;
    case TD_PWM:
        m_TDPWM = (quint8)TDParaValue;
        break;
    case TD_Switch:
        m_TDSwitch = (bool)TDParaValue;
        break;
    default:
        m_TDStartTime = TDParaValue;
        break;
    }
    TDParaTypeValue = TDParaType;
}

CCESingleCtrlPackage_WriteTDModule
    ::CCESingleCtrlPackage_WriteTDModule(quint16 TD_StartTime, quint8 TD_PWM, bool TD_Switch)
    : m_TDStartTime(TD_StartTime), m_TDPWM(TD_PWM), m_TDSwitch(TD_Switch)
{
    TDParaTypeValue = TD_AllData;
}

quint16 CCESingleCtrlPackage_WriteTDModule::CmdCtrlAddr() const
{
    switch (TDParaTypeValue) {
    case TD_StartTime:
        return quint16(ECommand::EC_Write_TDStartTime);
    case TD_PWM:
        return quint16(ECommand::EC_Write_TDPWM);
    case TD_Switch:
        return quint16(ECommand::EC_Write_TDSwitch);
    default:
        return quint16(ECommand::EC_Write_TDStartTime);
    }
}

QByteArray CCESingleCtrlPackage_WriteTDModule::CmdContent() const
{
    switch (TDParaTypeValue) {
    case TD_StartTime: {
        quint16 m_TDStartTimeSwap = CCEUIHelper::bigLittleSwap16(m_TDStartTime);
        return QByteArray((char *)&m_TDStartTimeSwap, 2);
    }
    case TD_PWM:
        return QByteArray((char *)&m_TDPWM, 1);
    case TD_Switch:
        return QByteArray((char *)&m_TDSwitch, 1);
    default:
        quint16 m_TDStartTimeSwap = CCEUIHelper::bigLittleSwap16(m_TDStartTime);
        QByteArray TDStartTime = QByteArray((char *)&m_TDStartTimeSwap, 2);
        QByteArray TDPWM = QByteArray((char *)&m_TDPWM, 1);
        QByteArray TDSwitch = QByteArray((char *)&m_TDSwitch, 1);
        QByteArray TDAllData = TDStartTime.append(TDPWM).append(TDSwitch);
        return TDAllData;
    }
}


//读取TD所有设置
SSingleDeviceCtrl CCESingleCtrlPackage_ReadTDModule::getTDAllData() const
{
    SSingleDeviceCtrl TDAllData;
    QByteArray data = getContent();
    TDAllData.setRawData(data);
    TDAllData.bigLittleSwap();
    return TDAllData;
}


//读取TD启动时间
quint16 CCESingleCtrlPackage_ReadTDModule::getTDStartTime() const
{
    QByteArray buffer = getContent();
    if (buffer.size() < m_dataLength)
        return 0;
    const SSingleDeviceCtrl* TDAllData = (SSingleDeviceCtrl*)buffer.constData();
    return CCEUIHelper::bigLittleSwap16(TDAllData->startTime);
}


//读取TDPWM
quint8 CCESingleCtrlPackage_ReadTDModule::getTDPWM() const
{
    QByteArray buffer = getContent();
    if (buffer.size() < m_dataLength)
        return 0;
    const SSingleDeviceCtrl* TDAllData = (SSingleDeviceCtrl*)buffer.constData();
    return TDAllData->PWMValue;
}


//读取TDSwitch
quint8 CCESingleCtrlPackage_ReadTDModule::getTDSwitch() const
{
    QByteArray buffer = getContent();
    if (buffer.size() < m_dataLength)
        return 0;
    const SSingleDeviceCtrl* TDAllData = (SSingleDeviceCtrl*)buffer.constData();
    return TDAllData->startSwitch;
}


//写入TI状态
CCESingleCtrlPackage_WriteTIModule
    ::CCESingleCtrlPackage_WriteTIModule(enum TIParaType TIParaType, quint16 TIParaValue)
{
    switch (TIParaType) {
    case TI_StartTime:
        m_TIStartTime = TIParaValue;
        break;
    case TI_PWM:
        m_TIPWM = (quint8)TIParaValue;
        break;
    case TI_Switch:
        m_TISwitch = (bool)TIParaValue;
        break;
    default:
        m_TIStartTime = TIParaValue;
        break;
    }
    TIParaTypeValue = TIParaType;
}

CCESingleCtrlPackage_WriteTIModule
    ::CCESingleCtrlPackage_WriteTIModule(quint16 TI_StartTime, quint8 TI_PWM, bool TI_Switch)
    : m_TIStartTime(TI_StartTime), m_TIPWM(TI_PWM), m_TISwitch(TI_Switch)
{
    TIParaTypeValue = TI_AllData;
}

quint16 CCESingleCtrlPackage_WriteTIModule::CmdCtrlAddr() const
{
    switch (TIParaTypeValue) {
    case TI_StartTime:
        return quint16(ECommand::EC_Write_TIStartTime);
    case TI_PWM:
        return quint16(ECommand::EC_Write_TIPWM);
    case TI_Switch:
        return quint16(ECommand::EC_Write_TISwitch);
    default:
        return quint16(ECommand::EC_Write_TIStartTime);
    }
    return quint16(ECommand::EC_Write_TIStartTime);
}

QByteArray CCESingleCtrlPackage_WriteTIModule::CmdContent() const
{
    switch (TIParaTypeValue) {
    case TI_StartTime: {
        quint16 m_TIStartTimeSwap = CCEUIHelper::bigLittleSwap16(m_TIStartTime);
        return QByteArray((char *)&m_TIStartTimeSwap, 2);
    }
    case TI_PWM:
        return QByteArray((char *)&m_TIPWM, 1);
    case TI_Switch:
        return QByteArray((char *)&m_TISwitch, 1);
    default:
        quint16 m_TIStartTimeSwap = CCEUIHelper::bigLittleSwap16(m_TIStartTime);
        QByteArray TIStartTime = QByteArray((char *)&m_TIStartTimeSwap, 2);
        QByteArray TIPWM = QByteArray((char *)&m_TIPWM, 1);
        QByteArray TISwitch = QByteArray((char *)&m_TISwitch, 1);
        QByteArray TIAllData = TIStartTime.append(TIPWM).append(TISwitch);
        return TIAllData;
    }
}


//读取TI所有设置
SSingleDeviceCtrl CCESingleCtrlPackage_ReadTIModule::getTIAllData() const
{
    SSingleDeviceCtrl TIAllData;
    QByteArray data = getContent();
    TIAllData.setRawData(data);
    TIAllData.bigLittleSwap();
    return TIAllData;
}


//读取TI启动时间
quint16 CCESingleCtrlPackage_ReadTIModule::getTIStartTime() const
{
    QByteArray buffer = getContent();
    if (buffer.size() < m_dataLength)
        return 0;
    const SSingleDeviceCtrl* TIAllData = (SSingleDeviceCtrl*)buffer.constData();
    return CCEUIHelper::bigLittleSwap16(TIAllData->startTime);
}


//读取TIPWM
quint8 CCESingleCtrlPackage_ReadTIModule::getTIPWM() const
{
    QByteArray buffer = getContent();
    if (buffer.size() < m_dataLength)
        return 0;
    const SSingleDeviceCtrl* TIAllData = (SSingleDeviceCtrl*)buffer.constData();
    return TIAllData->PWMValue;
}


//读取TISwitch
quint8 CCESingleCtrlPackage_ReadTIModule::getTISwitch() const
{
    QByteArray buffer = getContent();
    if (buffer.size() < m_dataLength)
        return 0;
    const SSingleDeviceCtrl* TIAllData = (SSingleDeviceCtrl*)buffer.constData();
    return TIAllData->startSwitch;
}


//写入COLUNN状态
CCESingleCtrlPackage_WriteCOLUMNModule
    ::CCESingleCtrlPackage_WriteCOLUMNModule(enum COLUMNParaType COLUMNParaType, quint16 COLUMNParaValue)
{
    switch (COLUMNParaType) {
    case COLUMN_StartTime:
        m_COLUMNStartTime = COLUMNParaValue;
        break;
    case COLUMN_PWM:
        m_COLUMNPWM = (quint8)COLUMNParaValue;
        break;
    case COLUMN_Switch:
        m_COLUMNSwitch = (bool)COLUMNParaValue;
        break;
    default:
        break;
    }
    COLUMNParaTypeValue = COLUMNParaType;
}

CCESingleCtrlPackage_WriteCOLUMNModule
    ::CCESingleCtrlPackage_WriteCOLUMNModule(quint16 COLUMN_StartTime, quint8 COLUMN_PWM, bool COLUMN_Switch)
    : m_COLUMNStartTime(COLUMN_StartTime), m_COLUMNPWM(COLUMN_PWM), m_COLUMNSwitch(COLUMN_Switch)
{
    COLUMNParaTypeValue = COLUMN_AllData;
}

quint16 CCESingleCtrlPackage_WriteCOLUMNModule::CmdCtrlAddr() const
{
    switch (COLUMNParaTypeValue) {
    case COLUMN_StartTime:
        return quint16(ECommand::EC_Write_COLUMNStartTime);
    case COLUMN_PWM:
        return quint16(ECommand::EC_Write_COLUMNPWM);
    case COLUMN_Switch:
        return quint16(ECommand::EC_Write_COLUMNSwitch);
    default:
        return quint16(ECommand::EC_Write_COLUMNStartTime);
    }
    return quint16(ECommand::EC_Write_COLUMNStartTime);
}

QByteArray CCESingleCtrlPackage_WriteCOLUMNModule::CmdContent() const
{
    switch (COLUMNParaTypeValue) {
    case COLUMN_StartTime: {
        quint16 m_COLUMNStartTimeSwap = CCEUIHelper::bigLittleSwap16(m_COLUMNStartTime);
        return QByteArray((char *)&m_COLUMNStartTimeSwap, 2);
    }
    case COLUMN_PWM:
        return QByteArray((char *)&m_COLUMNPWM, 1);
    case COLUMN_Switch:
        return QByteArray((char *)&m_COLUMNSwitch, 1);
    default:
        quint16 m_COLUMNStartTimeSwap = CCEUIHelper::bigLittleSwap16(m_COLUMNStartTime);
        QByteArray COLUMNStartTime = QByteArray((char *)&m_COLUMNStartTimeSwap, 2);
        QByteArray COLUMNPWM = QByteArray((char *)&m_COLUMNPWM, 1);
        QByteArray COLUMNSwitch = QByteArray((char *)&m_COLUMNSwitch, 1);
        QByteArray COLUMNAllData = COLUMNStartTime.append(COLUMNPWM).append(COLUMNSwitch);
        return COLUMNAllData;
    }
}


//读取COLUMN所有设置
SSingleDeviceCtrl CCESingleCtrlPackage_ReadCOLUMNModule::getCOLUMNAllData() const
{
    SSingleDeviceCtrl COLUMNAllData;
    QByteArray data = getContent();
    COLUMNAllData.setRawData(data);
    COLUMNAllData.bigLittleSwap();
    return COLUMNAllData;
}


//读取COLUMN启动时间
quint16 CCESingleCtrlPackage_ReadCOLUMNModule::getCOLUMNStartTime() const
{
    QByteArray buffer = getContent();
    if (buffer.size() < m_dataLength)
        return 0;
    const SSingleDeviceCtrl* COLUMNAllData = (SSingleDeviceCtrl*)buffer.constData();
    return CCEUIHelper::bigLittleSwap16(COLUMNAllData->startTime);
}


//读取COLUMNPWM
quint8 CCESingleCtrlPackage_ReadCOLUMNModule::getCOLUMNPWM() const
{
    QByteArray buffer = getContent();
    if (buffer.size() < m_dataLength)
        return 0;
    const SSingleDeviceCtrl* COLUMNAllData = (SSingleDeviceCtrl*)buffer.constData();
    return COLUMNAllData->PWMValue;
}


//读取COLUMNSwitch
quint8 CCESingleCtrlPackage_ReadCOLUMNModule::getCOLUMNSwitch() const
{
    QByteArray buffer = getContent();
    if (buffer.size() < m_dataLength)
        return 0;
    const SSingleDeviceCtrl* COLUMNAllData = (SSingleDeviceCtrl*)buffer.constData();
    return COLUMNAllData->startSwitch;
}


//写入PID的状态
CCESingleCtrlPackage_WritePIDModule
    ::CCESingleCtrlPackage_WritePIDModule(enum PIDParaType PIDParaType, quint16 PIDParaValue)
{
    switch (PIDParaType) {
    case PID_BiasVoltage:
        m_PIDBiasVoltage = PIDParaValue;
        break;
    case PID_Frequency:
        m_PIDFrequency = PIDParaValue;
        break;
    case PID_Switch:
        m_PIDSwitch = (bool)PIDParaValue;
        break;
    default:
        break;
    }
    PIDParaTypeValue = PIDParaType;
}

CCESingleCtrlPackage_WritePIDModule
    ::CCESingleCtrlPackage_WritePIDModule(quint16 PID_BiasVoltage, quint16 PID_Frequency, bool PID_Switch)
    : m_PIDBiasVoltage(PID_BiasVoltage), m_PIDFrequency(PID_Frequency), m_PIDSwitch(PID_Switch)
{
    PIDParaTypeValue = PID_AllData;
}

quint16 CCESingleCtrlPackage_WritePIDModule::CmdCtrlAddr() const
{
    switch (PIDParaTypeValue) {
    case PID_BiasVoltage:
        return quint16(ECommand::EC_Write_PIDBiasVoltage);
    case PID_Frequency:
        return quint16(ECommand::EC_Write_PIDFrequency);
    case PID_Switch:
        return quint16(ECommand::EC_Write_PIDSwitch);
    default:
        return quint16(ECommand::EC_Write_PIDBiasVoltage);
    }
    return quint16(ECommand::EC_Write_PIDBiasVoltage);
}

QByteArray CCESingleCtrlPackage_WritePIDModule::CmdContent() const
{
    switch (PIDParaTypeValue) {
    case PID_BiasVoltage: {
        quint16 m_PIDBiasVoltageSwap = CCEUIHelper::bigLittleSwap16(m_PIDBiasVoltage);
        return QByteArray((char *)&m_PIDBiasVoltageSwap, 2);
    }
    case PID_Frequency: {
        quint16 m_PIDFrequencySwap = CCEUIHelper::bigLittleSwap16(m_PIDFrequency);
        return QByteArray((char *)&m_PIDFrequencySwap, 2);
    }
    case PID_Switch:
        return QByteArray((char *)&m_PIDSwitch, 1);
    default:
        quint16 m_PIDBiasVoltageSwap = CCEUIHelper::bigLittleSwap16(m_PIDBiasVoltage);
        quint16 m_PIDFrequencySwap = CCEUIHelper::bigLittleSwap16(m_PIDFrequency);
        QByteArray PIDBiasVoltage = QByteArray((char *)&m_PIDBiasVoltageSwap, 2);
        QByteArray PIDFrequency = QByteArray((char *)&m_PIDFrequencySwap, 2);
        QByteArray PIDSwitch = QByteArray((char *)&m_PIDSwitch, 1);
        QByteArray PIDAllData = PIDBiasVoltage.append(PIDFrequency).append(PIDSwitch);
        return PIDAllData;
    }
}


//读取PID所有设置
SSingleMicroPIDCtrl CCESingleCtrlPackage_ReadPIDModule::getPIDAllData() const
{
    SSingleMicroPIDCtrl PIDAllData;
    QByteArray data = getContent();
    PIDAllData.setRawData(data);
    PIDAllData.bigLittleSwap();
    return PIDAllData;
}


//读取PID偏置电压
quint16 CCESingleCtrlPackage_ReadPIDModule::getPIDBiasVoltage() const
{
    QByteArray buffer = getContent();
    if (buffer.size() < m_dataLength)
        return 0;
    const SSingleMicroPIDCtrl* PIDAllData = (SSingleMicroPIDCtrl*)buffer.constData();
    return CCEUIHelper::bigLittleSwap16(PIDAllData->biasVoltage);
}


//读取PID频率
quint16 CCESingleCtrlPackage_ReadPIDModule::getPIDFrequency() const
{
    QByteArray buffer = getContent();
    if (buffer.size() < m_dataLength)
        return 0;
    const SSingleMicroPIDCtrl* PIDAllData = (SSingleMicroPIDCtrl*)buffer.constData();
    return CCEUIHelper::bigLittleSwap16(PIDAllData->freq);
}


//读取PID开关状态
quint8 CCESingleCtrlPackage_ReadPIDModule::getPIDSwitch() const
{
    QByteArray buffer = getContent();
    if (buffer.size() < m_dataLength)
        return 0;
    const SSingleMicroPIDCtrl* PIDAllData = (SSingleMicroPIDCtrl*)buffer.constData();
    return PIDAllData->startSwitch;
}

//写入EPC的控制电压
CCESingleCtrlPackage_WriteEPCVoltage::CCESingleCtrlPackage_WriteEPCVoltage(quint16 EPC_Voltage)
    : m_EPCVoltage(CCEUIHelper::bigLittleSwap16(EPC_Voltage))
{

}


//读取EPC控制电压
quint16 CCESingleCtrlPackage_ReadEPCVoltage::getEPCVoltage() const
{
    DO_GETUSHORTRESULT(getContent());
}


//写入EPC的开关状态
CCESingleCtrlPackage_WriteEPCSwitch::CCESingleCtrlPackage_WriteEPCSwitch(quint8 EPC_Switch)
    : m_EPCSwitch(EPC_Switch)
{

}


//读取EPC开关状态
quint8 CCESingleCtrlPackage_ReadEPCSwitch::getEPCSwitch() const
{
    DO_GETCHARRESULT(getContent());
}
