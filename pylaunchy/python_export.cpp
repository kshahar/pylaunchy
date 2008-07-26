#include "Precompiled.h"

using namespace boost::python;

extern void export_catalog();
extern void export_pylaunchy();
extern void export_ScriptPlugin();
extern void export_QString();

int add_five(int x)
{
	return x+5;
}

BOOST_PYTHON_MODULE(launchy)
{
	// Export our basic testing function
	def("add_five", add_five);

	export_QString();
	export_pylaunchy();
	export_catalog();
	export_ScriptPlugin();
}

void init_pylaunchy()
{
    initlaunchy();
}

