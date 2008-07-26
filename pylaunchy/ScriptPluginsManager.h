#ifndef ScriptPluginsManager_H_
#define ScriptPluginsManager_H_

#include "ScriptPlugin.h"
#include "ScriptPluginInfo.h"

class ScriptPluginsManager {
public:
	/** Returns the only instance of NullScriptPlugin */
	static ScriptPluginsManager& instance();

	void addPlugin(const ScriptPluginInfo& pluginInfo);
	QList<ScriptPluginInfo>& plugins();

	ScriptPlugin* currentPlugin() const;
	void setCurrentPlugin(ScriptPlugin* plugin);
	void resetCurrentPlugin();

private:
	ScriptPluginsManager();
	ScriptPluginsManager(const ScriptPluginsManager&);
	ScriptPluginsManager& operator=(const ScriptPluginsManager&);

	static ScriptPluginsManager* s_pInstance;

	ScriptPlugin* m_currentPlugin;
	QList<ScriptPluginInfo> m_scriptPlugins;
};

#endif //ScriptPluginsManager