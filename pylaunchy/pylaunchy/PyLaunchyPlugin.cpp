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

void PyLaunchyPlugin::registerPlugin(boost::python::object pluginClass)
{
	GUARDED_CALL_TO_PYTHON
	(
		LOG_DEBUG("Registering plugin");
		m_scriptPluginsClasses.push_back(pluginClass);
	);
}

const QDir& PyLaunchyPlugin::scriptsDir() const
{
	return m_scriptsDir;
}

PyLaunchyPlugin::PyLaunchyPlugin()
{
}

PyLaunchyPlugin::~PyLaunchyPlugin()
{
	LOG_DEBUG("Shutting down PyLaunchy");
	destroyPlugins();
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

	LOG_DEBUG("Copying init script to temporary file");
	QTemporaryFile* initScript =
		QTemporaryFile::createLocalFile( ":/pylaunchy.py" );

	QString initScriptFileName = initScript->fileName();

	m_scriptsDir = determineScriptsDir();

	GUARDED_CALL_TO_PYTHON
	(
		LOG_DEBUG("Importing __main__ and __dict__");
		boost::python::object mainModule = boost::python::import("__main__");
		boost::python::object mainNamespace = mainModule.attr("__dict__");

		LOG_INFO("Initializing launchy module");
		init_pylaunchy();

		LOG_DEBUG("Importing launchy");
		boost::python::object launchyModule = boost::python::import("launchy");
		boost::python::object launchyNamespace = launchyModule.attr("__dict__");

		LOG_DEBUG("Setting launchy.__settings object");
		if (settings && *settings) {
			PyObject* settingsPyObject = PyLong_FromVoidPtr ((void *) *settings);
			launchyNamespace["__settings"] = handle<>(settingsPyObject);
		}
		else {
			LOG_WARN("Launchy's QSettings object was not found");
		}

		LOG_INFO("Executing init script file");
		LOG_DEBUG("Init script file name is %s", (const char*)initScriptFileName.toUtf8());
		boost::python::exec_file(
			(const char*)initScriptFileName.toUtf8(), mainNamespace, mainNamespace);
		initScript->remove();
		LOG_INFO("Finished executing init script");
	);

	reloadScriptFiles();
	reloadPlugins();
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

void PyLaunchyPlugin::loadPlugins(QList<PluginInfo>* additionalPlugins)
{
	LOG_FUNCTRACK;

	LOG_INFO("Adding Python plugins to Launchy");
	PluginInfoHash::const_iterator itr = m_scriptPlugins.constBegin();
	for ( ; itr != m_scriptPlugins.constEnd(); ++itr ) {
		additionalPlugins->push_back(itr.value());
	}
}

void PyLaunchyPlugin::unloadPlugin(uint id)
{
	LOG_INFO("Unloading plugin with ID %i", id);
	PluginInfoHash::const_iterator itr = m_scriptPlugins.find(id);
	for ( ; itr != m_scriptPlugins.end() && itr.key() == id; ++itr ) {
		delete itr.value().obj;
	}
	m_scriptPlugins.remove(id);

	m_scriptPluginsObjects.remove(id);
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

		case MSG_LOAD_PLUGINS:
			handled = true;
			loadPlugins((QList<PluginInfo>*)wParam);
			break;

		case MSG_UNLOAD_PLUGIN:
			handled = true;
			unloadPlugin((uint)wParam);
			break;

		default:
			break;
	}
		
	return handled;
}

const PluginInfo& PyLaunchyPlugin::addPlugin(ScriptPlugin* scriptPlugin)
{
	LOG_DEBUG("Adding script plugin");
	ScriptPluginWrapper* pluginWrapper = new ScriptPluginWrapper(scriptPlugin);

	PluginInfo launchyPluginInfo;
	pluginWrapper->getID(&launchyPluginInfo.id);
	pluginWrapper->getName(&launchyPluginInfo.name);
	launchyPluginInfo.path = "";
	launchyPluginInfo.obj = pluginWrapper;

	m_scriptPlugins[launchyPluginInfo.id] = launchyPluginInfo;

	PluginInfoHash::iterator itemItr =
		m_scriptPlugins.insert(launchyPluginInfo.id, launchyPluginInfo);

	return itemItr.value();
}

void PyLaunchyPlugin::reloadPlugins()
{
	LOG_INFO("Reloading script plugins");
	foreach (boost::python::object pluginClass, m_scriptPluginsClasses) {
		GUARDED_CALL_TO_PYTHON
		(
			LOG_DEBUG("Creating plugin object");
			object pluginObject = pluginClass();

			LOG_DEBUG("Extracting plugin");
			ScriptPlugin* plugin = extract<ScriptPlugin*>(pluginObject);

			const PluginInfo& pluginInfo = addPlugin(plugin);
			m_scriptPluginsObjects.insert(pluginInfo.id, pluginObject);
		);
	}
}

void PyLaunchyPlugin::destroyPlugins()
{
	LOG_INFO("Destroying script plugins");
	PluginInfoHash::const_iterator itr = m_scriptPlugins.constBegin();
	for ( ; itr != m_scriptPlugins.constEnd(); ++itr ) {
		delete itr.value().obj;
	}
	m_scriptPlugins.clear();

	m_scriptPluginsObjects.clear();
}

void PyLaunchyPlugin::reloadScriptFiles()
{
	LOG_INFO("Reloading script files");
	QDir scriptsDir = m_scriptsDir;

	GUARDED_CALL_TO_PYTHON
	(
		LOG_DEBUG("Importing __main__ and __dict__");
		boost::python::object mainModule = boost::python::import("__main__");
		boost::python::object mainNamespace = mainModule.attr("__dict__");

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

QDir PyLaunchyPlugin::determineScriptsDir()
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
