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
#include "ScriptPluginsManager.h"
#include "PythonUtils.h"

using namespace boost::python;

extern void init_pylaunchy();

PyLaunchyPlugin* gmypluginInstance = NULL;

PyLaunchyPlugin::PyLaunchyPlugin()
: m_pluginsManager( ScriptPluginsManager::instance() ), 
  m_launchingItem(false)
{
}

PyLaunchyPlugin::~PyLaunchyPlugin()
{
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

	LOG_STATUS("Starting PyLaunchy");

	Py_Initialize();
	if (PyUnicode_SetDefaultEncoding("utf-8"))
	{
		LOG_FATAL("Failed to set default encoding to utf-8.\n");
		PyErr_Clear();
		return;
	}

	// TODO: check if exists
	QDir::setCurrent("plugins/python/");

	/*
	LOG_DEBUG("Opening init script");
	QFile initScript(":/pylaunchy.py");

	const QString tempFileName = 
		QDir::tempPath() + QDir::separator() + "pylaunchy.py";
	LOG_DEBUG("Trying to copy init script to path %s", (const char*)tempFileName.toUtf8());

	if (QFile::exists(tempFileName)) {
		LOG_DEBUG("Trying to remove %s", (const char*)tempFileName.toUtf8());
		const bool removeSuccess = QFile::remove(tempFileName);
		if (!removeSuccess) {
			LOG_ERROR("Cannot remove %s", (const char*)tempFileName.toUtf8());
		}
	}
	const bool copySuccess = initScript.copy(tempFileName);
	if (!copySuccess) {
		LOG_ERROR("Cannot copy pylaunchy.py file to temp directory");
	}*/

	LOG_DEBUG("Copying init script to temporary file");
	QTemporaryFile* initScript =
		QTemporaryFile::createLocalFile( ":/pylaunchy.py" );

	QString initScriptFileName = initScript->fileName();
	LOG_DEBUG("Init script file name is %s", initScriptFileName.toUtf8());

	GUARDED_CALL_TO_PYTHON
	(
		LOG_INFO("Importing __main__ and __dict__");
		m_mainModule = boost::python::import("__main__");
		boost::python::object main_namespace = m_mainModule.attr("__dict__");

		LOG_INFO("Initializing pylaunchy module");
		init_pylaunchy();
	
		LOG_INFO("Executing init script file");
		boost::python::object ignored = boost::python::exec_file(
			(const char*)initScriptFileName.toUtf8(), main_namespace, main_namespace);
		LOG_DEBUG("Finished executing init script");

		QDir scriptsDir(".");
		scriptsDir.setNameFilters(QStringList("*.py"));
		scriptsDir.setFilter(QDir::Files);
		
		LOG_INFO("Executing all *.py files in plugins/python directory");
		foreach (QString pyFile, scriptsDir.entryList()) {
			LOG_INFO("Found %s, executing it", (const char*) pyFile.toUtf8());
			boost::python::str pyFileName((const char*) pyFile.toUtf8());
			boost::python::exec_file(pyFileName, 
				main_namespace, main_namespace);
		}	
		LOG_INFO("Finished executing *.py files");
	);
}


void PyLaunchyPlugin::getLabels(QList<InputData>* id)
{
	LOG_FUNCTRACK;

	ScriptInputDataList inputDataList(prepareInputDataList(id));

	foreach (ScriptPluginInfo pluginInfo, m_pluginsManager.plugins())
	{
		m_pluginsManager.setCurrentPlugin(pluginInfo.plugin);
		GUARDED_CALL_TO_PYTHON(
			LOG_DEBUG("Calling plugin getLabels");
			pluginInfo.plugin->getLabels(inputDataList);
		);
	}
	m_pluginsManager.resetCurrentPlugin();
}

