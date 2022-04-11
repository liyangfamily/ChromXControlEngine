!isEmpty(CCE_COMMON_INCLUDED):error("CCECommon.pri already included")
CCE_COMMON_INCLUDED = 1

# For Parent Project Config
# Parent Project Need Creat This Config In "3rdparty/ChromXControlEngine"
# In this Config , Need to specify the variable: $$PRO_BIN_PATH $$PRO_LIBRARY_PATH
exists(../../ChromXControlEngine_OutputPath.pri):include(../../ChromXControlEngine_OutputPath.pri)

include(ChromXControlEngine.prf)

isEmpty(PRO_ID){
   PRO_ID = ChromXControlEngine
}
isEmpty(PRO_TARGET){
   PRO_TARGET = $$PRO_ID
}


# For ChromXControlEngine Include Path
CHROMXCONTROLENGINE_INCLUDE= $$PWD/include
INCLUDEPATH += $$CHROMXCONTROLENGINE_INCLUDE

# Project Source Tree Path
isEmpty(PRO_SOURCE_TREE){
   PRO_SOURCE_TREE = $$PWD
}

# Project OutPut Tree Path
isEmpty(PRO_BUILD_TREE) {
    sub_dir = $$_PRO_FILE_PWD_
    sub_dir ~= s,^$$re_escape($$PWD),,
    PRO_BUILD_TREE = $$clean_path($$OUT_PWD)
    PRO_BUILD_TREE ~= s,$$re_escape($$sub_dir)$,,
}

# For ChromXControlEngine Build Path
osx{
   isEmpty(PRO_APP_BUNDLE){
      exists($$PRO_BUILD_TREE/Contents/MacOS/$$PRO_TARGET): PRO_APP_BUNDLE = $$PRO_BUILD_TREE
      else: PRO_APP_BUNDLE = $$PRO_BIN_PATH/$${PRO_TARGET}.app
   }
    # target output path if not set manually
    isEmpty(PRO_OUTPUT_PATH): PRO_OUTPUT_PATH = $$PRO_APP_BUNDLE/Contents

    isEmpty(PRO_LIBRARY_PATH): PRO_LIBRARY_PATH = $$PRO_OUTPUT_PATH/Frameworks
    isEmpty(PRO_LIBRARY_PATH):  PRO_BIN_PATH     = $$PRO_OUTPUT_PATH/MacOS


}else{
    # target output path if not set manually
    isEmpty(PRO_OUTPUT_PATH): PRO_OUTPUT_PATH = $$PRO_BUILD_TREE

    isEmpty(PRO_LIBRARY_PATH): PRO_LIBRARY_PATH = $$PRO_OUTPUT_PATH/lib
    isEmpty(PRO_BIN_PATH): PRO_BIN_PATH     = $$PRO_OUTPUT_PATH/bin

}


# For ChromXControlEngine Module Dependencies
exists($$PRO_LIBRARY_PATH): LIBS *= -L$$PRO_LIBRARY_PATH  # ChromXControlEngine library path from output path

# ChromXControlEngine library path
isEmpty(CCE_MODULE_DIRS){
    CCE_MODULE_DIRS += $$PWD/src
}

# recursively resolve ChromXControlEngine library deps
done_libs =
for(ever) {
    isEmpty(PRO_LIB_DEPENDS): \
        break()
    done_libs += $$PRO_LIB_DEPENDS
    for(dep, PRO_LIB_DEPENDS) {
        dependencies_file =
        for(dir, CCE_MODULE_DIRS) {
            exists($$dir/$$dep/$${dep}_dependencies.pri) {
                dependencies_file = $$dir/$$dep/$${dep}_dependencies.pri
                break()
            }
        }
        isEmpty(dependencies_file): \
            error("Library dependency $$dep not found")
        include($$dependencies_file)
        LIBS += -l$$qtLibraryTargetName($$PRO_LIB_NAME)
        osx:QMAKE_LFLAGS += -l$$qtLibraryTargetName($$PRO_LIB_NAME)
    }
    PRO_LIB_DEPENDS = $$unique(PRO_LIB_DEPENDS)
    PRO_LIB_DEPENDS -= $$unique(done_libs)
}
