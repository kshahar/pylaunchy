#ifndef ScriptPluginWrapper_H_
#define ScriptPluginWrapper_H_

#include <QObject>
#include "launchy/plugin_interface.h"
#include "ScriptDataStructures.h"
class ScriptPlugin;
class ScriptPluginsSynchronizer;

class ScriptPluginWrapper: public QObject, public PluginInterface
{
	Q_OBJECT

public:
	ScriptPluginWrapper(ScriptPlugin* scriptPlugin, 
		ScriptPluginsSynchronizer& scriptPluginsSynchronizer);
	~ScriptPluginWrapper();
	int msg(int msgId, void* wParam = NULL, void* lParam = NULL); 

	void getLabels(QList<InputData>*);
	void getID(uint*);
	void getName(QString*);
	void getResults(QList<InputData>* id, QList<CatItem>* results);
	void getCatalog(QList<CatItem>* items);
	void launchItem(QList<InputData>*, CatItem*);
	bool hasDialog();
	void doDialog(QWidget* parent, QWidget**);
	void endDialog(bool accept);
	void init();
	QString getIcon();
	void launchyShow();
	void launchyHide();

	//! For testing
	bool isInPythonFunction() const;

private:
	//! Does the actual work of calling a Python function
	bool dispatchFunction(int msgId, void* wParam, void* lParam); 

	ScriptPlugin* m_pScriptPlugin;
	ScriptPluginsSynchronizer& m_scriptPluginsSynchronizer;
};

#endif //ScriptPluginWrapper_H_