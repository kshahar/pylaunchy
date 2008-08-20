# Copyright (c) 2008 Riverbank Computing Limited <info@riverbankcomputing.com>
# 
# This file is part of PyQt.
# 
# This file may be used under the terms of the GNU General Public
# License versions 2.0 or 3.0 as published by the Free Software
# Foundation and appearing in the files LICENSE.GPL2 and LICENSE.GPL3
# included in the packaging of this file.  Alternatively you may (at
# your option) use any later version of the GNU General Public
# License if such license has been publicly approved by Riverbank
# Computing Limited (or its successors, if any) and the KDE Free Qt
# Foundation. In addition, as a special exception, Riverbank gives you
# certain additional rights. These rights are described in the Riverbank
# GPL Exception version 1.1, which can be found in the file
# GPL_EXCEPTION.txt in this package.
# 
# Please review the following information to ensure GNU General
# Public Licensing requirements will be met:
# http://trolltech.com/products/qt/licenses/licensing/opensource/. If
# you are unsure which license is appropriate for your use, please
# review the following information:
# http://trolltech.com/products/qt/licenses/licensing/licensingoverview
# or contact the sales department at sales@riverbankcomputing.com.
# 
# This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
# INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE. Trolltech reserves all rights not expressly
# granted herein.
# 
# This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
# WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#
# This module is intended to be used by the configuration scripts of extension
# modules that %Import PyQt4 modules.


import sipconfig


# These are installation specific values created when PyQt4 was configured.
_pkg_config = {
    'pyqt_bin_dir':      'C:\\Python25',
    'pyqt_config_args':  '',
    'pyqt_mod_dir':      'C:\\Python25\\Lib\\site-packages\\PyQt4',
    'pyqt_modules':      'QtCore QtGui QtHelp QtNetwork QtOpenGL QtScript QtSql QtSvg QtTest QtWebKit QtXml QtXmlPatterns QtAssistant QtDesigner',
    'pyqt_sip_dir':      'C:\\Python25\\sip\\PyQt4',
    'pyqt_sip_flags':    '-x VendorID -t WS_WIN -x PyQt_NoPrintRangeBug -t Qt_4_4_0 -g',
    'pyqt_version':      0x040402,
    'pyqt_version_str':  '4.4.2',
    'qt_data_dir':       'C:\\Qt\\4.4.0',
    'qt_dir':            'C:\\Qt\\4.4.0',
    'qt_edition':        'free',
    'qt_framework':      0,
    'qt_inc_dir':        'C:\\Qt\\4.4.0\\include',
    'qt_lib_dir':        'C:\\Qt\\4.4.0\\lib',
    'qt_threaded':       1,
    'qt_version':        0x040400,
    'qt_winconfig':      'shared'
}

