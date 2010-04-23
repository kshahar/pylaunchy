#include "Precompiled.h"
#include "PyLaunchyPlugin.h"

#include "qt_utils/QSettingsWrapper.h"
#include "ScriptsDirectoryConfig.h"
#include "ScriptPluginsManager.h"
#include "PythonInitializer.h"
#include "GlobalPythonModuleData.h"

static PyLaunchyPlugin* g_pyLaunchyInstance = NULL;
static const char* CONFIG_pluginName = "PyLaunchy";
static unsigned int CONFIG_pluginHash = qHash(CONFIG_pluginName);

struct PyLaunchyPlugin::PrivateImpl 
{
	void init(QSettings* pSettings);
	void getID(uint*);
	void getName(QString*);
	QString getIcon();
	void loadPlugins(QList<PluginInfo>* additionalPlugins);
	void unloadPlugin(uint id);

	ScriptPluginsManager m_scriptPluginsManager;
};

PyLaunchyPlugin::PyLaunchyPlugin()
: m_pImpl(new PrivateImpl)
{
}

PyLaunchyPlugin::~PyLaunchyPlugin()
{
	LOG_DEBUG("Shutting down PyLaunchy");
}

void PyLaunchyPlugin::PrivateImpl::getID(uint* id)
{
	*id = CONFIG_pluginHash;
}

void PyLaunchyPlugin::PrivateImpl::getName(QString* str)
{
	*str = CONFIG_pluginName;
}

void PyLaunchyPlugin::PrivateImpl::init(QSettings* pSettings)
{
	LOG_FUNCTRACK;

	LOG_STATUS("Starting PyLaunchy");

	qt_utils::QSettingsWrapper settings;
	settings.setQSettings(pSettings);

	ScriptsDirectoryConfig scriptsDirectoryConfig;
	scriptsDirectoryConfig.init(settings);
	const QDir scriptsDir = scriptsDirectoryConfig.scriptsDirectory();

	const QString configFile = settings.fileName();
	QFileInfo configFileInfo(configFile);

	pylaunchy::GlobalPythonModuleData& moduleData =
		pylaunchy::globalPythonModuleData();
	moduleData.pScriptPluginRegisterer = &m_scriptPluginsManager;
	moduleData.scriptsDirectoryAbsolutePath = scriptsDir.absolutePath();
	moduleData.configDirectoryAbsolutePath = configFileInfo.absolutePath();
	moduleData.applicationDirPath = qApp->applicationDirPath();

	PythonInitializer pythonInitializer;
	pythonInitializer.initPython( settings.getQSettings() );

	m_scriptPluginsManager.loadScriptFiles(scriptsDir);
	m_scriptPluginsManager.loadPlugins();	
}

QString PyLaunchyPlugin::PrivateImpl::getIcon()
{
	return QString::null;
}

void PyLaunchyPlugin::PrivateImpl::loadPlugins(QList<PluginInfo>* additionalPlugins)
{
	LOG_FUNCTRACK;

	// Iterate over all script plugins, which are already loaded, and
	// add them to a list supplied to Launchy.
	// TODO: move this code to ScriptPluginsManager, it doesn't seem right here

	LOG_INFO("Adding Python plugins to Launchy");

	const ScriptPluginsManager::PluginInfoHash& scriptPluginsInfo = 
		m_scriptPluginsManager.scriptPluginsInfo();
	ScriptPluginsManager::PluginInfoHash::const_iterator it = 
		scriptPluginsInfo.constBegin();
	ScriptPluginsManager::PluginInfoHash::const_iterator ite = 
		scriptPluginsInfo.constEnd();

	for ( ; it != ite; ++it ) {
		additionalPlugins->push_back(it.value());
	}
}

void PyLaunchyPlugin::PrivateImpl::unloadPlugin(uint id)
{
	m_scriptPluginsManager.unloadPlugin(id);
}

int PyLaunchyPlugin::msg(int msgId, void* wParam, void* lParam)
{
	if (msgId == MSG_INIT) {
		init();
	}
	else if (msgId == MSG_GET_ID) {
		m_pImpl->getID((uint*) wParam);
	}
	else if (msgId == MSG_GET_NAME) {
		m_pImpl->getName((QString*) wParam);
	}
	else if (msgId == MSG_LOAD_PLUGINS) {
		m_pImpl->loadPlugins((QList<PluginInfo>*)wParam);
	}
	else if (msgId == MSG_UNLOAD_PLUGIN) {
		m_pImpl->unloadPlugin((uint)wParam);
	}
	else if (msgId == MSG_HAS_DIALOG) {
		// This is the only case we return false
		return false;
	}
	
	// Message was handled so we return true
	return true;
}

void PyLaunchyPlugin::init()
{
	if (g_pyLaunchyInstance) {
		return;
	}	
	g_pyLaunchyInstance = this;
	m_pImpl->init(*settings);
}

Q_EXPORT_PLUGIN2(PyLaunchy, PyLaunchyPlugin) 
