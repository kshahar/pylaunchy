#include "Precompiled.h"
#include "NullScriptPlugin.h"

NullScriptPlugin* NullScriptPlugin::s_pInstance = NULL;
static const QString nameNullScriptPlugin("NullScriptPlugin");
const unsigned int NullScriptPlugin::hash = qHash(nameNullScriptPlugin);

NullScriptPlugin::NullScriptPlugin()
{
}

NullScriptPlugin* NullScriptPlugin::instance()
{
	if (s_pInstance == NULL) {
		s_pInstance = new NullScriptPlugin;
	}
	return s_pInstance;
}

void NullScriptPlugin::init()
{
}

unsigned int NullScriptPlugin::getID()
{
	return hash;
}

QString NullScriptPlugin::getName()
{
	return nameNullScriptPlugin;
}

QString NullScriptPlugin::getIcon()
{
	static QString icon;
	return icon;
}

void NullScriptPlugin::getLabels(ScriptInputDataList& inputDataList)
{
}

void NullScriptPlugin::getResults(ScriptInputDataList& inputDataList, 
		ScriptResultsList& resultsList)
{
}

void NullScriptPlugin::getCatalog(ScriptResultsList& resultsList)
{
}

void NullScriptPlugin::launchItem(ScriptInputDataList& inputDataList, 
	CatItem& item)
{
}	

void* NullScriptPlugin::doDialog(void* parentWidget)
{
	return NULL;
}

void NullScriptPlugin::endDialog(bool accept)
{
}

void NullScriptPlugin::launchyShow()
{
}

void NullScriptPlugin::launchyHide()
{
}
