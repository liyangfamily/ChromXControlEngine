QT += core network serialport
CONFIG += c++11 qt

DEFINES += CCE_COMMUNICATENGINE_LIB

HEADERS += \
    ../../include/CCE_CommunicatEngine/CCECommunicatEngineDef.h \
    ../../include/CCE_CommunicatEngine/CCECommunicatEngineGlobal.h \
    ../../include/CCE_CommunicatEngine/CCEInteCtrlPackageStruct.h \
    ../../include/CCE_CommunicatEngine/CCEPackage.h \
    ../../include/CCE_CommunicatEngine/CCEPackageManager.h \

SOURCES += \
    Protocol/CCEPackage.cpp \
    Protocol/CCEPackageManager.cpp \
