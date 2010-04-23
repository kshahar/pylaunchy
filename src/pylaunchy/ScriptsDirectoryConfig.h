#ifndef ScriptsDirectoryConfig_H_
#define ScriptsDirectoryConfig_H_

#include <QDir>
namespace qt_utils {
	class QSettingsWrapper;
}

class ScriptsDirectoryConfig {
public:
	void init(qt_utils::QSettingsWrapper& settings);
	
	const QDir& scriptsDirectory() const;
	
	void setApplicationDirPathForTesting(const QString& path);

protected:
	QDir determineScriptsDirectory(qt_utils::QSettingsWrapper& settings);
	QString applicationDirPath() const;

private:
	QDir m_scriptsDirectory;
	QString m_applicationDirPath;
};

#endif // ScriptsDirectoryConfig_H_
