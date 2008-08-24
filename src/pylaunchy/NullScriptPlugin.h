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

	virtual void getLabels(ScriptInputDataList& inputDataList);

	virtual void getResults(ScriptInputDataList& inputDataList, 
		ScriptResultsList& resultsList);

	virtual void getCatalog(ScriptResultsList& resultsList);

	virtual void launchItem(ScriptInputDataList& inputDataList, 
		CatItem& item);	

	virtual bool hasDialog();

	virtual void* doDialog(void* parentWidget);

	virtual void endDialog(bool accept);

	virtual void launchyShow();

	virtual void launchyHide();

	static const unsigned int hash;

private:
	NullScriptPlugin();
	NullScriptPlugin(const NullScriptPlugin&);
	NullScriptPlugin& operator=(const NullScriptPlugin&);

	static NullScriptPlugin* s_pInstance;
};

#endif //NullScriptPlugin_H_