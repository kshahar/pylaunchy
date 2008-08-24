#ifndef ScriptPluginInfo_H_
#define ScriptPluginInfo_H_

class ScriptPlugin;

struct ScriptPluginInfo {
	ScriptPlugin* plugin;
	QString name; // We cache the name for error printing

	ScriptPluginInfo(ScriptPlugin* _plugin, QString _name)
		: plugin(_plugin), name(_name) {}
};

#endif //ScriptPluginInfo_H_