 include("PyLaunchyCommon.pro")
 
 TEMPLATE      = app
 CONFIG       += qtestlib release
 FORMS         = 
 VPATH         = pylaunchy/
 VPATH        += pylaunchy_unit_test/
  
 TARGET        = PyLaunchy
 
 SOURCES      += main.cpp
 SOURCES      += ScriptsDirectoryConfigTest.cpp
 
 RESOURCES     = PyLaunchyPlugin.qrc
 
 INCLUDEPATH  += pylaunchy $$(GTEST_INCLUDE_DIR)
 
 win32 {
     CONFIG += embed_manifest_exe
     LIBS += qtmaind.lib
     LIBS += $$(GTEST_LIB_FILE)
}

