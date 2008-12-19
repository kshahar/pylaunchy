 include("PyLaunchyCommon.pro")
 
 TEMPLATE      = app
 CONFIG       += release warn_on plugin
 FORMS         = 
 VPATH         = pylaunchy/
 VPATH        += pylaunchy_unit_test/
  
 TARGET        = PyLaunchy
 
 SOURCES      += main.cpp
 SOURCES      += ScriptsDirectoryConfigTest.cpp
 
 RESOURCES     = PyLaunchyPlugin.qrc
 
 INCLUDEPATH  += pylaunchy $$(GTEST_INCLUDE_DIR)
 
 DEFINES += PYLAUNCHY_TESTING
 
 win32 {
     CONFIG += embed_manifest_exe
     LIBS += qtmaind.lib
     LIBS += $$(GTEST_LIB_FILE)
}

