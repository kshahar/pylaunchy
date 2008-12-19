#ifndef ScriptPluginsManager_H_
#define ScriptPluginsManager_H_

#include <boost/python/object.hpp>
#include <QList>
#include <QHash>
#include "plugin_info.h"

class QDir;
class ScriptPlugin;

class ScriptPluginsManager {
public:
	~ScriptPluginsManager();

	void loadScriptFiles(const QDir& scriptsDirectory);
	void registerPlugin(boost::python::object pluginClass);
	void loadPlugins();

	typedef QHash<uint, PluginInfo> PluginInfoHash;
	const PluginInfoHash& scriptPluginsInfo() const;

	void unloadPlugin(uint id);
	void destroyPlugins();
private:
	const PluginInfo& addPlugin(ScriptPlugin* scriptPlugin);

	QList<boost::python::object> m_scriptPluginsClasses;
	QHash<uint, boost::python::object> m_scriptPluginsObjects;
	PluginInfoHash m_scriptPlugins;
};

#endif // ScriptPluginsManager_H_