_default_macros = {
    'AIX_SHLIB':                '',
    'AR':                       '',
    'CC':                       'gcc',
    'CFLAGS':                   '',
    'CFLAGS_CONSOLE':           '',
    'CFLAGS_DEBUG':             '-g',
    'CFLAGS_EXCEPTIONS_OFF':    '',
    'CFLAGS_EXCEPTIONS_ON':     '',
    'CFLAGS_MT':                '',
    'CFLAGS_MT_DBG':            '',
    'CFLAGS_MT_DLL':            '',
    'CFLAGS_MT_DLLDBG':         '',
    'CFLAGS_RELEASE':           '-O2',
    'CFLAGS_RTTI_OFF':          '',
    'CFLAGS_RTTI_ON':           '',
    'CFLAGS_SHLIB':             '',
    'CFLAGS_STL_OFF':           '',
    'CFLAGS_STL_ON':            '',
    'CFLAGS_THREAD':            '',
    'CFLAGS_WARN_OFF':          '-w',
    'CFLAGS_WARN_ON':           '-Wall',
    'CHK_DIR_EXISTS':           'if not exist',
    'CONFIG':                   'qt warn_on release link_prl copy_dir_files debug_and_release debug_and_release_target precompile_header',
    'COPY':                     'copy /y',
    'CXX':                      'g++',
    'CXXFLAGS':                 '',
    'CXXFLAGS_CONSOLE':         '',
    'CXXFLAGS_DEBUG':           '-g',
    'CXXFLAGS_EXCEPTIONS_OFF':  '-fno-exceptions',
    'CXXFLAGS_EXCEPTIONS_ON':   '-fexceptions -mthreads',
    'CXXFLAGS_MT':              '',
    'CXXFLAGS_MT_DBG':          '',
    'CXXFLAGS_MT_DLL':          '',
    'CXXFLAGS_MT_DLLDBG':       '',
    'CXXFLAGS_RELEASE':         '-O2',
    'CXXFLAGS_RTTI_OFF':        '-fno-rtti',
    'CXXFLAGS_RTTI_ON':         '-frtti',
    'CXXFLAGS_SHLIB':           '',
    'CXXFLAGS_STL_OFF':         '',
    'CXXFLAGS_STL_ON':          '',
    'CXXFLAGS_THREAD':          '',
    'CXXFLAGS_WARN_OFF':        '-w',
    'CXXFLAGS_WARN_ON':         '-Wall',
    'DEFINES':                  'UNICODE QT_LARGEFILE_SUPPORT',
    'DEL_FILE':                 'del',
    'EXTENSION_PLUGIN':         '',
    'EXTENSION_SHLIB':          '',
    'INCDIR':                   '',
    'INCDIR_OPENGL':            '',
    'INCDIR_QT':                'C:\\Qt\\4.4.0\\include',
    'INCDIR_X11':               '',
    'LFLAGS':                   '-enable-stdcall-fixup -Wl,-enable-auto-import -Wl,-enable-runtime-pseudo-reloc',
    'LFLAGS_CONSOLE':           '-Wl,-subsystem,console',
    'LFLAGS_CONSOLE_DLL':       '',
    'LFLAGS_DEBUG':             '',
    'LFLAGS_DLL':               '-shared',
    'LFLAGS_OPENGL':            '',
    'LFLAGS_PLUGIN':            '',
    'LFLAGS_RELEASE':           '-Wl,-s',
    'LFLAGS_SHLIB':             '',
    'LFLAGS_SONAME':            '',
    'LFLAGS_THREAD':            '',
    'LFLAGS_WINDOWS':           '-Wl,-subsystem,windows',
    'LFLAGS_WINDOWS_DLL':       '',
    'LIB':                      'ar -ru',
    'LIBDIR':                   '',
    'LIBDIR_OPENGL':            '',
    'LIBDIR_QT':                'C:\\Qt\\4.4.0\\lib',
    'LIBDIR_X11':               '',
    'LIBS':                     '',
    'LIBS_CONSOLE':             '',
    'LIBS_CORE':                '-lkernel32 -luser32 -lshell32 -luuid -lole32 -ladvapi32 -lws2_32',
    'LIBS_GUI':                 '-lgdi32 -lcomdlg32 -loleaut32 -limm32 -lwinmm -lwinspool -lws2_32 -lole32 -luuid -luser32 -ladvapi32',
    'LIBS_NETWORK':             '-lws2_32',
    'LIBS_OPENGL':              '-lopengl32 -lglu32 -lgdi32 -luser32',
    'LIBS_RT':                  '',
    'LIBS_RTMT':                '',
    'LIBS_THREAD':              '',
    'LIBS_WINDOWS':             '',
    'LIBS_X11':                 '',
    'LINK':                     'g++',
    'LINK_SHLIB':               '',
    'LINK_SHLIB_CMD':           '',
    'MAKEFILE_GENERATOR':       'MINGW',
    'MKDIR':                    'mkdir',
    'MOC':                      'C:\\Qt\\4.4.0\\bin\\moc.exe',
    'RANLIB':                   '',
    'RPATH':                    '',
    'STRIP':                    'strip'
}


class Configuration(sipconfig.Configuration):
    """The class that represents PyQt configuration values.
    """
    def __init__(self, sub_cfg=None):
        """Initialise an instance of the class.

        sub_cfg is the list of sub-class configurations.  It should be None
        when called normally.
        """
        if sub_cfg:
            cfg = sub_cfg
        else:
            cfg = []

        cfg.append(_pkg_config)

        sipconfig.Configuration.__init__(self, cfg)


class QtCoreModuleMakefile(sipconfig.SIPModuleMakefile):
    """The Makefile class for modules that %Import QtCore.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if not kw.has_key("qt"):
            kw["qt"] = ["QtCore"]

        sipconfig.SIPModuleMakefile.__init__(self, *args, **kw)


class QtGuiModuleMakefile(QtCoreModuleMakefile):
    """The Makefile class for modules that %Import QtGui.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if not kw.has_key("qt"):
            kw["qt"] = ["QtCore", "QtGui"]

        QtCoreModuleMakefile.__init__(self, *args, **kw)


