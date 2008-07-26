#include "Precompiled.h"
#include "ScriptPluginsManager.h"
#include "NullScriptPlugin.h"

ScriptPluginsManager* ScriptPluginsManager::s_pInstance = NULL;

ScriptPluginsManager::ScriptPluginsManager()
: m_currentPlugin( NullScriptPlugin::instance() )
{
}

ScriptPluginsManager& ScriptPluginsManager::instance()
{
	if (s_pInstance == NULL) {
		s_pInstance = new ScriptPluginsManager;
	}
	return *s_pInstance;
}

void ScriptPluginsManager::addPlugin(const ScriptPluginInfo& pluginInfo)
{
	m_scriptPlugins.push_back(pluginInfo);
}

QList<ScriptPluginInfo>& ScriptPluginsManager::plugins()
{
	return m_scriptPlugins;
}

ScriptPlugin* ScriptPluginsManager::currentPlugin() const
{
	return m_currentPlugin;
}

void ScriptPluginsManager::setCurrentPlugin(ScriptPlugin* plugin)
{
	m_currentPlugin = plugin;
}

void ScriptPluginsManager::resetCurrentPlugin()
{
	m_currentPlugin = NullScriptPlugin::instance();
}