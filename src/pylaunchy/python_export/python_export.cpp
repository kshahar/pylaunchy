#include "Precompiled.h"
#include "python_export_catalog.h"
#include "python_export_pylaunchy.h"
#include "python_export_qstring.h"
#include "python_export_ScriptPlugin.h"

using namespace boost::python;

static int add_five(int x)
{
	return x+5;
}

BOOST_PYTHON_MODULE(launchy)
{
	// Don't want auto docstrings at this time
	//docstring_options doc_options(true);

	// Export our basic testing function
	def("add_five", add_five);

	python_export::export_QString();
	python_export::export_pylaunchy();
	python_export::export_catalog();
	python_export::export_ScriptPlugin();
}

namespace python_export {
	void init_pylaunchy()
	{
		initlaunchy();
	}
};