void PyLaunchyPlugin::getResults(QList<InputData>* id, QList<CatItem>* results)
{
	LOG_FUNCTRACK;

	ScriptInputDataList inputDataList(prepareInputDataList(id));
	ScriptResultsList scriptResults(*results);

	foreach (ScriptPluginInfo pluginInfo, m_pluginsManager.plugins())
	{
		m_pluginsManager.setCurrentPlugin(pluginInfo.plugin);
		GUARDED_CALL_TO_PYTHON(
			LOG_DEBUG("Calling plugin getResults");
			pluginInfo.plugin->getResults(inputDataList, scriptResults);
		);
	}
	m_pluginsManager.resetCurrentPlugin();
}



QString PyLaunchyPlugin::getIcon()
{
#ifdef Q_WS_WIN
	return qApp->applicationDirPath() + "/plugins/icons/python.ico";
#endif
}

void PyLaunchyPlugin::getCatalog(QList<CatItem>* items)
{
	LOG_FUNCTRACK;

	ScriptResultsList scriptResults(*items);

	foreach (ScriptPluginInfo pluginInfo, m_pluginsManager.plugins())
	{
		m_pluginsManager.setCurrentPlugin(pluginInfo.plugin);
		GUARDED_CALL_TO_PYTHON(
			LOG_DEBUG("Calling plugin getCatalog");
			pluginInfo.plugin->getCatalog(scriptResults);
		);
	}
	m_pluginsManager.resetCurrentPlugin();
}

void PyLaunchyPlugin::launchItem(QList<InputData>* id, CatItem* item)
{
	LOG_FUNCTRACK;
	
	CatItem& topResult = id->last().getTopResult();
	item = &topResult;

	if (item->data == NULL) {
		LOG_WARN("Item has no plugin info");
		return;
	}

	if (reinterpret_cast<unsigned int>(item->data) == 0x2) {
		LOG_WARN("item->data == 0x2");
		return;
	}

	ScriptInputDataList inputDataList(prepareInputDataList(id));
	ScriptPlugin* plugin = reinterpret_cast<ScriptPlugin*>(item->data);

	LOG_DEBUG("Begining to launch item");
	m_launchingItem = true;

	if (plugin) {
		GUARDED_CALL_TO_PYTHON(
			LOG_DEBUG("Calling plugin launchItem");
			plugin->launchItem(inputDataList, *item);
		);
	}
	else {
		LOG_WARN("Cannot access plugin");
	}

	LOG_DEBUG("Finished launching item");
	m_launchingItem = false;
}

void PyLaunchyPlugin::doDialog(QWidget* parent, QWidget** newDlg) 
{
}

void PyLaunchyPlugin::endDialog(bool accept) 
{
}

void PyLaunchyPlugin::launchyShow() 
{
	LOG_FUNCTRACK;

	foreach (ScriptPluginInfo pluginInfo, m_pluginsManager.plugins())
	{
		m_pluginsManager.setCurrentPlugin(pluginInfo.plugin);
		GUARDED_CALL_TO_PYTHON(
			LOG_DEBUG("Calling plugin launchyShow");
			pluginInfo.plugin->launchyShow();
		);
	}
	m_pluginsManager.resetCurrentPlugin();
}

void PyLaunchyPlugin::launchyHide() 
{
	// pygo-y would crash in launchItem() if this test was not here.
	// TODO: find a better way to fix the crash.
	if (m_launchingItem) {
		return;
	}

	LOG_FUNCTRACK;

	foreach (ScriptPluginInfo pluginInfo, m_pluginsManager.plugins())
	{
		m_pluginsManager.setCurrentPlugin(pluginInfo.plugin);
		GUARDED_CALL_TO_PYTHON(
			LOG_DEBUG("Calling plugin launchyHide");
			pluginInfo.plugin->launchyHide();
		);
	}
	m_pluginsManager.resetCurrentPlugin();
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

		default:
			break;
	}
		
	return handled;
}

ScriptInputDataList PyLaunchyPlugin::prepareInputDataList(QList<InputData>* id)
{
	ScriptInputDataList inputDataList;
	QList<InputData>::iterator itr = id->begin();
	for ( ; itr != id->end(); ++itr) {
		inputDataList.push_back(&(*itr));
	}
	return inputDataList;
}

Q_EXPORT_PLUGIN2(PyLaunchy, PyLaunchyPlugin) 
