#include "Precompiled.h"
#include "PyLaunchyPlugin.h"

#include <QtGui>
#include <QUrl>
#include <QFile>
#include <QRegExp>
#include <QTextCodec>

#ifdef Q_WS_WIN
#include <windows.h>
#include <shlobj.h>
#include <tchar.h>
#endif

#include "PyLaunchyPluginDefines.h"
#include "ScriptPlugin.h"
#include "PythonUtils.h"

#include "plugin_info.h"
#include "ScriptPluginWrapper.h"

using namespace boost::python;

extern void init_pylaunchy();

PyLaunchyPlugin* g_pyLaunchyInstance = NULL;

void PyLaunchyPlugin::registerPlugin(ScriptPlugin* scriptPlugin)
{
	LOG_DEBUG("Adding script plugin");
	ScriptPluginWrapper* pluginWrapper = new ScriptPluginWrapper(scriptPlugin);
	m_scriptPlugins.push_back( pluginWrapper );
}

PyLaunchyPlugin::PyLaunchyPlugin()
{
}

PyLaunchyPlugin::~PyLaunchyPlugin()
{
	LOG_DEBUG("Shutting down PyLaunchy");
	while (!m_scriptPlugins.isEmpty()) {
		delete m_scriptPlugins.takeFirst();
	}
}

void PyLaunchyPlugin::getID(uint* id)
{
	*id = pylaunchy::pluginHash;
}

void PyLaunchyPlugin::getName(QString* str)
{
	*str = pylaunchy::pluginName;
}

void PyLaunchyPlugin::init()
{
	LOG_FUNCTRACK;

	if (g_pyLaunchyInstance) {
		return;
	}

	LOG_STATUS("Starting PyLaunchy");
	g_pyLaunchyInstance = this;

	Py_Initialize();
	if (PyUnicode_SetDefaultEncoding("utf-8"))
	{
		LOG_FATAL("Failed to set default encoding to utf-8.\n");
		PyErr_Clear();
		return;
	}

	QDir scriptsDir = getScriptsDir();

	LOG_DEBUG("Copying init script to temporary file");
	QTemporaryFile* initScript =
		QTemporaryFile::createLocalFile( ":/pylaunchy.py" );

	QString initScriptFileName = initScript->fileName();

	GUARDED_CALL_TO_PYTHON
	(
		LOG_INFO("Importing __main__ and __dict__");
		boost::python::object mainModule = boost::python::import("__main__");
		boost::python::object mainNamespace = mainModule.attr("__dict__");

		LOG_INFO("Initializing pylaunchy module");
		init_pylaunchy();
	
		LOG_INFO("Executing init script file");
		LOG_DEBUG("Init script file name is %s", (const char*)initScriptFileName.toUtf8());
		boost::python::exec_file(
			(const char*)initScriptFileName.toUtf8(), mainNamespace, mainNamespace);
		initScript->remove();
		LOG_INFO("Finished executing init script");

		scriptsDir.setNameFilters(QStringList("*.py"));
		scriptsDir.setFilter(QDir::Files);
		
		LOG_INFO("Executing all *.py files in scripts directory");
		foreach (QString pyFile, scriptsDir.entryList()) {
			LOG_INFO("Found %s, executing it", (const char*) pyFile.toUtf8());
			boost::python::str pyFileName((const char*) 
				scriptsDir.absoluteFilePath(pyFile).toUtf8());
			boost::python::exec_file(pyFileName, 
				mainNamespace, mainNamespace);
		}	
		LOG_INFO("Finished executing *.py files");
	);
}


void PyLaunchyPlugin::getLabels(QList<InputData>* id)
{
}

void PyLaunchyPlugin::getResults(QList<InputData>* id, QList<CatItem>* results)
{
}

QString PyLaunchyPlugin::getIcon()
{
#ifdef Q_WS_WIN
	return qApp->applicationDirPath() + "/plugins/icons/python.ico";
#endif
}

void PyLaunchyPlugin::getCatalog(QList<CatItem>* items)
{
}

void PyLaunchyPlugin::launchItem(QList<InputData>* id, CatItem* item)
{
}

void PyLaunchyPlugin::doDialog(QWidget* parent, QWidget** newDlg) 
{
}

void PyLaunchyPlugin::endDialog(bool accept) 
{
}

void PyLaunchyPlugin::launchyShow() 
{
}

void PyLaunchyPlugin::launchyHide() 
{
}

void PyLaunchyPlugin::getPlugins(QList<PluginInfo>* additionalPlugins)
{
	LOG_FUNCTRACK;
	foreach (ScriptPluginWrapper* pluginWrapper, m_scriptPlugins)
	{
		PluginInfo launchyPluginInfo;
		pluginWrapper->getID(&launchyPluginInfo.id);
		pluginWrapper->getName(&launchyPluginInfo.name);
		launchyPluginInfo.path = "";
		launchyPluginInfo.obj = pluginWrapper;

		additionalPlugins->push_back(launchyPluginInfo);
	}	
}

int PyLaunchyPlugin::msg(int msgId, void* wParam, void* lParam)
{
	bool handled = false;
	switch (msgId)
	{		
		case MSG_INIT:
			init();
			handled = true;
			break;
		case MSG_GET_LABELS:
			getLabels((QList<InputData>*) wParam);
			handled = true;
			break;
		case MSG_GET_ID:
			getID((uint*) wParam);
			handled = true;
			break;
		case MSG_GET_NAME:
			getName((QString*) wParam);
			handled = true;
			break;
		case MSG_GET_RESULTS:
			getResults((QList<InputData>*) wParam, (QList<CatItem>*) lParam);
			handled = true;
			break;
		case MSG_GET_CATALOG:
			getCatalog((QList<CatItem>*) wParam);
			handled = true;
			break;
		case MSG_LAUNCH_ITEM:
			launchItem((QList<InputData>*) wParam, (CatItem*) lParam);
			handled = true;
			break;
		case MSG_HAS_DIALOG:
			// Set to true if you provide a gui
			handled = true;
			break;
		case MSG_DO_DIALOG:
			// This isn't called unless you return true to MSG_HAS_DIALOG
			doDialog((QWidget*) wParam, (QWidget**) lParam);
			break;
		case MSG_END_DIALOG:
			// This isn't called unless you return true to MSG_HAS_DIALOG
			endDialog((bool) wParam);
			break;
		case MSG_LAUNCHY_SHOW:
			handled = true;
			launchyShow();
			break;
		case MSG_LAUNCHY_HIDE:
			handled = true;
			launchyHide();
			break;

		case MSG_GET_PLUGINS:
			handled = true;
			getPlugins((QList<PluginInfo>*)wParam);
			break;

		default:
			break;
	}
		
	return handled;
}

QDir PyLaunchyPlugin::getScriptsDir()
{
	QSettings* set = *settings;

	LOG_DEBUG("Reading scripts dir location from settings");
	const QString scriptsDirKey = "pylaunchy/scriptsDir";
	QString scriptsDirPath;
	if (set->contains(scriptsDirKey)) {
		scriptsDirPath = set->value(scriptsDirKey).toString();
	}
	else {
		scriptsDirPath = "plugins/python/";
		set->setValue(scriptsDirKey, scriptsDirPath);
	}
	LOG_INFO("Using scripts dir %s", (const char*)scriptsDirPath.toUtf8());
	QDir scriptsDir(scriptsDirPath);
	if ( !scriptsDir.exists() ) {
		scriptsDir.mkdir(scriptsDirPath);
	}

	return scriptsDir;
}

Q_EXPORT_PLUGIN2(PyLaunchy, PyLaunchyPlugin) 
