 # Check for requried environment variables
 !exists($$(PYTHON_INCLUDE_DIR)) {
     error("The PYTHON_INCLUDE_DIR environment variable is not defined.")
 }
 !exists($$(PYTHON_LIB_FILE)) {
    error("The PYTHON_LIB_FILE environment variable is not defined.")
 } 
 !exists($$(BOOST_ROOT)) {
    error("The BOOST_ROOT environment variable is not defined.")
 } 
 
 HEADERS       = catalog.h plugin_interface.h
 SOURCES       = catalog.cpp plugin_interface.cpp 
 
 HEADERS      += PyLaunchyPlugin.h NullScriptPlugin.h
 SOURCES      += PyLaunchyPlugin.cpp NullScriptPlugin.cpp
 
 HEADERS      += ScriptPlugin.h ScriptPluginWrapper.h
 SOURCES      += ScriptPluginWrapper.cpp
 
 HEADERS      += ScriptsDirectoryConfig.h
 SOURCES      += ScriptsDirectoryConfig.cpp
 
 SOURCES      += python_export.cpp python_export_pylaunchy.cpp python_export_qstring.cpp python_export_catalog.cpp python_export_ScriptPlugin.cpp
 
 HEADRES      += Precompiled.h
 SOURCES      += Precompiled.cpp
 
 PRECOMPILED_HEADER = Precompiled.h
  
 INCLUDEPATH = ezlogger $$(PYTHON_INCLUDE_DIR) $$(BOOST_ROOT)
 
 win32 {
	DEFINES = _CRT_SECURE_NO_DEPRECATE
	LIBS += shell32.lib
	LIBS += $$(PYTHON_LIB_FILE)
	LIBS += -L$$(BOOST_ROOT)\lib
 }