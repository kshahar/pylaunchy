#include "Precompiled.h"
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include "catalog.h"
#include "ScriptPlugin.h"
#include "PythonUtils.h"

using namespace boost::python;

void export_CatItem()
{
	class_<CatItem>("CatItem", init<>())
		.def(init<QString, bool>())
		.def(init<QString, const char*>())
		.def(init<QString, QString, unsigned int>())
		.def(init<QString, QString, unsigned int, QString>())
		
		BOOST_PYTHON_EXPORT_CUSTOM_TYPE("fullPath", &CatItem::fullPath)
		BOOST_PYTHON_EXPORT_CUSTOM_TYPE("shortName", &CatItem::shortName)
		BOOST_PYTHON_EXPORT_CUSTOM_TYPE("icon", &CatItem::icon)

		.def_readwrite("usage", &CatItem::usage)
		.def_readwrite("id", &CatItem::id)
	;
}

void export_InputData()
{
	class_<InputData>("InputData", no_init)
		.def("setLabel", &InputData::setLabel)
		.def("hasLabel", &InputData::hasLabel)
		.def("setID", &InputData::setID)
		.def("getID", &InputData::getID)
		.def("getText", &InputData::getText)
		.def("setText", &InputData::setText)
		.def("getTopResult", &InputData::getTopResult, return_value_policy<reference_existing_object>())
		.def("setTopResult", &InputData::setTopResult)
	;		

	register_ptr_to_python< InputData* >();

	class_< std::vector<InputData*> >("InputDataVector")
		.def(vector_indexing_suite< std::vector<InputData*>, true>());

}

void export_catalog()
{
	export_CatItem();
	export_InputData();
}
