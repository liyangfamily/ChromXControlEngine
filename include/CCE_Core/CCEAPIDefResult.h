#ifndef CVTE_H_LAPI_STRUCT_RESULT
#define CVTE_H_LAPI_STRUCT_RESULT
#pragma once

namespace CCEAPI
{
    /*API函数返回状态*/
    enum EResult
    {
        //
        ER_Fail = 0xE000,
        ER_Success = 0xE001, //成功
        ER_InDataError = 0xE002,
        ER_InDataNullptr = 0xE003,
        ER_CannotEnterExclusiveMode = 0xE004,
        ER_NoSenderCardSelect = 0xE005,
        ER_NotSupportThisCommand = 0xE006,
        ER_SyncSendTimeOut = 0xE007,
    };
}
#endif // CVTE_H_LAPI_STRUCT_RESULT
