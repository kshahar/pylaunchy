#include "Precompiled.h"

#include <QHash>
#include "plugin_interface.h"
#include "ScriptPluginsManager.h"

using namespace boost::python;

// Since the plugin is created in the script, we need to hold a reference
// to it so that the python GC will not delete it
static std::vector<object> g_scriptPluginsObjects;

namespace pylaunchy 
{
	void addPlugin(boost::python::object pluginObject)
	{
		try {
			EZLOGGERSTREAM << "Extracting plugin" << std::endl;
			ScriptPlugin* plugin = extract<ScriptPlugin*>(pluginObject);

			if (!plugin) {
				EZLOGGERSTREAM << "Plugin is NULL" << std::endl;
			}

			if (plugin) {
				EZLOGGERSTREAM << "Initializing plugin" << std::endl;
				plugin->init();

				EZLOGGERSTREAM << "Getting plugin name" << std::endl;
				QString pluginName = plugin->getName();

				EZLOGGERSTREAM << "Adding plugin to list" << std::endl;
				ScriptPluginsManager& pluginsManager = ScriptPluginsManager::instance();
				pluginsManager.addPlugin( ScriptPluginInfo(plugin, pluginName) );

				// Keep a copy of the object here to avoid deleting by the GC
				g_scriptPluginsObjects.push_back(pluginObject);
			}
		}
		catch(boost::python::error_already_set const &) {
			EZLOGGERSTREAM << "Exception caught when trying to add plugin" << std::endl;
		}
	}

	unsigned int hash(const char* str)
	{
		return qHash(str);
	}

	QString getLaunchyPath()
	{
		return qApp->applicationDirPath();
	}
	
	QString getScriptsPath()
	{
		return qApp->applicationDirPath() + "/plugins/python";
	}

	QString getIconsPath()
	{
		return qApp->applicationDirPath() + "/plugins/icons";
	}

	void runProgram(QString file, QString args)
	{
		::runProgram(file, args);
	}
};

void export_pylaunchy()
{
	def("addPlugin", &pylaunchy::addPlugin);
	def("hash", &pylaunchy::hash);
	def("getLaunchyPath", &pylaunchy::getLaunchyPath);
	def("getScriptsPath", &pylaunchy::getScriptsPath);
	def("getIconsPath", &pylaunchy::getIconsPath);
	def("runProgram", &pylaunchy::runProgram);
}