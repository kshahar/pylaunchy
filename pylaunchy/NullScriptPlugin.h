#ifndef NullScriptPlugin_H_
#define NullScriptPlugin_H_

#include "ScriptPlugin.h"

class NullScriptPlugin: public ScriptPlugin {
public:
	/** Returns the only instance of NullScriptPlugin */
	static NullScriptPlugin* instance();

	virtual void init();

	virtual unsigned int getID();

	virtual QString getName();

	virtual QString getIcon();

	virtual void addLabels(ScriptInputDataList& inputDataList);

	virtual void addResults(ScriptInputDataList& inputDataList, 
		ScriptResultsList& resultsList);

	virtual void getCatalog(ScriptResultsList& resultsList);

	virtual void launchItem(ScriptInputDataList& inputDataList, 
		CatItem& item);	

	static const unsigned int hash;

private:
	NullScriptPlugin();
	NullScriptPlugin(const NullScriptPlugin&);
	NullScriptPlugin& operator=(const NullScriptPlugin&);

	static NullScriptPlugin* s_pInstance;
};

#endif //NullScriptPlugin_H_