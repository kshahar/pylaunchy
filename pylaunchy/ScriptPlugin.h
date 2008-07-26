#ifndef ScriptPlugin_H_
#define ScriptPlugin_H_

#include "ScriptDataStructures.h"

class ScriptPlugin {
public:
	virtual void init() = 0;

	virtual unsigned int getID() = 0;

	virtual QString getName() = 0;

	virtual QString getIcon() = 0;

	virtual void addLabels(ScriptInputDataList& inputDataList) = 0;

	virtual void addResults(ScriptInputDataList& inputDataList, 
		ScriptResultsList& resultsList) = 0;

	virtual void getCatalog(ScriptResultsList& resultsList) = 0;

	virtual void launchItem(ScriptInputDataList& inputDataList, 
		CatItem& item) = 0;
};

#endif