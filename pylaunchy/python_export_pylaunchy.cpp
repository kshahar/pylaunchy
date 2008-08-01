#include "Precompiled.h"

#include <QHash>
#include "plugin_interface.h"
#include "PythonUtils.h"
#include "PyLaunchyPlugin.h"
#include "ScriptPlugin.h"

using namespace boost::python;

// Since the plugin is created in the script, we need to hold a reference
// to it so that the python GC will not delete it
static std::vector<object> g_scriptPluginsObjects;

extern PyLaunchyPlugin* g_pyLaunchyInstance;

namespace pylaunchy 
{
	void registerPlugin(boost::python::object pluginObject)
	{
		LOG_FUNCTRACK;

		GUARDED_CALL_TO_PYTHON
		(
			LOG_DEBUG("Extracting plugin");
			ScriptPlugin* plugin = extract<ScriptPlugin*>(pluginObject);

			if (!plugin) {
				LOG_DEBUG("Plugin is NULL");
				return;
			}

			if (plugin) {
				LOG_DEBUG("Initializing plugin");
				plugin->init();

				LOG_DEBUG("Getting plugin name");
				QString pluginName = plugin->getName();

				LOG_DEBUG("Registering plugin");
				g_pyLaunchyInstance->registerPlugin(plugin);

				// Keep a copy of the object here to avoid deleting by the GC
				g_scriptPluginsObjects.push_back(pluginObject);
			}
		);
	}

	unsigned int hash(QString str)
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
		LOG_DEBUG("Running file [args]: %s [%s]", 
			(const char*)file.toUtf8(), (const char*)args.toUtf8());
		::runProgram(file, args);
	}
};

void export_pylaunchy()
{
	def("registerPlugin", &pylaunchy::registerPlugin);
	def("hash", &pylaunchy::hash);
	def("getLaunchyPath", &pylaunchy::getLaunchyPath);
	def("getScriptsPath", &pylaunchy::getScriptsPath);
	def("getIconsPath", &pylaunchy::getIconsPath);
	def("runProgram", &pylaunchy::runProgram);
}