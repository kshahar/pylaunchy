#include <gtest/gtest.h>
#include <memory>
#include <QMutex>
#include <QThread>

#include "ScriptPluginWrapper.h"
#include "ScriptPlugin.h"
#include "ScriptPluginsSynchronizer.h"

class LockedScriptPlugin: public ScriptPlugin {
public:
	QMutex m_mutex;

	virtual void init() {}
	virtual unsigned int getID() { return 1234; }
	virtual QString getName() { return "BlockedScriptPlugin"; }
	virtual void getLabels(ScriptInputDataList& inputDataList) {}
	virtual void getResults(ScriptInputDataList& inputDataList, 
		ScriptResultsList& resultsList) {}
	virtual void getCatalog(ScriptResultsList& resultsList) {}
	virtual void launchItem(ScriptInputDataList& inputDataList, 
		CatItem& item) {}
	virtual bool hasDialog() { return false; }
	virtual void* doDialog(void* parentWidget) { return NULL; }
	virtual void endDialog(bool accept) {}
	virtual void launchyShow()
	{
		// Wait until we are unlocked
		m_mutex.lock();
		m_mutex.unlock();
	}
	virtual void launchyHide() {}  
};

class LaunchyShowThread: public QThread {
public:
	LaunchyShowThread( ScriptPluginWrapper& scriptPluginWrapper )
		: m_scriptPluginWrapper(scriptPluginWrapper) {}

	virtual void run()
	{
		m_scriptPluginWrapper.msg(MSG_LAUNCHY_SHOW);
	}

private:
	ScriptPluginWrapper& m_scriptPluginWrapper;
};

class LaunchyHideThread: public QThread {
public:
	LaunchyHideThread( ScriptPluginWrapper& scriptPluginWrapper )
		: m_scriptPluginWrapper(scriptPluginWrapper) {}

	virtual void run()
	{
		m_scriptPluginWrapper.msg(MSG_LAUNCHY_HIDE);
	}

private:
	ScriptPluginWrapper& m_scriptPluginWrapper;
};

//! Give time to the other threads
static void YieldThread()
{
#ifdef _WIN32
	Sleep(10);
#endif //_WIN32
}

TEST(ScriptPluginWrapperTest, CallFromOneThread)
{
	LockedScriptPlugin lockedScriptPlugin;
	ScriptPluginsSynchronizer synchronizer;
	ScriptPluginWrapper scriptPluginWrapper( 
		&lockedScriptPlugin, synchronizer );
	LaunchyShowThread launchyShowThread(scriptPluginWrapper);

	lockedScriptPlugin.m_mutex.lock();
	launchyShowThread.start(); // Should block

	YieldThread();
	ASSERT_TRUE( scriptPluginWrapper.isInPythonFunction() );
	ASSERT_FALSE( launchyShowThread.isFinished() );

	lockedScriptPlugin.m_mutex.unlock();

	YieldThread();
	EXPECT_FALSE( scriptPluginWrapper.isInPythonFunction() );
	EXPECT_TRUE( launchyShowThread.isFinished() );
}

TEST(ScriptPluginWrapperTest, CallsFromMultipleThreads)
{
	LockedScriptPlugin lockedScriptPlugin;
	ScriptPluginsSynchronizer synchronizer;
	ScriptPluginWrapper scriptPluginWrapper( 
		&lockedScriptPlugin, synchronizer );
	LaunchyShowThread launchyShowThread(scriptPluginWrapper);
	LaunchyHideThread launchyHideThread(scriptPluginWrapper);

	lockedScriptPlugin.m_mutex.lock();
	launchyShowThread.start(); // Should block
	
	YieldThread();
	ASSERT_TRUE( scriptPluginWrapper.isInPythonFunction() );
	ASSERT_FALSE( launchyShowThread.isFinished() );

	launchyHideThread.start(); // Should finish immediately
	YieldThread();
	ASSERT_TRUE( launchyHideThread.isFinished() );

	lockedScriptPlugin.m_mutex.unlock();

	YieldThread();
	EXPECT_FALSE( scriptPluginWrapper.isInPythonFunction() );
	EXPECT_TRUE( launchyShowThread.isFinished() );
}
