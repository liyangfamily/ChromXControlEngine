QT += core network serialport
CONFIG += c++11 qt

DEFINES += CCE_ChromXItem_LIB

HEADERS += \
    $$PWD/../../include/CCE_ChromXItem/CCEChromXItemGlobal.h \
    $$PWD/../../include/CCE_ChromXItem/CCEChromXItemStructGlobal.h \
    $$PWD/../../include/CCE_ChromXItem/CCEChromXDevice.h \
    $$PWD/../../include/CCE_ChromXItem/CCEDetectServer.h \
    $$PWD/../../include/CCE_ChromXItem/CCELEDPanelUnitDevice.h \
    $$PWD/../../include/CCE_ChromXItem/CCEMainCtrlDevice.h \
    $$PWD/../../include/CCE_ChromXItem/CCEAbstractModule.h \
    $$PWD/CCEAbstractModule_p.h \
    $$PWD/../../include/CCE_ChromXItem/CCESingleCtrlDevice.h \
    $$PWD/../../include/CCE_ChromXItem/CCESingleStatusDevice.h \
    $$PWD/../../include/CCE_ChromXItem/CCEStatusWarnDevice.h \
    $$PWD/../../include/CCE_ChromXItem/CCETestDataDevice.h \
    $$PWD/../../include/CCE_ChromXItem/CCETestParamSetDevice.h

SOURCES += \
    $$PWD/CCEAbstractModule.cpp \
    $$PWD/CCEChromXDevice.cpp \
    $$PWD/CCEDetectServer.cpp \
    $$PWD/CCELEDPanelUnitDevice.cpp \
    $$PWD/CCEMainCtrlDevice.cpp \
    $$PWD/CCESingleCtrlDevice.cpp \
    $$PWD/CCESingleStatusDevice.cpp \
    $$PWD/CCEStatusWarnDevice.cpp \
    $$PWD/CCETestDataDevice.cpp \
    $$PWD/CCETestParamSetDevice.cpp



