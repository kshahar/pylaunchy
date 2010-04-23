#include "Precompiled.h"
#include "ScriptPluginsSynchronizer.h"
#include <QMutex>

struct ScriptPluginsSynchronizer::PrivateImpl {
	QMutex dialogMutex;
	QMutex inPythonMutex;
};

ScriptPluginsSynchronizer::ScriptPluginsSynchronizer()
: m_pImpl(new PrivateImpl)
{
}

ScriptPluginsSynchronizer::~ScriptPluginsSynchronizer()
{
}

bool ScriptPluginsSynchronizer::tryLockInPythonMutex()
{
	return m_pImpl->inPythonMutex.tryLock();
}

void ScriptPluginsSynchronizer::unlockInPythonMutex()
{
	m_pImpl->inPythonMutex.unlock();
}

bool ScriptPluginsSynchronizer::tryLockDialogMutex()
{
	return m_pImpl->dialogMutex.tryLock();
}

void ScriptPluginsSynchronizer::unlockDialogMutex()
{
	m_pImpl->dialogMutex.unlock();
}

void ScriptPluginsSynchronizer::enteringDoDialog()
{
	m_pImpl->dialogMutex.lock();
}

void ScriptPluginsSynchronizer::finishedEndDialog()
{
	m_pImpl->dialogMutex.unlock();
}
