/*********************************************************************************************************
** This file is part of the CCE_Core module of the CCE Toolkit.
*********************************************************************************************************/
#ifndef CHROMX_H_CCEDEF
#define CHROMX_H_CCEDEF
#pragma once

/*
   CCE_VERSION is (major << 16) + (minor << 8) + patch.
*/
#define CCE_VERSION      CCE_VERSION_CHECK(CCE_VERSION_MAJOR, CCE_VERSION_MINOR, CCE_VERSION_PATCH)
/*
   can be used like #if (CCE_VERSION >= CCE_VERSION_CHECK(4, 4, 0))
*/
#define CCE_VERSION_CHECK(major, minor, patch) ((major<<16)|(minor<<8)|(patch))


#define CCE_VERSION_STR "1.0.0"
#define CCE_VERSION_MAJOR 1
#define CCE_VERSION_MINOR 0
#define CCE_VERSION_PATCH 0

#define CCE_Defalut_SyncTimeout 1500

#ifdef _DEBUG
#define CCE_MemoryLeaksDetect false
#else
#define CCE_MemoryLeaksDetect false
#endif

#endif
