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

#include "ScriptPlugin.h"

using namespace boost::python;

extern void init_pylaunchy();

PyLaunchyPlugin* gmypluginInstance = NULL;

#define PLUGIN_DEBUG

#ifdef PLUGIN_DEBUG

struct PluginDebug {
	PluginDebug()
		: debugFile("PythonPluginDebug.txt"),
		  debugStream(&debugFile)
	{
		if (!debugFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
		}
	}

	QFile debugFile;
	QTextStream debugStream;
};
static PluginDebug g_pluginDebug;

#define LOG_DEBUG(logExpr) \
	do { \
		g_pluginDebug.debugStream << (logExpr) << "\n"; \
		g_pluginDebug.debugStream.flush(); \
		g_pluginDebug.debugStream.flush(); \
	} while(0);
#else
#define LOG_DEBUG(logExpr) \
	do {} while(0);
#endif

void PyLaunchyPlugin::getID(uint* id)
{
	*id = HASH_myplugin;
}

void PyLaunchyPlugin::getName(QString* str)
{
	*str = PLUGIN_NAME;
}

void PyLaunchyPlugin::init()
{
	LOG_DEBUG(__FUNCTION__);

	Py_Initialize();
	if (PyUnicode_SetDefaultEncoding("utf-8"))
	{
		LOG_DEBUG("Failed to set default encoding to utf-8.\n");
		PyErr_Clear();
	}

	try {
		LOG_DEBUG("Importing __main__ and __dict__");
		m_mainModule = boost::python::import("__main__");
		boost::python::object main_namespace = m_mainModule.attr("__dict__");

		LOG_DEBUG("Initializing pylaunchy exports");
		init_pylaunchy();

		LOG_DEBUG("Executing init.py file");
		boost::python::object ignored = boost::python::exec_file(
			"plugins/python/init.py", main_namespace, main_namespace);

		LOG_DEBUG("Retrieving getPlugin function");
		boost::python::object getPlugin = m_mainModule.attr("getPlugin");

		LOG_DEBUG("Retrieving plugin");		
		boost::python::object pluginObject = getPlugin();

		addPlugin(pluginObject);
	} 
	catch(boost::python::error_already_set const &) {
		LOG_DEBUG("Exception occured");
	}
}


void PyLaunchyPlugin::getLabels(QList<InputData>* id)
{
	LOG_DEBUG(__FUNCTION__);

	ScriptInputDataList inputDataList(prepareInputDataList(id));

	foreach (ScriptPluginInfo pluginInfo, m_scriptPlugins)
	{
		try {
			LOG_DEBUG("Calling plugin addLabels");
			pluginInfo.plugin->addLabels(inputDataList);
		}
		catch(boost::python::error_already_set const &) {
			LOG_DEBUG(QString("Exception occured with plugin ") + pluginInfo.name);
		}
	}
}

void PyLaunchyPlugin::getResults(QList<InputData>* id, QList<CatItem>* results)
{
	LOG_DEBUG(__FUNCTION__);

	ScriptInputDataList inputDataList(prepareInputDataList(id));
	ScriptResultsList scriptResults(*results);

	foreach (ScriptPluginInfo pluginInfo, m_scriptPlugins)
	{
		try {
			LOG_DEBUG("Calling plugin addResults");
			pluginInfo.plugin->addResults(inputDataList, scriptResults);
		}
		catch(boost::python::error_already_set const &) {
			LOG_DEBUG(QString("Exception occured with plugin ") + pluginInfo.name);
		}
	}

	/*try {
		
		if (plugin) {
			LOG_DEBUG("Calling plugin addResults");
			ScriptResultsList scriptResults(*results);
			plugin->addResults(inputDataList, scriptResults);
		}
	}
	catch(boost::python::error_already_set const &) {
		LOG_DEBUG("Exception occured");
		//PyErr_Print();
		//PyErr_Clear(); // <-- 
		//boost::python::exec("sys.stderr.flush()");
	}*/
}



QString PyLaunchyPlugin::getIcon()
{
#ifdef Q_WS_WIN
	return qApp->applicationDirPath() + "/plugins/icons/python.ico";
#endif
}

void PyLaunchyPlugin::getCatalog(QList<CatItem>* items)
{
	LOG_DEBUG(__FUNCTION__);

	ScriptResultsList scriptResults(*items);

	foreach (ScriptPluginInfo pluginInfo, m_scriptPlugins)
	{
		try {
			LOG_DEBUG("Calling plugin getCatalog");
			pluginInfo.plugin->getCatalog(scriptResults);
		}
		catch(boost::python::error_already_set const &) {
			LOG_DEBUG(QString("Exception occured with plugin ") + pluginInfo.name);
		}
	}
}

void PyLaunchyPlugin::launchItem(QList<InputData>* id, CatItem* item)
{
	LOG_DEBUG(__FUNCTION__);

	ScriptInputDataList inputDataList(prepareInputDataList(id));

	foreach (ScriptPluginInfo pluginInfo, m_scriptPlugins)
	{
		try {
			LOG_DEBUG("Calling plugin launchItem");
			const CatItem& catItem = *item;
			pluginInfo.plugin->launchItem(inputDataList, boost::ref(catItem));
		}
		catch(boost::python::error_already_set const &) {
			LOG_DEBUG(QString("Exception occured with plugin ") + pluginInfo.name);
		}
	}
}

void PyLaunchyPlugin::doDialog(QWidget* parent, QWidget** newDlg) 
{
}

void PyLaunchyPlugin::endDialog(bool accept) 
{
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

		default:
			break;
	}
		
	return handled;
}

void PyLaunchyPlugin::addPlugin(boost::python::object pluginObject)
{
	LOG_DEBUG("Extracting plugin");
	ScriptPlugin* plugin = extract<ScriptPlugin*>(pluginObject);

	if (plugin) {
		LOG_DEBUG("Initializing plugin");
		plugin->init();

		LOG_DEBUG("Getting plugin name");
		QString pluginName = plugin->getName();

		LOG_DEBUG("Adding plugin to list");
		m_scriptPlugins.push_back( ScriptPluginInfo(plugin, pluginName) );
	}
}

ScriptInputDataList PyLaunchyPlugin::prepareInputDataList(QList<InputData>* id)
{
	ScriptInputDataList inputDataList;
	QList<InputData>::iterator itr = id->begin();
	for ( ; itr != id->end(); ++itr) {
		inputDataList.push_back(ExportedInputData(*itr));
	}
	return inputDataList;
}

Q_EXPORT_PLUGIN2(PyLaunchy, PyLaunchyPlugin) 
