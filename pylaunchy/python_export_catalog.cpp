#include "Precompiled.h"
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include "catalog.h"
#include "ExportedInputData.h"
#include "ScriptPlugin.h"

using namespace boost::python;

void export_CatItem()
{
	class_<CatItem>("CatItem", init<>())
		.def(init<QString, bool>())
		.def(init<QString, const char*>())
		.def(init<QString, QString, unsigned int>())
		.def(init<QString, QString, unsigned int, QString>())
		.def("fullPath", &CatItem::get_fullPath)
		.def("shortName", &CatItem::get_shortName)
		.def("lowName", &CatItem::get_lowName)
		.def("icon", &CatItem::get_icon)
		.def("usage", &CatItem::get_usage)
		.def("id", &CatItem::get_scriptPluginId)
	;

		/* Direct access to CatItem members does not work. 
		I get TypeError with "No Python class registered for C++ class class QString"

		.def_readwrite("fullPath", &CatItem::fullPath)
		.def_readwrite("shortName", &CatItem::shortName)
		.def_readwrite("lowName", &CatItem::lowName)
		.def_readwrite("icon", &CatItem::icon)
		.def_readwrite("usage", &CatItem::usage)
		.def_readwrite("id", &CatItem::id)
		*/
}

/*
void export_CatItem()
{
	class_<ExportedCatItem>("CatItem", init<>())
		.def(init<const char*, bool>())
		.def(init<const char*, const char*>())
		.def(init<const char*, const char*, unsigned int>())
		.def(init<const char*, const char*, unsigned int, const char*>())
		.def("fullPath", &ExportedCatItem::fullPath)
		.def("shortName", &ExportedCatItem::shortName)
		.def("lowName", &ExportedCatItem::lowName)
		.def("icon", &ExportedCatItem::icon)
		.def("usage", &ExportedCatItem::usage)
		.def("id", &ExportedCatItem::id)
	;
}
*/

void export_InputData()
{
	class_<ExportedInputData>("InputData", no_init)
		.def("setLabel", &ExportedInputData::setLabel)
		.def("hasLabel", &ExportedInputData::hasLabel)
		.def("setID", &ExportedInputData::setID)
		.def("getID", &ExportedInputData::getID)
		.def("getText", &ExportedInputData::getText)
		.def("setText", &ExportedInputData::setText)
		.def("getTopResult", &ExportedInputData::getTopResult, return_value_policy<reference_existing_object>())
		.def("setTopResult", &ExportedInputData::setTopResult)
	;
}

class MyTest {
public:
	MyTest(): test1(""), test2("") {}
	const char* test1;
	const char* test2;
};

void export_MyTest()
{
	class_<MyTest>("MyTest")
		.def_readwrite("test1", &MyTest::test1)
		.def_readwrite("test2", &MyTest::test2)
	;
}

void export_catalog()
{
	export_CatItem();
	export_InputData();
	export_MyTest();

	class_< std::vector<ExportedInputData> >("InputDataVector")
                 .def(vector_indexing_suite< std::vector<ExportedInputData>, true>());

}
