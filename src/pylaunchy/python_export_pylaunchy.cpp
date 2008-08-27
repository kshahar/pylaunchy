#include "Precompiled.h"

#include <QHash>
#include "plugin_interface.h"
#include "PythonUtils.h"
#include "PyLaunchyPlugin.h"
#include "ScriptPlugin.h"

using namespace boost::python;

namespace pylaunchy 
{
	void registerPlugin(boost::python::object pluginClass)
	{
		LOG_FUNCTRACK;
		g_pyLaunchyInstance->registerPlugin(pluginClass);
	}

	unsigned int hash(QString str)
	{
		LOG_FUNCTRACK;
		return qHash(str);
	}

	QString getLaunchyPath()
	{
		LOG_FUNCTRACK;
		return qApp->applicationDirPath();
	}
	
	QString getScriptsPath()
	{
		LOG_FUNCTRACK;
		return g_pyLaunchyInstance->scriptsDir().absolutePath();
	}

	QString getLibPath()
	{
		LOG_FUNCTRACK;
		return g_pyLaunchyInstance->scriptsDir().absolutePath() + 
			QDir::separator() + "lib";
	}

	QString getIconsPath()
	{
		LOG_FUNCTRACK;
		return qApp->applicationDirPath() + "/plugins/icons";
	}

	QString getConfigPath()
	{
		LOG_FUNCTRACK;
		static QString configPath;
		if (configPath.isNull()) {
			QSettings* settings = *(g_pyLaunchyInstance->settings);
			const QString configFile = settings->fileName();
			QFileInfo configFileInfo(configFile);
			configPath = configFileInfo.absolutePath();
		}
		return configPath;
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
	def("getLibPath", &pylaunchy::getLibPath);
	def("getIconsPath", &pylaunchy::getIconsPath);
	def("getConfigPath", &pylaunchy::getConfigPath);
	def("runProgram", &pylaunchy::runProgram);
}