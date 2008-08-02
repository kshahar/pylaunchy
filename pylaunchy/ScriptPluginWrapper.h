#ifndef ScriptPluginWrapper_H_
#define ScriptPluginWrapper_H_

#include "plugin_interface.h"
#include "ScriptDataStructures.h"
class ScriptPlugin;

class ScriptPluginWrapper: public QObject, public PluginInterface
{
	Q_OBJECT
	Q_INTERFACES(PluginInterface)

public:
	ScriptPluginWrapper(ScriptPlugin* scriptPlugin);
	~ScriptPluginWrapper();
	int msg(int msgId, void* wParam = NULL, void* lParam = NULL); 

	void getLabels(QList<InputData>*);
	void getID(uint*);
	void getName(QString*);
	void getResults(QList<InputData>* id, QList<CatItem>* results);
	void getCatalog(QList<CatItem>* items);
	void launchItem(QList<InputData>*, CatItem*);
	void doDialog(QWidget* parent, QWidget**);
	void endDialog(bool accept);
	void init();
	QString getIcon();
	void launchyShow();
	void launchyHide();

private:
	ScriptPlugin* m_pScriptPlugin;
	static bool s_inPythonFunction;
};

#endif //ScriptPluginWrapper_H_