#include "Precompiled.h"
#include "ScriptsDirectoryConfig.h"
#include "SimpleSettings.h"

void ScriptsDirectoryConfig::init(SimpleSettings& settings)
{
	m_scriptsDirectory = determineScriptsDirectory(settings);
}

const QDir& ScriptsDirectoryConfig::scriptsDirectory() const
{
	return m_scriptsDirectory;
}

void ScriptsDirectoryConfig::setApplicationDirPathForTesting(const QString& path)
{
	m_applicationDirPath = path;
}

QDir ScriptsDirectoryConfig::determineScriptsDirectory(SimpleSettings& settings)
{
	LOG_DEBUG("Reading scripts dir location from settings");
	const QString scriptsDirKey = "pylaunchy/scriptsDir";
	QString scriptsDirPath;
	if (settings.contains(scriptsDirKey)) {
		scriptsDirPath = settings.value(scriptsDirKey).toString();
	}
	else {
		LOG_DEBUG("No scriptsDir entry in settings file, creating it");
		scriptsDirPath = "plugins/python/";
		settings.setValue(scriptsDirKey, scriptsDirPath);
	}

	QDir scriptsDir(scriptsDirPath);
	if ( scriptsDir.isRelative() ) {
		LOG_DEBUG("Scripts dir is relative, prepending Launchy's path");
		scriptsDir = applicationDirPath() + "/" + scriptsDirPath;
	}
	else {
		LOG_DEBUG("Scripts dir is absolute");
	}

	LOG_INFO("Using scripts dir %s", (const char*)scriptsDir.path().toUtf8());

	/*if ( !scriptsDir.exists() ) {
		scriptsDir.mkpath(scriptsDirPath);
	}*/

	return scriptsDir;	
}

QString ScriptsDirectoryConfig::applicationDirPath() const
{
	if ( m_applicationDirPath.isEmpty() ) {
		return qApp->applicationDirPath();
	}
	else {
		return m_applicationDirPath;
	}
}
