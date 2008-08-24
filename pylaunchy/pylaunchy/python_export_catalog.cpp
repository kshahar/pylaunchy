#include "Precompiled.h"
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include "catalog.h"
#include "ScriptPlugin.h"
#include "PythonUtils.h"

using namespace boost::python;

/** Convert QSet<T> to a Python list */
template <typename T>
struct QSet_to_python_list
{
    static PyObject* convert(const QSet<T>& set)
    {
		boost::python::list pylist;
		QSet<T>::const_iterator itr = set.constBegin();
		for ( ; itr != set.constEnd(); ++itr) {
			pylist.append(*itr);
		}
		return incref(pylist.ptr());
	}
};

void export_CatItem()
{
	class_<CatItem>("CatItem", init<>())
		.def(init<QString, QString, unsigned int, QString>())
		
		BOOST_PYTHON_EXPORT_CUSTOM_TYPE("fullPath", &CatItem::fullPath)
		BOOST_PYTHON_EXPORT_CUSTOM_TYPE("shortName", &CatItem::shortName)
		BOOST_PYTHON_EXPORT_CUSTOM_TYPE("lowName", &CatItem::lowName)
		BOOST_PYTHON_EXPORT_CUSTOM_TYPE("icon", &CatItem::icon)

		.def_readwrite("usage", &CatItem::usage)
		.def_readwrite("id", &CatItem::id)
	;
}

void export_InputData()
{
	class_<InputData>("InputData", no_init)
		.def("getLabels", &InputData::getLabels)
		.def("setLabel", &InputData::setLabel)
		.def("hasLabel", &InputData::hasLabel)
		.def("setID", &InputData::setID)
		.def("getID", &InputData::getID)
		.def("getText", &InputData::getText)
		.def("setText", &InputData::setText)
		.def("getTopResult", &InputData::getTopResult, 
			return_value_policy<reference_existing_object>())
		.def("setTopResult", &InputData::setTopResult)
	;		

	register_ptr_to_python< InputData* >();

	class_< std::vector<InputData*> >("InputDataVector")
		.def(vector_indexing_suite< std::vector<InputData*>, true>());

}

void export_catalog()
{
	// Converter for the return type of InputData::getLabels()
	boost::python::to_python_converter< 
		QSet<uint>, QSet_to_python_list<uint> >();

	export_CatItem();
	export_InputData();
}
