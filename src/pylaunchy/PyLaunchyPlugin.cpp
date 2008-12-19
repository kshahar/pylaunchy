#include "Precompiled.h"
#include "PyLaunchyPlugin.h"

#include "PyLaunchyPluginDefines.h"
#include "PythonUtils.h"

#include "SimpleQSettings.h"
#include "ScriptsDirectoryConfig.h"

extern void init_pylaunchy();

PyLaunchyPlugin* g_pyLaunchyInstance = NULL;

void PyLaunchyPlugin::registerPlugin(boost::python::object pluginClass)
{
	m_scriptPluginsManager.registerPlugin(pluginClass);
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

	initPython();
	handleVersion();
	m_scriptPluginsManager.loadScriptFiles(m_scriptsDir);
	m_scriptPluginsManager.loadPlugins();
}

QString PyLaunchyPlugin::getIcon()
{
	return QString::null;
}

void PyLaunchyPlugin::loadPlugins(QList<PluginInfo>* additionalPlugins)
{
	LOG_FUNCTRACK;

	LOG_INFO("Adding Python plugins to Launchy");
	const PluginInfoHash& scriptPluginsInfo = 
		m_scriptPluginsManager.scriptPluginsInfo();
	PluginInfoHash::const_iterator it = scriptPluginsInfo.constBegin();
	PluginInfoHash::const_iterator ite = scriptPluginsInfo.constEnd();
	for ( ; it != ite; ++it ) {
		additionalPlugins->push_back(it.value());
	}
}

void PyLaunchyPlugin::unloadPlugin(uint id)
{
	m_scriptPluginsManager.unloadPlugin(id);
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
			handled = true;
			break;
		case MSG_GET_CATALOG:
			handled = true;
			break;
		case MSG_LAUNCH_ITEM:
			handled = true;
			break;
		case MSG_HAS_DIALOG:
			// Set to true if you provide a gui
			handled = false;
			break;
		case MSG_DO_DIALOG:
			break;
		case MSG_END_DIALOG:
			break;
		case MSG_LAUNCHY_SHOW:
			handled = true;
			break;
		case MSG_LAUNCHY_HIDE:
			handled = true;
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

void PyLaunchyPlugin::initPython()
{
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

	SimpleQSettings simpleSettings(**settings);
	ScriptsDirectoryConfig scriptsDirectoryConfig;
	scriptsDirectoryConfig.init(simpleSettings);

	m_scriptsDir = scriptsDirectoryConfig.scriptsDirectory();

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
			PyObject* settingsPyObject = 
				PyLong_FromVoidPtr ((void *) *settings);
			launchyNamespace["__settings"] = 
				boost::python::handle<>(settingsPyObject);
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
}

void PyLaunchyPlugin::handleVersion()
{
	QFile file(":/Version.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		LOG_WARN("Failed to open :/Version.txt file");
		return;
	}

	QTextStream in(&file);
	const QString realVersion = in.readLine();
	LOG_INFO( "Version is %s", (const char*)realVersion.toUtf8() );

	QSettings* set = *settings;
	const QString configVersion = 
		set->value("pylaunchy/version", "0.0").toString();

	if (configVersion == "0.0") {
		QMessageBox::information(0, "PyLaunchy",
			QString("PyLaunchy %1 was installed successfully")
				.arg(realVersion)
		);
	}
	else if (realVersion != configVersion) {
		QMessageBox::information(0, "PyLaunchy",
			QString("PyLaunchy was upgraded successfully from version %1 to %2")
				.arg(configVersion).arg(realVersion)
		);
	}
	else {
		// Version is the same, do nothing
	}

	set->setValue("pylaunchy/version", realVersion);
}

Q_EXPORT_PLUGIN2(PyLaunchy, PyLaunchyPlugin) 
