#ifndef ScriptPlugin_H_
#define ScriptPlugin_H_

#include "ScriptDataStructures.h"

class ScriptPlugin {
public:
	virtual void init() = 0;

	virtual unsigned int getID() = 0;

	virtual QString getName() = 0;

	virtual void getLabels(ScriptInputDataList& inputDataList) = 0;

	virtual void getResults(ScriptInputDataList& inputDataList, 
		ScriptResultsList& resultsList) = 0;

	virtual void getCatalog(ScriptResultsList& resultsList) = 0;

	virtual void launchItem(ScriptInputDataList& inputDataList, 
		CatItem& item) = 0;

	virtual bool hasDialog() = 0;

	virtual void* doDialog(void* parentWidget) = 0;

	virtual void endDialog(bool accept) = 0;

	virtual void launchyShow() = 0;

	virtual void launchyHide() = 0;
};

#endif