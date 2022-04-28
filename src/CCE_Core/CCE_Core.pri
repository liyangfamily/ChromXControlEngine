QT += core
CONFIG += c++11 qt

DEFINES += CCE_CORE_LIB

SOURCES += \
    $$PWD/CCEJsonHelper.cpp \
    CCESignalWaiter.cpp \
    CCEUIHelper.cpp 

HEADERS += \
    $$PWD/../../include/CCE_Core/CCEAPIDef \
    $$PWD/../../include/CCE_Core/CCEAPIDef.h \
    $$PWD/../../include/CCE_Core/CCEAPIDefResult.h \
    $$PWD/../../include/CCE_Core/CCEAPIDefUI.h \
    $$PWD/../../include/CCE_Core/CCEJsonHelper.h \
    ../../include/CCE_Core/CCECoreGlobal.h \
    ../../include/CCE_Core/CCEDef.h \
    ../../include/CCE_Core/CCESignalWaiter.h \
    ../../include/CCE_Core/CCEUIHelper.h
