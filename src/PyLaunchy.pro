 include("PyLaunchyCommon.pro")
 
 TEMPLATE      = lib
 CONFIG       += plugin release
 FORMS         = 
 VPATH         = pylaunchy/
 
 TARGET		   = PyLaunchy
 
 RESOURCES     = PyLaunchyPlugin.qrc
 
 win32 {
     CONFIG -= embed_manifest_dll
}

