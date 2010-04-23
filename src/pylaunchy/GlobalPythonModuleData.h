#ifndef GlobalPythonModuleData_H_
#define GlobalPythonModuleData_H_

namespace pylaunchy {
	class ScriptPluginRegisterer;

	/** Data required by the pylaunchy module interface
	 */
	class GlobalPythonModuleData {
	public:
		GlobalPythonModuleData();
		ScriptPluginRegisterer* pScriptPluginRegisterer;
		QString scriptsDirectoryAbsolutePath;
		QString configDirectoryAbsolutePath;
		QString applicationDirPath;
	};

	//! 
	GlobalPythonModuleData& globalPythonModuleData(); 

#ifdef PYLAUNCHY_TESTING
	//! Used for testing
	void setGlobalPythonModuleData(GlobalPythonModuleData& globalPythonModuleData);
#endif
};

#endif // GlobalPythonModuleData