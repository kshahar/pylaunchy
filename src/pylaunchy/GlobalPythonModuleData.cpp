#include "Precompiled.h"
#include "GlobalPythonModuleData.h"

namespace pylaunchy 
{
	GlobalPythonModuleData _globalPythonModuleData;

	GlobalPythonModuleData& globalPythonModuleData()
	{
		return _globalPythonModuleData;
	}

#ifdef PYLAUNCHY_TESTING
	//! Used for testing
	void setGlobalPythonModuleData(GlobalPythonModuleData& globalPythonModuleData)
	{
		_globalPythonModuleData = globalPythonModuleData;
	}
#endif

	GlobalPythonModuleData::GlobalPythonModuleData()
	: pScriptPluginRegisterer(0)
	{
	}
}