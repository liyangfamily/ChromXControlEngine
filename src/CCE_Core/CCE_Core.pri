QT += core
CONFIG += c++11 qt

DEFINES += CCE_CORE_LIB

SOURCES += \
    CCESignalWaiter.cpp \
    CCEUIHelper.cpp 

HEADERS += \
    ../../include/CCE_Core/CCECoreGlobal.h \
    ../../include/CCE_Core/CCEDef.h \
    ../../include/CCE_Core/CCESignalWaiter.h \
    ../../include/CCE_Core/CCEUIHelper.h
