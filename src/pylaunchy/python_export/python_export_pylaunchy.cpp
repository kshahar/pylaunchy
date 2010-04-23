#include "Precompiled.h"

#include <QHash>
#include "launchy/plugin_interface.h" // For runProgram
#include "PythonUtils.h"
#include "ScriptPluginRegisterer.h"
#include "GlobalPythonModuleData.h"

using namespace boost::python;

// TODO: Move out of this file
namespace pylaunchy 
{
	void registerPlugin(boost::python::object pluginClass)
	{
		LOG_FUNCTRACK;
		ScriptPluginRegisterer* pScriptPluginRegisterer = 
			globalPythonModuleData().pScriptPluginRegisterer;
		if (pScriptPluginRegisterer) {
			pScriptPluginRegisterer->registerPlugin(pluginClass);
		}
	}

	unsigned int hash(QString str)
	{
		LOG_FUNCTRACK;
		return qHash(str);
	}

	QString getLaunchyPath()
	{
		LOG_FUNCTRACK;
		return globalPythonModuleData().applicationDirPath;
	}
	
	QString getScriptsPath()
	{
		LOG_FUNCTRACK;
		return globalPythonModuleData().scriptsDirectoryAbsolutePath;
	}

	QString getLibPath()
	{
		LOG_FUNCTRACK;
		return globalPythonModuleData().scriptsDirectoryAbsolutePath + 
			QDir::separator() + "lib";
	}

	QString getIconsPath()
	{
		LOG_FUNCTRACK;
		return globalPythonModuleData().applicationDirPath + 
			"/plugins/icons";
	}

	QString getConfigPath()
	{
		LOG_FUNCTRACK;
		return globalPythonModuleData().configDirectoryAbsolutePath;
	}

	void runProgram(QString file, QString args)
	{
		LOG_DEBUG("Running file [args]: %s [%s]", 
			(const char*)file.toUtf8(), (const char*)args.toUtf8());
		::runProgram(file, args);
	}
};

namespace python_export {

void export_pylaunchy()
{
	def("registerPlugin", &pylaunchy::registerPlugin);
	def("hash", &pylaunchy::hash);
	def("getLaunchyPath", &pylaunchy::getLaunchyPath);
	def("getScriptsPath", &pylaunchy::getScriptsPath);
	def("getLibPath", &pylaunchy::getLibPath);
	def("getIconsPath", &pylaunchy::getIconsPath);
	def("getConfigPath", &pylaunchy::getConfigPath);
	def("runProgram", &pylaunchy::runProgram);
}

}