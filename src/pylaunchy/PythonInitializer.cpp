#include "Precompiled.h"
#include "PythonInitializer.h"

#include <Python.h>
#include <boost/python.hpp>
#include "PythonUtils.h"
#include "python_export/python_export.h"
#include "qt_utils/QTemporaryFileWrapper.h"

void PythonInitializer::initPython(void* pQSettingsObject)
{
	if ( !initPythonSystem() ) {
		return;
	}

	initPythonBindings();

	setQSettingsObject(pQSettingsObject);

	executePythonInitScript();
}

bool PythonInitializer::initPythonSystem()
{
	LOG_FUNCTRACK;
	Py_Initialize();
	if (PyUnicode_SetDefaultEncoding("utf-8"))
	{
		LOG_FATAL("Failed to set default encoding to utf-8.\n");
		PyErr_Clear();
		return false;
	}
	return true;
}

void PythonInitializer::initPythonBindings()
{
	LOG_INFO("Initializing Python bindings");
	GUARDED_CALL_TO_PYTHON
	(		
		python_export::init_pylaunchy();
	);
}

void PythonInitializer::setQSettingsObject(void* pQSettingsObject)
{
	LOG_FUNCTRACK;
	GUARDED_CALL_TO_PYTHON
	(
		LOG_DEBUG("Importing launchy");
		boost::python::object launchyModule = boost::python::import("launchy");
		boost::python::object launchyNamespace = launchyModule.attr("__dict__");

		LOG_DEBUG("Setting launchy.__settings object");
		if (pQSettingsObject) {
			PyObject* settingsPyObject = 
				PyLong_FromVoidPtr( pQSettingsObject );
			launchyNamespace["__settings"] = 
				boost::python::handle<>(settingsPyObject);
		}
		else {
			LOG_WARN("Launchy's QSettings object was not found");
		}
	);
}

void PythonInitializer::executePythonInitScript()
{
	LOG_FUNCTRACK;
	LOG_DEBUG("Copying init script to temporary file");
	qt_utils::QTemporaryFileWrapper initScript(
		QTemporaryFile::createLocalFile( ":/pylaunchy.py" )
	);

	GUARDED_CALL_TO_PYTHON
	(
		LOG_DEBUG("Importing __main__ and __dict__");
		boost::python::object mainModule = boost::python::import("__main__");
		boost::python::object mainNamespace = mainModule.attr("__dict__");

		LOG_INFO("Executing init script file");
		boost::python::exec_file(
			initScript.fileName(), 
			mainNamespace, mainNamespace);
		LOG_INFO("Finished executing init script");
	);
}
