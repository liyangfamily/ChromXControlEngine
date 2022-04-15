#ifndef CVTE_H_ChromXItem_GLOBAL
#define CVTE_H_ChromXItem_GLOBAL
#pragma once

#include <QtCore/qglobal.h>

#include <CCE_Core/CCEDef>
#if(CCE_MemoryLeaksDetect)
#include <vld.h>
#endif

#ifndef BUILD_STATIC
# if defined(CCE_ChromXItem_LIB)
#  define CCE_CHROMXITEM_EXPORT Q_DECL_EXPORT
# else
#  define CCE_CHROMXITEM_EXPORT Q_DECL_IMPORT
# endif
#else
# define CCE_CHROMXITEM_EXPORT
#endif

#endif
