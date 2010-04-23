#ifndef ScriptPluginRegisterer_H_
#define ScriptPluginRegisterer_H_

#include <boost/python/object.hpp>

namespace pylaunchy {
	class ScriptPluginRegisterer {
	public:
		virtual void registerPlugin(boost::python::object pluginClass) = 0;
	};
};

#endif // ScriptPluginRegisterer_H_