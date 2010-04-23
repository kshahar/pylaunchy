#ifndef ScriptPluginsSynchronizer_H_
#define ScriptPluginsSynchronizer_H_

#include <memory>

class ScriptPluginsSynchronizer {
public:
	ScriptPluginsSynchronizer();
	~ScriptPluginsSynchronizer();
	
	virtual bool tryLockInPythonMutex();
	virtual void unlockInPythonMutex();
	
	virtual bool tryLockDialogMutex();
	virtual void unlockDialogMutex();
	
	virtual void enteringDoDialog();
	virtual void finishedEndDialog();
private:
	//! Not implemented
	ScriptPluginsSynchronizer(const ScriptPluginsSynchronizer&);
	//! Not implemented
	ScriptPluginsSynchronizer& operator=(const ScriptPluginsSynchronizer&);

	struct PrivateImpl;
	std::auto_ptr<PrivateImpl> m_pImpl;
};

#endif // ScriptPluginsSynchronizer_H_
