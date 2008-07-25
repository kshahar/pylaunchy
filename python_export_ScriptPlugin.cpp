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

	virtual void addLabels(ScriptInputDataList& inputDataList)
	{
		this->get_override("addLabels")(inputDataList);
	}

	virtual void addResults(ScriptInputDataList& inputDataList, 
		ScriptResultsList& resultsList)
	{
		this->get_override("addResults")(inputDataList, resultsList);
	}

	virtual void getCatalog(ScriptResultsList& resultsList)
	{
		this->get_override("getCatalog")(resultsList);
	}

	virtual void launchItem(ScriptInputDataList& inputDataList, 
		const ExportedCatItem& item)
	{
		this->get_override("launchItem")(inputDataList, item);
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

	class_< ScriptInputDataList >("InputDataList")
		.def(vector_indexing_suite< ScriptInputDataList, true>());

	class_< ScriptPluginWrapper, boost::noncopyable >("Plugin")
		.def("init", pure_virtual(&ScriptPlugin::init))
		.def("getID", pure_virtual(&ScriptPlugin::getID))
		.def("getName", pure_virtual(&ScriptPlugin::getName))
		.def("getIcon", pure_virtual(&ScriptPlugin::getIcon))
		.def("addLabels", pure_virtual(&ScriptPlugin::addLabels))
		.def("addResults", pure_virtual(&ScriptPlugin::addResults))
		.def("getCatalog", pure_virtual(&ScriptPlugin::getCatalog))
		.def("launchItem", pure_virtual(&ScriptPlugin::launchItem))
    ;

}
