#ifndef CVTE_H_LAPI_STRUCT_RESULT
#define CVTE_H_LAPI_STRUCT_RESULT
#pragma once

namespace CCEAPI
{
    /*API函数返回状态*/
    enum EResult
    {
        ER_Success = 0x0000,     //命令帧接受正确
        ER_CRCErr = 0x0001,      //校验码错误
        ER_FrameTypeErr = 0x0002,//帧类型错误
        ER_UnitAddrErr = 0x0003, //单元地址错误
        ER_CtrlAddrErr = 0x0004, //控制地址错误
        ER_DataLenErr = 0x0005,  //数据长度错误
        //
        ER_Fail = 0xE000,
        ER_InDataError = 0xE002,
        ER_InDataNullptr = 0xE003,
        ER_NotSupportThisCommand = 0xE004,

        ER_CannotEnterExclusiveMode = 0xE005,
        ER_InExclusiveMode = 0xE006,
        ER_ExclusiveKeyNotMatch = 0xE007,

        ER_SyncSendTimeOut = 0xE008,
        ER_SyncSendLockFail = 0xE009,
    };
}
#endif // CVTE_H_LAPI_STRUCT_RESULT
