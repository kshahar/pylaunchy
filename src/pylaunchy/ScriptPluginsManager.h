#ifndef ScriptPluginsManager_H_
#define ScriptPluginsManager_H_

#include <boost/python/object.hpp>
#include <QList>
#include <QHash>
#include "launchy/plugin_info.h"
#include "ScriptPluginRegisterer.h"
#include "ScriptPluginsSynchronizer.h"

class QDir;
class ScriptPlugin;

class ScriptPluginsManager: public pylaunchy::ScriptPluginRegisterer {
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
	ScriptPluginsSynchronizer m_scriptPluginsSynchronizer;
};

#endif // ScriptPluginsManager_H_
