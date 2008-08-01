#include "Precompiled.h"
#include <boost/python.hpp>
#include <boost/python/wrapper.hpp>
#include <boost/python/with_custodian_and_ward.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include "ScriptPlugin.h"

using namespace boost::python;

class ScriptPluginWrapper: public ScriptPlugin, public wrapper<ScriptPlugin> {
public:
	virtual void init()
	{
		this->get_override("init")();
	}

	virtual unsigned int getID()
	{
		return this->get_override("getID")();
	}

	virtual QString getName()
	{
		return this->get_override("getName")();
	}

	virtual QString getIcon()
	{
		return this->get_override("getIcon")();
	}

	virtual void getLabels(ScriptInputDataList& inputDataList)
	{
		this->get_override("getLabels")(inputDataList);
	}

	virtual void getResults(ScriptInputDataList& inputDataList, 
		ScriptResultsList& resultsList)
	{
		this->get_override("getResults")(inputDataList, resultsList);
	}

	virtual void getCatalog(ScriptResultsList& resultsList)
	{
		this->get_override("getCatalog")(resultsList);
	}

	virtual void launchItem(ScriptInputDataList& inputDataList, 
		CatItem& item)
	{
		this->get_override("launchItem")(inputDataList, item);
	}

	virtual void launchyShow()
	{
		this->get_override("launchyShow")();
	}

	virtual void launchyHide()
	{
		this->get_override("launchyHide")();
	}


};

void export_ScriptResultsList()
{
	class_< ScriptResultsList>("ResultsList", no_init)
		.def("append", &ScriptResultsList::append)
		.def("prepend", &ScriptResultsList::prepend)
		.def("push_front", &ScriptResultsList::push_front)
		.def("push_back", &ScriptResultsList::push_back)
	;
}

void export_ScriptPlugin()
{
	export_ScriptResultsList();

	class_< ScriptPluginWrapper, boost::noncopyable >("Plugin")
		.def("init", pure_virtual(&ScriptPlugin::init))
		.def("getID", pure_virtual(&ScriptPlugin::getID))
		.def("getName", pure_virtual(&ScriptPlugin::getName))
		.def("getIcon", pure_virtual(&ScriptPlugin::getIcon))
		.def("getLabels", pure_virtual(&ScriptPlugin::getLabels))
		.def("getResults", pure_virtual(&ScriptPlugin::getResults))
		.def("getCatalog", pure_virtual(&ScriptPlugin::getCatalog))
		.def("launchItem", pure_virtual(&ScriptPlugin::launchItem))
		.def("launchyShow", pure_virtual(&ScriptPlugin::launchyShow))
		.def("launchyHide", pure_virtual(&ScriptPlugin::launchyHide))
    ;

}
