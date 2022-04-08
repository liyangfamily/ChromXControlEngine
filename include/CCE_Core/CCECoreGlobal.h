/*********************************************************************************************************
** This file is part of the CCE_Core module of the CCE Toolkit.
*********************************************************************************************************/

#pragma once

#include <QtCore/qglobal.h>

#include <CCE_Core/CCEDef>
#if(CCE_MemoryLeaksDetect)
#include <vld.h>
#endif

#ifndef BUILD_STATIC
# if defined(CCE_CORE_LIB)
#  define CCE_CORE_EXPORT Q_DECL_EXPORT
# else
#  define CCE_CORE_EXPORT Q_DECL_IMPORT
# endif
#else
# define CCE_CORE_EXPORT
#endif
