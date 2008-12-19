#ifndef ScriptsDirectoryConfig_H_
#define ScriptsDirectoryConfig_H_

#include <QDir>
class SimpleSettings;

class ScriptsDirectoryConfig {
public:
	void init(SimpleSettings& settings);
	
	const QDir& scriptsDirectory() const;
	
	void setApplicationDirPathForTesting(const QString& path);

protected:
	QDir determineScriptsDirectory(SimpleSettings& settings);
	QString applicationDirPath() const;

private:
	QDir m_scriptsDirectory;
	QString m_applicationDirPath;
};

#endif // ScriptsDirectoryConfig_H_
