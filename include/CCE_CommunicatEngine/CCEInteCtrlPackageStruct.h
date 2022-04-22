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

#pragma pack(pop)
#endif
