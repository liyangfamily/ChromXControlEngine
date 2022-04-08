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
	quint8 head[7];	//0X55（7个）
	quint8 headCmd;	//0xC0

	bool operator==(tagIntegratedFrameLimit &other)
	{
		if (memcmp(this->head, other.head, 7) == 0&&this->headCmd==other.headCmd)
			return true;
		else
			return false;
	}

	tagIntegratedFrameLimit& build()
	{
		memset(this->head, 0x55, 7);
		this->headCmd = 0xC0;
		return *this; 
	}

}SIntegratedFrameLimit;

//LED一体机集成控制协议请求头3.0
typedef struct tagIntegratedCtrlProtocolHeader
{
    SIntegratedFrameLimit frameLimit;

    quint8 protocolNum; //0x01 LED一体机集成控制协议
    quint8 protocolVersion; //0x01 协议版本

    tagIntegratedCtrlProtocolHeader()
    {
        int i = sizeof(tagIntegratedCtrlProtocolHeader);
        memset(this, 0x00, i);
    }

}SIntegratedCtrlProtocolHeader;

//LED一体机集成控制协议请求头3.0
typedef struct tagIntegratedCtrlHeader
{
    SIntegratedCtrlProtocolHeader protocolHeader;

	quint16 targetDeviceType; //0xD001 目标设备类型-安卓设备
	quint16 sourceDeviceType; //0xD100 源设备类型-外部设备

	quint16 cmd; //命令码

	quint16 serialNumber; //流水号
	quint8  uuidType; //uuid类型
	QUuid uuid; //+16Uuid
	quint8 sendCardIndex; //发送卡序号

	quint16 dataLength;		//附加数据长度

	tagIntegratedCtrlHeader()
	{
		int i = sizeof(tagIntegratedCtrlHeader);
		memset(this, 0x00, i);
        protocolHeader.frameLimit.build();
	}

}SIntegratedCtrlHeader;

#pragma pack(pop)
#endif
