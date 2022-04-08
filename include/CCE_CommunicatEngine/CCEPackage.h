/*********************************************************************************************************
** This file is part of the CCE_CommunicatEngine module of the CCE Toolkit.
*********************************************************************************************************/
#ifndef CHROMX_H_CCEPACKAGE
#define CHROMX_H_CCEPACKAGE
#pragma once
#include <CCE_CommunicatEngine/CCECommunicatEngineGlobal>
#include "CCE_CommunicatEngine/CCEInteCtrlPackageStruct.h"
#include "CCE_CommunicatEngine/CCECommunicatEngineDef.h"

#include <QByteArray>
#include <QDebug>
#include <QString>
#include <QUuid>
#include <QSize>
#include <QPoint>

#define CCE_DECLARE_PACKAGECONSTRUCTOR(Class,inheritsClass) \
    friend class CCEPackageManager;\
    friend class CCEPackageDispatcher;\
public:\
    Class() {}\
    Class(const QByteArray& data) :inheritsClass(data) {}\
    virtual ~Class() {};\

#define CCE_DECLARE_COMMANDSEND(d,pack) \
    CCEEnginePackage enginePack;\
    enginePack.initByDetectInfo(d->m_parentItemDetectInfo);\
    enginePack.setData(pack.getDataToSend());\
    if (sync) {\
        CCEEnginePackage recEnginePack;\
        CCEClusterProxy::syncSend(enginePack, recEnginePack, msec);\
        return d->m_packageMgr.handle(CCEPackage(recEnginePack.data()));\
    }\
    else {\
        return CCEClusterProxy::asyncSend(enginePack) ? LAPI::EResult::ER_INTECTRL_Success : LAPI::EResult::ER_INTECTRL_Fail_NoReason;\
    }\

#define DO_GETOPERATIONRESULT() \
    quint16 value = 0;\
    QByteArray buffer = getContent(); \
    if (buffer.size() < 2) { \
        return value; }\
    memcpy(&value, buffer, sizeof(quint16)); \
    return value; \

//此类提供给不同协议的Package类在onReceive中调用
class CCE_COMMUNICATENGINE_EXPORT CCEPackage
{
    friend class CCEPackageManager;
    friend class CCEPackageDispatcher;
public:
    enum EPackageClass
    {
        EPC_IntegratedCtrl = 0x01, //集控协议
        EPC_FileTransfer = 0x03, //文件传输协议
        EPC_NULL = 0xFF,
    };
    enum EPackageVersion
    {
        EPV_1_0 = 1,
        EPV_2_0 = 2,
        EPV_3_0 = 3,
        EPV_NULL = 0xFF,
    };
    enum EDeviceType
    {
        EDT_NULL=0x0000,
        EDT_Android = 0xD001,
        EDT_Monitor_In_Sender = 0xD002,
        EDT_MCU_In_Sender = 0xD003,
        EDT_ReceiveCard = 0xD004,
        EDT_FPGA = 0xD005,
        EDT_NT68400 = 0xD006,
        EDT_MS9570 = 0xD007,
        EDT_External = 0xD100,
        EDT_CtrlSW = 0xD200,
        EDT_Broadcast = 0xFFFF,
    };
    enum EUUIDType
    {
        EUT_SenderUUID = 0xC1,
        EUT_SenderGroupUUID = 0xC2,
        EUT_BroadcastUUID = 0xFF,
    };

    enum EOperationResult
    {
        EOR_NULL=0x0000, //空
        EOR_Success = 0x0001, //成功
        EOR_Fail_NoReason = 0x0002, //失败-无具体原因
        EOR_Fail_NoCOM = 0x0003, //失败-找不到对应串口
        EOR_Fail_NoRet = 0x0004, //失败-无返回
        EOR_Success_UpgradeImmediately = 0x0011, //成功-立即升级
        EOR_Fail_Busy = 0x8001, //失败-忙碌
        EOR_Fail_Exclusive = 0x8002, //失败-被占用
        EOR_Fail_NoCMD=0xF001, //失败-命令码不支持
    };

    enum EDataBlock
    {
        EDB_Header,
        EDB_Content,
        EDB_CheckSum
    };

    CCEPackage();
    CCEPackage(const QByteArray& data);
    virtual ~CCEPackage();
    CCEPackage(const CCEPackage& package);
    virtual CCEPackage& operator=(const CCEPackage& package);

    //获取用于发送的数据
    QByteArray getDataToSend() const;

    bool initByDetectInfo(const SDetectItemInfo*);
    /*********************构建时用**************************/
    void SetCmdTargetDevice(quint16 n);
    void SetCmdSourceDevice(quint16 n);
    void SetCmdUuidType(quint8 n);
    void SetCmdUuid(QUuid n);
    void SetCmdSenderIndex(quint8 n);

    /*********************解析数据时获取**************************/
    //获取协议号
    quint8 getProtocolNum() const;
    //获取协议版本
    quint8 getProtocolVersion() const;
    //获取命令号
    quint16 getCmdNum() const;
    //获取命令内容
    QByteArray getContent() const;
    //获取流水号
    quint16 getSerialNum() const;
    //获取校验和
    quint8 getCheckSum() const;
    //获取目标设备
    quint16 getTargetDevice() const;
    //获取源设备
    quint16 getSourceDevice() const;
    //获取Uuid类型
    quint8 getUuidType() const;
    //获取Uuid
    QUuid getUuid() const;
    //获取发送卡序号
    quint8 getSenderCardIndex() const;
    //获取附加数据长度
    quint16 getReplayDataLength() const;

    /*********************工具函数**************************/
    //重新计算校验和
    quint8 genCheckSum();
    //计算校验和
    static quint8 getCheckSum(const QByteArray& data);

    /*********************构建时用**************************/
    //创建一个包
    CCEPackage& build(quint16 serialNum);

protected:
    /*********************构建时用**************************/
    virtual quint8 CmdProtocolNum() const; //在不同协议的基类中实现
    virtual quint8 CmdProtocolVersion() const; //在不同协议的基类中实现
    quint16 CmdTargetDevice() const;
    quint16 CmdSourceDevice() const;
    virtual quint16 CmdNum() const; //在具体协议的具体类中实现
    virtual quint16 CmdRetNum() const; //在具体协议的具体类中实现
    quint8 CmdUuidType() const;
    QUuid CmdUuid() const;
    quint8 CmdSenderIndex() const;
    virtual QByteArray CmdContent() const; //在具体协议的具体类中实现


    /*********************解析时用**************************/
    //调用注册的回调函数
    void onReceive(const CCEPackage& package);

    //需要先注册回调函数,然后在onReceive函数中调用
    void setPackageCallBack(std::function<void(const QByteArray&)> cb)
    {
        m_callBack = cb;
    }

private:
    /*********************工具函数**************************/
    static QByteArray getData(const QByteArray& data, quint8 index);
protected:
    /*********************构建时用**************************/
    quint16 m_targetDeviceType = 0;
    quint16 m_sourceDeviceType = 0;
    quint8 m_uuidType = 0;;
    QUuid m_uuid;
    quint8 m_sendCardIndex = 0;
    /*********************解析时用**************************/
private:
    //void * m_callBack = nullptr;
    std::function<void(const QByteArray&)> m_callBack;
    QByteArray m_data;//整包数据
};
#endif
