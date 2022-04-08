#pragma once

#include <QtCore/qglobal.h>

#include <CCE_Core/CCEDef>
#if(CCE_MemoryLeaksDetect)
#include <vld.h>
#endif

#ifndef BUILD_STATIC
# if defined(CCE_COMMUNICATENGINE_LIB)
#  define CCE_COMMUNICATENGINE_EXPORT Q_DECL_EXPORT
# else
#  define CCE_COMMUNICATENGINE_EXPORT Q_DECL_IMPORT
# endif
#else
# define CCE_COMMUNICATENGINE_EXPORT
#endif
