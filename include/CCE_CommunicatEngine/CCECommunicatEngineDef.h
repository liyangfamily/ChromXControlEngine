#pragma once

#include <QObject>
#include <QString>
#include <QUuid>

enum ECommunicatType
{
    ECT_NULL,
    ECT_UDP,
    ECT_TCP,
    ECT_COM,
};

enum EPackageFromType
{
    EPFT_NULL,
    EPFT_Send,
    EPFT_Receive,
};

//探测方式
enum EDeviceDetectType
{
    EDDT_NULL = 0x00,
    EDDT_AUTO = 0x01,	//自动探卡
    EDDT_Manual = 0x02,	//手动指定
    EDDT_Test = 0xFF,

};

//设备状态
enum EDeviceStatus
{
    EDS_OffLine = 0x00,
    EDS_Online = 0x01, //在线
};

//设备类型
enum EDeviceType{
    EDT_NULL = 0,
    EDT_MainCOMDevice,
    EDT_AssistCOMDevice,
};

#if(1)
#pragma pack(1)
/*探卡能读取到的信息,用于添加设备*/
//网络信息部分
typedef struct tagNetInfo
{
    QString ipAddr = 0;
    quint16 port = 0;
}SNetInfo;
//串口信息部分
typedef struct tagComInfo
{
    QString comName = 0;
}SComInfo;
typedef struct tagDetectItemInfo
{
    EDeviceDetectType detectType;
    ECommunicatType communType;

    EDeviceStatus deviceStatus;
    EDeviceType deviceType;

    SNetInfo netInfo;
    SComInfo comInfo;

    QObject* socketObj = nullptr;
    QString hostName;

    tagDetectItemInfo()
    {
        this->clear();
    }
    void clear()
    {
        this->detectType = EDeviceDetectType::EDDT_NULL;
        this->communType = ECommunicatType::ECT_NULL;
        this->deviceStatus = EDeviceStatus::EDS_OffLine;
        this->deviceType = EDeviceType::EDT_NULL;
        this->netInfo.ipAddr.clear();
        this->netInfo.port = 0;
        this->comInfo.comName.clear();

        this->socketObj = nullptr;
        this->hostName.clear();

    }
    void set(const tagDetectItemInfo& other)
    {
        this->detectType = other.detectType;
        this->communType = other.communType;
        this->deviceStatus = other.deviceStatus;
        this->deviceType = other.deviceType;
        this->netInfo.ipAddr = other.netInfo.ipAddr;
        this->netInfo.port = other.netInfo.port;
        this->comInfo.comName = other.comInfo.comName;

        this->socketObj = other.socketObj;
        this->hostName = other.hostName;
    }
    tagDetectItemInfo(const tagDetectItemInfo&ohter)
    {
        this->set(ohter);
    }

    tagDetectItemInfo& operator=(const tagDetectItemInfo&other)
    {
        this->set(other);
        return *this;
    }

    bool operator==(const tagDetectItemInfo& other)const
    {
        if (/*this->uuidType == other.uuidType&& //Uuid后续启用,不启用期间可能会出现问题，因为无法唯一识别
            this->uuid == other.uuid&&*/
            this->socketObj == other.socketObj&&
            this->hostName==other.hostName)
        {
            return true;
        }
        else
        {
            return false;
        }
        //return memcmp(this, &other, sizeof(tagDetectItemInfo)) == 0 ? true : false;
    }

}SDetectItemInfo;
Q_DECLARE_METATYPE(SDetectItemInfo);
#pragma pack()
#endif
