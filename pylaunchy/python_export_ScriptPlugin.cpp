#include "Precompiled.h"
#include <boost/python.hpp>
#include <boost/python/wrapper.hpp>
#include <boost/python/with_custodian_and_ward.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include "ScriptPlugin.h"
#include "PythonUtils.h"

using namespace boost::python;

namespace pylaunchy {
	class ScriptPluginWrapper: public ScriptPlugin, public wrapper<ScriptPlugin> {
	public:
		virtual void init()
		{
			if (override f = this->get_override("init")) {
				f();
			}
		}

		virtual unsigned int getID()
		{
			if (override f = this->get_override("getID")) {
				return f();
			}
			else {
				return -1;
			}
		}

		virtual QString getName()
		{
			static QString defaultName("DefaultScriptPlugin");

			if (override f = this->get_override("getName")) {
				return f();
			}
			else {
				return defaultName;
			}
		}

		virtual QString getIcon()
		{
			static QString icon;

			if (override f = this->get_override("getIcon")) {
				return f();
			}
			else {
				return icon;
			}
		}

		virtual void getLabels(ScriptInputDataList& inputDataList)
		{
			if (override f = this->get_override("getLabels")) {
				f(inputDataList);
			}
		}

		virtual void getResults(ScriptInputDataList& inputDataList, 
			ScriptResultsList& resultsList)
		{
			if (override f = this->get_override("getResults")) {
				f(inputDataList, resultsList);
			}
		}

		virtual void getCatalog(ScriptResultsList& resultsList)
		{
			if (override f = this->get_override("getCatalog")) {
				f(resultsList);
			}
		}

		virtual void launchItem(ScriptInputDataList& inputDataList, 
			CatItem& item)
		{
			if (override f = this->get_override("launchItem")) {
				f(inputDataList, item);
			}
		}

		virtual void* doDialog(void* parentWidget)
		{
			PyObject *pw = PyLong_FromVoidPtr ((void *) parentWidget);
			if (override f = this->get_override("doDialog")) {
				object result = f(handle<>(pw));
				return voidPtrFromObject(result);
			}
			else {
				return NULL;
			}			
		}

		virtual void endDialog(bool accept)
		{
			if (override f = this->get_override("endDialog")) {
				f(accept);
			}
		}

		virtual void launchyShow()
		{
			if (override f = this->get_override("launchyShow")) {
				f();
			}
		}

		virtual void launchyHide()
		{
			if (override f = this->get_override("launchyHide")) {
				f();
			}
		}

	};
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

	using pylaunchy::ScriptPluginWrapper;
	class_< ScriptPluginWrapper, boost::noncopyable >("Plugin")
		.def("init", pure_virtual(&ScriptPlugin::init))
		.def("getID", pure_virtual(&ScriptPlugin::getID))
		.def("getName", pure_virtual(&ScriptPlugin::getName))
		.def("getIcon", pure_virtual(&ScriptPlugin::getIcon))
		.def("getLabels", pure_virtual(&ScriptPlugin::getLabels))
		.def("getResults", pure_virtual(&ScriptPlugin::getResults))
		.def("getCatalog", pure_virtual(&ScriptPlugin::getCatalog))
		.def("launchItem", pure_virtual(&ScriptPlugin::launchItem))
		.def("doDialog", pure_virtual(&ScriptPlugin::doDialog), return_value_policy<return_by_value>())
		.def("endDialog", pure_virtual(&ScriptPlugin::endDialog))
		.def("launchyShow", pure_virtual(&ScriptPlugin::launchyShow))
		.def("launchyHide", pure_virtual(&ScriptPlugin::launchyHide))
    ;

}
