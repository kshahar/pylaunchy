#ifndef ScriptPluginWrapper_H_
#define ScriptPluginWrapper_H_

#include <QObject>
#include <QMutex>
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
	bool hasDialog();
	void doDialog(QWidget* parent, QWidget**);
	void endDialog(bool accept);
	void init();
	QString getIcon();
	void launchyShow();
	void launchyHide();

private:
	//! Does the actual work of calling a Python function
	bool dispatchFunction(int msgId, void* wParam, void* lParam); 

	ScriptPlugin* m_pScriptPlugin;

	//! Should be locked whenever a Python function is called
	static QMutex s_inPythonFunction;

	//! Should be locked when doDialog was called and before endDialog called
	static QMutex s_pythonGuiMutex;
};

#endif //ScriptPluginWrapper_H_