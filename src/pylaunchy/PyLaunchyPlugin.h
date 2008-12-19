/*
Launchy: Application Launcher
Copyright (C) 2007  Josh Karlin

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
#ifndef PyLaunchyPlugin_H_
#define PyLaunchyPlugin_H_

#include "plugin_interface.h"
#include "ScriptPluginsManager.h"

class PyLaunchyPlugin : public QObject, public PluginInterface
{
	Q_OBJECT
	Q_INTERFACES(PluginInterface)

public:
	/** Interface for script plugins management */
	//@{
	void registerPlugin(boost::python::object pluginClass);
	const QDir& scriptsDir() const;
	//@}

public:
	/** Interface for Launchy */
	//@{

	PyLaunchyPlugin();
	~PyLaunchyPlugin();
	int msg(int msgId, void* wParam = NULL, void* lParam = NULL); 

	void getID(uint*);
	void getName(QString*);
	void init();
	QString getIcon();
	void loadPlugins(QList<PluginInfo>* additionalPlugins);
	void unloadPlugin(uint id);

	//@}

private:
	void initPython();
	void handleVersion();

	ScriptPluginsManager m_scriptPluginsManager;
	QDir m_scriptsDir;
};

extern PyLaunchyPlugin* g_pyLaunchyInstance;

#endif //PyLaunchyPlugin_H_