class QtHelpModuleMakefile(QtGuiModuleMakefile):
    """The Makefile class for modules that %Import QtHelp.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if not kw.has_key("qt"):
            kw["qt"] = ["QtCore", "QtGui", "QtHelp"]

        QtGuiModuleMakefile.__init__(self, *args, **kw)


class QtNetworkModuleMakefile(QtCoreModuleMakefile):
    """The Makefile class for modules that %Import QtNetwork.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if not kw.has_key("qt"):
            kw["qt"] = ["QtCore", "QtNetwork"]

        QtCoreModuleMakefile.__init__(self, *args, **kw)


class QtAssistantModuleMakefile(QtNetworkModuleMakefile):
    """The Makefile class for modules that %Import QtAssistant.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if not kw.has_key("qt"):
            kw["qt"] = ["QtCore", "QtGui", "QtNetwork", "QtAssistant"]

        QtNetworkModuleMakefile.__init__(self, *args, **kw)


class QtOpenGLModuleMakefile(QtGuiModuleMakefile):
    """The Makefile class for modules that %Import QtOpenGL.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        kw["opengl"] = 1

        if not kw.has_key("qt"):
            kw["qt"] = ["QtCore", "QtGui", "QtOpenGL"]

        QtGuiModuleMakefile.__init__(self, *args, **kw)


class QtScriptModuleMakefile(QtCoreModuleMakefile):
    """The Makefile class for modules that %Import QtScript.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if not kw.has_key("qt"):
            kw["qt"] = ["QtCore", "QtScript"]

        QtCoreModuleMakefile.__init__(self, *args, **kw)


class QtSqlModuleMakefile(QtGuiModuleMakefile):
    """The Makefile class for modules that %Import QtSql.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if not kw.has_key("qt"):
            kw["qt"] = ["QtCore", "QtGui", "QtSql"]

        QtGuiModuleMakefile.__init__(self, *args, **kw)


class QtSvgModuleMakefile(QtGuiModuleMakefile):
    """The Makefile class for modules that %Import QtSvg.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if not kw.has_key("qt"):
            kw["qt"] = ["QtCore", "QtGui", "QtSvg"]

        QtGuiModuleMakefile.__init__(self, *args, **kw)


class QtTestModuleMakefile(QtGuiModuleMakefile):
    """The Makefile class for modules that %Import QtTest.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if not kw.has_key("qt"):
            kw["qt"] = ["QtCore", "QtGui", "QtTest"]

        QtGuiModuleMakefile.__init__(self, *args, **kw)


class QtWebKitModuleMakefile(QtNetworkModuleMakefile):
    """The Makefile class for modules that %Import QtWebKit.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if not kw.has_key("qt"):
            kw["qt"] = ["QtCore", "QtGui", "QtNetwork", "QtWebKit"]

        QtNetworkModuleMakefile.__init__(self, *args, **kw)


class QtXmlModuleMakefile(QtCoreModuleMakefile):
    """The Makefile class for modules that %Import QtXml.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if not kw.has_key("qt"):
            kw["qt"] = ["QtCore", "QtXml"]

        QtCoreModuleMakefile.__init__(self, *args, **kw)


class QtXmlPatternsModuleMakefile(QtCoreModuleMakefile):
    """The Makefile class for modules that %Import QtXmlPatterns.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if not kw.has_key("qt"):
            kw["qt"] = ["QtCore", "QtXmlPatterns"]

        QtCoreModuleMakefile.__init__(self, *args, **kw)


class phononModuleMakefile(QtGuiModuleMakefile):
    """The Makefile class for modules that %Import phonon.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if not kw.has_key("qt"):
            kw["qt"] = ["QtCore", "QtGui", "phonon"]

        QtGuiModuleMakefile.__init__(self, *args, **kw)


class QtDesignerModuleMakefile(QtGuiModuleMakefile):
    """The Makefile class for modules that %Import QtDesigner.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if not kw.has_key("qt"):
            kw["qt"] = ["QtCore", "QtGui", "QtDesigner"]

        QtGuiModuleMakefile.__init__(self, *args, **kw)


class QAxContainerModuleMakefile(QtGuiModuleMakefile):
    """The Makefile class for modules that %Import QAxContainer.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if not kw.has_key("qt"):
            kw["qt"] = ["QtCore", "QtGui", "QAxContainer"]

        QtGuiModuleMakefile.__init__(self, *args, **kw)
