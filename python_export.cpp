#include "Precompiled.h"

#include <QHash>

#include "plugin_interface.h"

using namespace boost::python;
extern void export_catalog();
extern void export_ScriptPlugin();
extern void export_QString();

int add_five(int x)
{
	return x+5;
}

namespace pylaunchy 
{
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



BOOST_PYTHON_MODULE(launchy)
{
	// Export our basic testing function
	def("add_five", add_five);

	def("hash", &pylaunchy::hash);
	def("getLaunchyPath", &pylaunchy::getLaunchyPath);
	def("getScriptsPath", &pylaunchy::getScriptsPath);
	def("getIconsPath", &pylaunchy::getIconsPath);
	def("runProgram", &pylaunchy::runProgram);

	export_QString();
	export_catalog();
	export_ScriptPlugin();
}

void init_pylaunchy()
{
    initlaunchy();
}

