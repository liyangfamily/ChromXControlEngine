# For LBusiness Module Load Dependencies
include($$replace(_PRO_FILE_PWD_, ([^/]+$), \\1/\\1_dependencies.pri))
TARGET = $$PRO_LIB_NAME

# For LBusiness Module Load Common Function, Path and Dependencies Resolver
include(../CCECommon.pri)

win32 {
    DLLDESTDIR = $$PRO_BIN_PATH
}

DESTDIR = $$PRO_LIBRARY_PATH
#message($$PRO_LIBRARY_PATH)

TARGET = $$qtLibraryTargetName($$TARGET)

TEMPLATE = lib
CONFIG += shared dll
