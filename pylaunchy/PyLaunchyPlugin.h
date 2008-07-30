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
#pragma once

#include "plugin_interface.h"
#include "ScriptPluginInfo.h"
#include "ScriptDataStructures.h"

class ScriptPluginsManager;

class PyLaunchyPlugin : public QObject, public PluginInterface
{
	Q_OBJECT
	Q_INTERFACES(PluginInterface)

private:

public:
	PyLaunchyPlugin();
	~PyLaunchyPlugin();
	int msg(int msgId, void* wParam = NULL, void* lParam = NULL); 

	void getLabels(QList<InputData>*);
	void getID(uint*);
	void getName(QString*);
	void getResults(QList<InputData>* id, QList<CatItem>* results);
	void getCatalog(QList<CatItem>* items);
	void launchItem(QList<InputData>*, CatItem*);
	void doDialog(QWidget* parent, QWidget**);
	void endDialog(bool accept);
	void init();
	QString getIcon();
	void launchyShow();
	void launchyHide();

private:
	/** Convert QList<InputData> -> ScriptInputDataList */
	ScriptInputDataList prepareInputDataList(QList<InputData>* id);

	boost::python::object m_mainModule;
	ScriptPluginsManager& m_pluginsManager;
	bool m_launchingItem;
};

extern PyLaunchyPlugin* gmypluginInstance;
