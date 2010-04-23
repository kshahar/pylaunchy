CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

INCLUDE(${QT_USE_FILE}) 

INCLUDE_DIRECTORIES("../ezlogger") 
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_LIBRARIES(${PYTHON_LIBRARIES})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

INCLUDE_DIRECTORIES(".")

SET( PyLaunchy_SRCS 
	launchy/catalog.cpp
	launchy/plugin_interface.cpp 
	PyLaunchyPlugin.cpp
	ScriptPluginWrapper.cpp
	PythonInitializer.cpp
	ScriptsDirectoryConfig.cpp ScriptPluginsManager.cpp 
	GlobalPythonModuleData.cpp
	ScriptPluginsSynchronizer.cpp
	qt_utils/QSettingsWrapper.cpp
	qt_utils/QTemporaryFileWrapper.cpp
	python_export/python_export.cpp 
	python_export/python_export_pylaunchy.cpp 
	python_export/python_export_qstring.cpp 
	python_export/python_export_catalog.cpp 
	python_export/python_export_ScriptPlugin.cpp
)

SET( PyLaunchy_HDRS 
	launchy/catalog.h 
	launchy/plugin_interface.h
	launchy/plugin_info.h 
	pylaunchy_ezlogger_adapter.h
	PyLaunchyPlugin.h 
	ScriptPlugin.h ScriptPluginWrapper.h ScriptDataStructures.h
	PythonInitializer.h
	ScriptsDirectoryConfig.h ScriptPluginsManager.h
	PythonUtils.h 
	GlobalPythonModuleData.h
	ScriptPluginsSynchronizer.h
	qt_utils/QSettingsWrapper.h
	qt_utils/QTemporaryFileWrapper.h
	python_export/python_export.h 
	python_export/python_export_pylaunchy.h
	python_export/python_export_qstring.h 
	python_export/python_export_catalog.h 
	python_export/python_export_ScriptPlugin.h
)

# Generate with moc .cxx files our .h files
# TODO: Add Precompiled.h switch on MSVC
QT4_WRAP_CPP( PyLaunchy_MOC_SRCS
	PyLaunchyPlugin.h
	ScriptPluginWrapper.h
)

# Generate with rcc .cxx files for our .qrc files
QT4_ADD_RESOURCES( PyLaunchy_RCC_SRCS
	PyLaunchyPlugin.qrc
)

IF (MSVC)
	# Add Precompiled headers for source files
	MSVC_ADD_PRECOMPILED_HEADER( Precompiled.h Precompiled.cpp ${PyLaunchy_SRCS} )
	
	# Precompiled.cpp should be compiled too
	list(APPEND PyLaunchy_SRCS Precompiled.cpp)
ENDIF(MSVC)

# Add the rest of the files to sources list
list(APPEND PyLaunchy_SRCS ${PyLaunchy_HDRS})
list(APPEND PyLaunchy_SRCS ${PyLaunchy_MOC_SRCS})
list(APPEND PyLaunchy_SRCS ${PyLaunchy_RCC_SRCS})

# Add some definitions for QT
ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS(-DQT_PLUGIN)
ADD_DEFINITIONS(-DQT_NO_DEBUG)
ADD_DEFINITIONS(-DQT_SHARED)

IF( MSVC )
	ADD_DEFINITIONS(-DUNICODE)
	ADD_DEFINITIONS(-D_UNICODE)

	# Kill "deprecated" warnings
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_DEPRECATE=1)
	
	# Don't embed the manifest. This is the same as the qmake expression -
	#     CONFIG -= embed_manifest_dll
	# qmake manual says that embedding the manifest is bad for plug-ins
	SET(CMAKE_SHARED_LINKER_FLAGS "/MANIFEST:NO")
ENDIF( MSVC )

# Compile and link PyLaunchy shared library
ADD_LIBRARY( PyLaunchy SHARED ${PyLaunchy_SRCS})
TARGET_LINK_LIBRARIES(PyLaunchy ${QT_LIBRARIES})

IF(WANT_TEST)
	ADD_DEFINITIONS(-DPYLAUNCHY_TESTING)
	ADD_LIBRARY( PyLaunchyStaticLib STATIC ${PyLaunchy_SRCS} )
	TARGET_LINK_LIBRARIES(PyLaunchyStaticLib ${QT_LIBRARIES})
ENDIF(WANT_TEST)

# Install the DLL on Windows
IF (WIN32)
	INSTALL(SCRIPT ${CMAKE_MODULE_PATH}/LaunchyDown.cmake)
	INSTALL(TARGETS PyLaunchy  
		RUNTIME DESTINATION "C:\\Program Files\\Launchy\\plugins"
	)
ENDIF (WIN32)