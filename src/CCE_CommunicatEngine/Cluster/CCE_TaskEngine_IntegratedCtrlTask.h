#ifndef CVTE_H_CCE_TASKENGINE_INTEGRATEDCTRLTASK
#define CVTE_H_CCE_TASKENGINE_INTEGRATEDCTRLTASK
#pragma once

#include "CCE_CommunicatEngine/CCEEnginePackage.h"
#include "CCE_CommunicatEngine/CCEMainCtrlPackage.h"
#include "../TaskEngine/CCE_TaskEngine_TaskBase.h"

class CCECluster;
class CCE_TaskEngine_IntegratedCtrlTask : public CCE_TaskEngine_TaskBase
{
    Q_OBJECT
public:
    explicit CCE_TaskEngine_IntegratedCtrlTask(CCECluster* pCluster, QObject* pSocket, QObject * parent = 0);
    ~CCE_TaskEngine_IntegratedCtrlTask();
    int run() override;
    void sendHelloPackage() override;
    void checkHeartBeating() override;
protected:
    //返回使用的字节数
    int filter_message(const CCEEnginePackage&, int offset);
    int filter_identifyProtocolHeader(const CCEEnginePackage&, int offset);
    int filter_identifyStandardHeader(const CCEEnginePackage&, int offset);
    //处理当前的消息块
    virtual int deal_current_message_block(const CCEEnginePackage&);

protected:
    CCECluster* m_pCluster;

    SIntegratedFrameLimit m_currentFrameLimit;
    SIntegratedFrameLimit m_standerFrameLimit;
    SIntegratedCtrlHeader m_currentHeader;
};

class CCE_TaskEngine_IntegratedCtrlUDPTask : public CCE_TaskEngine_IntegratedCtrlTask
{
public:
    explicit CCE_TaskEngine_IntegratedCtrlUDPTask(CCECluster* pCluster, QObject* pSocket, QObject * parent = 0);
    ~CCE_TaskEngine_IntegratedCtrlUDPTask();
    void sendHelloPackage() override;
protected:
    int deal_current_message_block(const CCEEnginePackage&) override;
protected:
    quint16 m_tagetDeviceType;
    QString m_broadCastIP;
    quint16 m_targetPort;
};

class CCE_TaskEngine_IntegratedCtrlCOMTask : public CCE_TaskEngine_IntegratedCtrlTask
{
public:
    explicit CCE_TaskEngine_IntegratedCtrlCOMTask(CCECluster* pCluster, QObject* pSocket, QObject * parent = 0);
    ~CCE_TaskEngine_IntegratedCtrlCOMTask();
    void sendHelloPackage() override;
protected:
    quint16 m_tagetDeviceType;
    int deal_current_message_block(const CCEEnginePackage&) override;
};
#endif
