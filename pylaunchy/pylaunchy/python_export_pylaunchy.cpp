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
		g_pyLaunchyInstance->registerPlugin(pluginClass);
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
		return g_pyLaunchyInstance->scriptsDir().absolutePath();
	}

	QString getLibPath()
	{
		return g_pyLaunchyInstance->scriptsDir().absolutePath() + 
			QDir::separator() + "lib";
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
	def("getLibPath", &pylaunchy::getLibPath);
	def("getIconsPath", &pylaunchy::getIconsPath);
	def("runProgram", &pylaunchy::runProgram);
}