QT += core network serialport
CONFIG += c++11 qt

DEFINES += CCE_COMMUNICATENGINE_LIB

HEADERS += \
    $$PWD/../../include/CCE_CommunicatEngine/CCECluster.h \
    $$PWD/../../include/CCE_CommunicatEngine/CCEClusterProxy.h \
    $$PWD/../../include/CCE_CommunicatEngine/CCELEDPanelUnitPackage.h \
    $$PWD/../../include/CCE_CommunicatEngine/CCEMainCtrlPackage.h \
    $$PWD/../../include/CCE_CommunicatEngine/CCESingleCtrlPackage.h \    
	$$PWD/../../include/CCE_CommunicatEngine/CCEEnginePackage.h \
    $$PWD/../../include/CCE_CommunicatEngine/CCEPackageDispatcher.h \
    $$PWD/../../include/CCE_CommunicatEngine/CCEPackageEvent.h \
    $$PWD/../../include/CCE_CommunicatEngine/CCESocketLock.h \
    $$PWD/Cluster/CCE_TaskEngine_IntegratedCtrlTask.h \
    $$PWD/NetEngine/CCEEnginePackage_p.h \
    $$PWD/NetEngine/CCE_EnginePackage_p.h \
    $$PWD/NetEngine/CCE_NetEngine.h \
    $$PWD/NetEngine/CCE_NetEngine_COMTransThread.h \
    $$PWD/NetEngine/CCE_NetEngine_TransThread.h \
    $$PWD/NetEngine/CCE_NetEngine_UDPTransThread.h \
    $$PWD/TaskEngine/CCE_TaskEngine.h \
    $$PWD/TaskEngine/CCE_TaskEngine_TaskBase.h \
    $$PWD/TaskEngine/CCE_TaskEngine_WorkingThread.h \
    ../../include/CCE_CommunicatEngine/CCECommunicatEngineDef.h \
    ../../include/CCE_CommunicatEngine/CCECommunicatEngineGlobal.h \
    ../../include/CCE_CommunicatEngine/CCEInteCtrlPackageStruct.h \
    ../../include/CCE_CommunicatEngine/CCEPackage.h \
    ../../include/CCE_CommunicatEngine/CCEPackageManager.h \

SOURCES += \
    $$PWD/Cluster/CCECluster.cpp \
    $$PWD/Cluster/CCE_TaskEngine_IntegratedCtrlTask.cpp \
    $$PWD/NetEngine/CCEEnginePackage.cpp \
    $$PWD/NetEngine/CCE_NetEngine.cpp \
    $$PWD/NetEngine/CCE_NetEngine_COMTransThread.cpp \
    $$PWD/NetEngine/CCE_NetEngine_TransThread.cpp \
    $$PWD/NetEngine/CCE_NetEngine_UDPTransThread.cpp \
    $$PWD/Protocol/MainCtrl/CCEMainCtrlPackage.cpp \
    $$PWD/Protocol/SingleCtrl/CCESingleCtrlPackage.cpp \
    $$PWD/Protocol/LEDPanelUnit/CCELEDPanelUnitPackage.cpp \
    $$PWD/TaskEngine/CCE_TaskEngine.cpp \
    $$PWD/TaskEngine/CCE_TaskEngine_TaskBase.cpp \
    $$PWD/TaskEngine/CCE_TaskEngine_WorkingThread.cpp \
    $$PWD/Tools/CCEClusterProxy.cpp \
    $$PWD/Tools/CCEPackageDispatcher.cpp \
    $$PWD/Tools/CCEPackageEvent.cpp \
    $$PWD/Tools/CCESocketLock.cpp \
    Protocol/CCEPackage.cpp \
    Protocol/CCEPackageManager.cpp \
