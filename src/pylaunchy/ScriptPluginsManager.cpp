#include "Precompiled.h"
#include "ScriptPluginsManager.h"

#include "PythonUtils.h"
#include "ScriptPlugin.h"
#include "ScriptPluginWrapper.h"

ScriptPluginsManager::~ScriptPluginsManager()
{
	destroyPlugins();
}

void ScriptPluginsManager::loadScriptFiles(const QDir& scriptsDirectory)
{
	LOG_INFO("Loading script files from %s", scriptsDirectory.absolutePath().toUtf8());
	QDir scriptsDir = scriptsDirectory;

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

void ScriptPluginsManager::registerPlugin(boost::python::object pluginClass)
{
	GUARDED_CALL_TO_PYTHON
	(
		LOG_DEBUG("Registering plugin");
		m_scriptPluginsClasses.push_back(pluginClass);
	);
}

void ScriptPluginsManager::loadPlugins()
{
	LOG_INFO("Reloading script plugins");
	foreach (boost::python::object pluginClass, m_scriptPluginsClasses) {
		GUARDED_CALL_TO_PYTHON
		(
			LOG_DEBUG("Creating plugin object");
			boost::python::object pluginObject = pluginClass();

			LOG_DEBUG("Extracting plugin");
			ScriptPlugin* plugin = 
				boost::python::extract<ScriptPlugin*>(pluginObject);

			const PluginInfo& pluginInfo = addPlugin(plugin);
			m_scriptPluginsObjects.insert(pluginInfo.id, pluginObject);
		);
	}
}

const ScriptPluginsManager::PluginInfoHash& ScriptPluginsManager::scriptPluginsInfo() const
{
	return m_scriptPlugins;
}

void ScriptPluginsManager::unloadPlugin(uint id)
{
	LOG_INFO("Unloading plugin with ID %i", id);
	PluginInfoHash::const_iterator itr = m_scriptPlugins.find(id);
	for ( ; itr != m_scriptPlugins.end() && itr.key() == id; ++itr ) {
		delete itr.value().obj;
	}
	m_scriptPlugins.remove(id);

	m_scriptPluginsObjects.remove(id);
}

void ScriptPluginsManager::destroyPlugins()
{
	LOG_INFO("Destroying script plugins");
	PluginInfoHash::const_iterator itr = m_scriptPlugins.constBegin();
	for ( ; itr != m_scriptPlugins.constEnd(); ++itr ) {
		delete itr.value().obj;
	}
	m_scriptPlugins.clear();

	m_scriptPluginsObjects.clear();
}

const PluginInfo& ScriptPluginsManager::addPlugin(ScriptPlugin* scriptPlugin)
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
