 TEMPLATE      = lib
 CONFIG       += plugin debug_and_release
 FORMS		   = 
 
 HEADERS       = catalog.h plugin_interface.h
 SOURCES       = catalog.cpp plugin_interface.cpp 
 
 HEADERS      += PyLaunchyPlugin.h ScriptPluginsManager.h NullScriptPlugin.h
 SOURCES      += PyLaunchyPlugin.cpp ScriptPluginsManager.cpp NullScriptPlugin.cpp
 
 HEADERS      += ExportedInputData.h ScriptPlugin.h
 SOURCES      += ExportedInputData.cpp
 
 SOURCES      += python_export.cpp python_export_pylaunchy.cpp python_export_qstring.cpp python_export_catalog.cpp python_export_ScriptPlugin.cpp
 TARGET		   = PyLaunchy
 PRECOMPILED_HEADER = Precompiled.h
 
 RESOURCES     = PyLaunchyPlugin.qrc
 
 INCLUDEPATH = $$(PYTHON_ROOT)\include $$(BOOST_1_35_0) ezlogger
 
 win32 {
	DEFINES = _CRT_SECURE_NO_DEPRECATE
 	CONFIG -= embed_manifest_dll
	LIBS += shell32.lib
	LIBS += $$(PYTHONROOT)\libs\python25.lib
	LIBS += -L$$(BOOST_1_35_0)\lib
	RC_FILE = PyLaunchyPlugin.rc
%	LIBS += user32.lib
%	LIBS += Gdi32.lib
%	LIBS += comctl32.lib
}

