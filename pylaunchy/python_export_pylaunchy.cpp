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

	boost::python::handle<> getSettings()
	{
		QSettings* settings = *g_pyLaunchyInstance->settings;
		PyObject* settingsPyObject = PyLong_FromVoidPtr ((void *) settings);
		return handle<>(settingsPyObject);
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
	def("getSettings", &pylaunchy::getSettings);
}