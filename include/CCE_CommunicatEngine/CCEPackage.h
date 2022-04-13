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

//#define CCE_DECLARE_COMMANDSEND(d,pack) \
//    CCEEnginePackage enginePack;\
//    enginePack.initByDetectInfo(d->m_parentItemDetectInfo);\
//    enginePack.setData(pack.getDataToSend());\
//    if (sync) {\
//        CCEEnginePackage recEnginePack;\
//        CCEClusterProxy::syncSend(enginePack, recEnginePack, msec);\
//        return d->m_packageMgr.handle(CCEPackage(recEnginePack.data()));\
//    }\
//    else {\
//        return CCEClusterProxy::asyncSend(enginePack) ? LAPI::EResult::ER_INTECTRL_Success : LAPI::EResult::ER_INTECTRL_Fail_NoReason;\
//    }\

#define DO_GETOPERATIONRESULT() \
    quint8 value = 0;\
    QByteArray buffer = getContent(); \
    if (buffer.size() < 1) { \
        return value; }\
    memcpy(&value, buffer, sizeof(quint8)); \
    return value; \

//此类提供给不同协议的Package类在onReceive中调用
class CCE_COMMUNICATENGINE_EXPORT CCEPackage
{
    friend class CCEPackageManager;
    friend class CCEPackageDispatcher;
public:
    /******************************************协议中数据定义************************************************/
    enum EFrameType{
        EFT_NULL = 0,           //空
        EFT_WriteFrame = 0x81,  //写数据帧
        EFT_ReadFrame = 0x82,   //读数据帧
        EFT_ReportFrame = 0x83, //报告帧
        EFT_ChartFrame = 0x84,  //图谱数据帧
    };

    enum EUnitAddr{
        EUA_NULL = 0,               //空
        EUA_MainCtrl = 0x10,        //主控单元板
        EUA_PressureSensor = 0x11,  //压力传感器单元
        EUA_SingleCtrl = 0x12,      //单控控制单元
        EUA_SingleStatus = 0x13,    //单控状态单元
        EUA_TestParamSet = 0x14,    //测试参数设置单元
        EUA_TestData = 0x15,        //测试数据单元
        EUA_StatusWarn = 0x16,      //状态警告单元
    };

    enum EFrameError{
        EFE_Success = 0x00,     //命令帧接受正确
        EFE_CRCErr = 0x01,      //校验码错误
        EFE_FrameTypeErr = 0x02,//帧类型错误
        EFE_UnitAddrErr = 0x03, //单元地址错误
        EFE_CtrlAddrErr = 0x04, //控制地址错误
        EFE_DataLenErr = 0x05,  //数据长度错误
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

    /*********************解析数据时获取**************************/
    //判断是否有效
    bool isValid();
    //获取帧长度
    quint8 getFrameLength() const;
    //获取协议版本
    quint8 getFrameType() const;

    //获取单元地址
    quint8 getUnitAddr() const;
    //获取操作地址
    quint16 getCtrlAddr() const;

    //获取命令内容
    QByteArray getContent() const;

    //获取校验和
    quint16 getCheckSum() const;

    /*********************构建时用**************************/
    //创建校验和
    quint16 genCheckSum();
    //创建一个包
    CCEPackage& build();

protected:
    /*********************构建时用**************************/
    virtual EFrameType CmdFrameType() const;      //在具体协议的具体类中实现
    virtual EUnitAddr CmdUnitAddr() const;        //在不同单元协议的基类中实现
    virtual quint16 CmdCtrlAddr() const;    //在具体协议的具体类中实现
    virtual QByteArray CmdContent() const;  //在具体协议的具体类中实现

    /*********************解析时用**************************/
    //调用注册的回调处理函数
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
    //EUnitAddr m_unitAddr = EUA_NULL;
    /*********************解析时用**************************/
private:
    //void * m_callBack = nullptr;
    std::function<void(const QByteArray&)> m_callBack;
    QByteArray m_data;//整包数据
};
#endif
