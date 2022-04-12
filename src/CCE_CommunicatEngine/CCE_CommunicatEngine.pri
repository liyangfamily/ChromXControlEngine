QT += core network serialport
CONFIG += c++11 qt

DEFINES += CCE_COMMUNICATENGINE_LIB

HEADERS += \
    $$PWD/../../include/CCE_CommunicatEngine/CCEMainCtrlPackage.h \
    ../../include/CCE_CommunicatEngine/CCECommunicatEngineDef.h \
    ../../include/CCE_CommunicatEngine/CCECommunicatEngineGlobal.h \
    ../../include/CCE_CommunicatEngine/CCEInteCtrlPackageStruct.h \
    ../../include/CCE_CommunicatEngine/CCEPackage.h \
    ../../include/CCE_CommunicatEngine/CCEPackageManager.h \

SOURCES += \
    $$PWD/Protocol/MainCtrl/CCEMainCtrlPackage.cpp \
    Protocol/CCEPackage.cpp \
    Protocol/CCEPackageManager.cpp \
