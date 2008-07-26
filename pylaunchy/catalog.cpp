#include "Precompiled.h"
#include "catalog.h"

#include "ScriptPluginsManager.h"
#include "NullScriptPlugin.h"
#include "PyLaunchyPluginDefines.h"

CatItem::CatItem() {}



CatItem::CatItem(QString full, bool isDir) 
	: fullPath(full) 
{
	int last = fullPath.lastIndexOf("/");
	if (last == -1) {
		shortName = fullPath;

	} else {
		shortName = fullPath.mid(last+1);
		if (!isDir)
			shortName = shortName.mid(0,shortName.lastIndexOf("."));
	}

	lowName = shortName.toLower();
	data = NULL;
	usage = 0;
	id = 0;
	data = ScriptPluginsManager::instance().currentPlugin();
}


CatItem::CatItem(QString full, QString shortN) 
	: fullPath(full), shortName(shortN) 
{
	lowName = shortName.toLower();
	usage = 0;
	id = 0;
	data = ScriptPluginsManager::instance().currentPlugin();
}

CatItem::CatItem(QString full, QString shortN, uint i_d) 
	: /*id(i_d), */fullPath(full), shortName(shortN)
{
	lowName = shortName.toLower();
	id = pylaunchy::pluginHash;
	usage = 0;
	data = ScriptPluginsManager::instance().currentPlugin();
}

CatItem::CatItem(QString full, QString shortN, uint i_d, QString iconPath) 
	: /*id(i_d), */fullPath(full), shortName(shortN), icon(iconPath)
{
	lowName = shortName.toLower();
	id = pylaunchy::pluginHash;
	usage = 0;
	data = ScriptPluginsManager::instance().currentPlugin();
}

CatItem::CatItem(const CatItem &s) {
	fullPath = s.fullPath;
	shortName = s.shortName;
	lowName = s.lowName;
	icon = s.icon;
	usage = s.usage;
	data = s.data;
	id = s.id;
}

CatItem& CatItem::operator=( const CatItem &s ) {
	fullPath = s.fullPath;
	shortName = s.shortName;
	lowName = s.lowName;
	icon = s.icon;
	usage = s.usage;
	data = s.data;
	id = s.id;
	return *this;
}

bool CatItem::operator==(const CatItem& other) const{
	if (fullPath == other.fullPath)
		return true;
	return false;
}

int CatItem::get_scriptPluginId() const
{
	if (id == pylaunchy::pluginHash) {
		ScriptPlugin* plugin = reinterpret_cast<ScriptPlugin*>(data);
		return plugin->getID();
	}
	else {
		return id;
	}
}