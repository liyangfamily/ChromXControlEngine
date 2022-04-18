QT += core network serialport
CONFIG += c++11 qt

DEFINES += CCE_ChromXItem_LIB

HEADERS += \
    $$PWD/../../include/CCE_ChromXItem/CCEChromXItemGlobal.h \
    $$PWD/../../include/CCE_ChromXItem/CCEChromXItemStructGlobal.h \
    $$PWD/../../include/CCE_ChromXItem/CCEChromXDevice.h \
    $$PWD/../../include/CCE_ChromXItem/CCEDetectServer.h \
    $$PWD/../../include/CCE_ChromXItem/CCEMainCtrlDevice.h \
    $$PWD/../../include/CCE_ChromXItem/CCEAbstractModule.h \
    $$PWD/CCEAbstractModule_p.h

SOURCES += \
    $$PWD/CCEAbstractModule.cpp \
    $$PWD/CCEChromXDevice.cpp \
    $$PWD/CCEDetectServer.cpp \
    $$PWD/CCEMainCtrlDevice.cpp



