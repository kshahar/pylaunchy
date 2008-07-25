 TEMPLATE      = lib
 CONFIG       += plugin debug_and_release
 FORMS		   = 
 HEADERS       = plugin_interface.h PyLaunchyPlugin.h
 SOURCES       = plugin_interface.cpp PyLaunchyPlugin.cpp 
 HEADERS      += ExportedCatItem.h ExportedInputData.h ScriptPlugin.h
 SOURCES      += ExportedCatItem.cpp ExportedInputData.cpp
 SOURCES      += python_export.cpp python_export_qstring.cpp python_export_catalog.cpp python_export_ScriptPlugin.cpp
 TARGET		   = PyLaunchy
 PRECOMPILED_HEADER = Precompiled.h
 
 INCLUDEPATH = $$(PYTHON_ROOT)\include $$(BOOST_1_35_0)
 
 win32 {
 	CONFIG -= embed_manifest_dll
	LIBS += shell32.lib
	LIBS += $$(PYTHONROOT)\libs\python25.lib
	LIBS += -L$$(BOOST_1_35_0)\lib
%	LIBS += user32.lib
%	LIBS += Gdi32.lib
%	LIBS += comctl32.lib
}

