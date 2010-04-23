#include <gtest/gtest.h>
#include "ScriptsDirectoryConfig.h"
#include "qt_utils/QSettingsWrapper.h"

static const char* CONFIG_scriptsDirIniKey = "pylaunchy/scriptsDir";

class QSettingsWrapperForTest: public qt_utils::QSettingsWrapper {
public:
	virtual bool contains(const QString &key) const
	{
		return m_key == key;
	}
    virtual void setValue(const QString &key, const QVariant &value)
	{
		m_key = key;
		m_value = value;
	}
    virtual QVariant value(const QString &key, const QVariant &defaultValue = QVariant()) const
	{
		if (m_key == key) {
			return m_value;
		}
		else {
			return defaultValue;
		}
	}

	QString m_key;
	QVariant m_value;
};

class ScriptsDirectoryConfigTest : public testing::Test {
protected:
	QSettingsWrapperForTest settings;
	ScriptsDirectoryConfig scriptsDirectoryConfig;

	virtual void SetUp() 
	{
		scriptsDirectoryConfig.setApplicationDirPathForTesting( "C:/" );
	}

	void initWithSettings()
	{
		scriptsDirectoryConfig.init(settings);
	}
};


TEST_F(ScriptsDirectoryConfigTest, Construction)
{
	// Testing is done in fixture
}

TEST_F(ScriptsDirectoryConfigTest, AbsolutePath)
{
	const char* absolutePath = "C:/Path/To/Dir";
	settings.setValue(CONFIG_scriptsDirIniKey, absolutePath);
	initWithSettings();
	ASSERT_TRUE( settings.contains(CONFIG_scriptsDirIniKey) );

	const QDir dir = scriptsDirectoryConfig.scriptsDirectory();
	EXPECT_STREQ( 
		absolutePath, 
		dir.path().toUtf8() );
	EXPECT_STREQ( 
		CONFIG_scriptsDirIniKey, 
		settings.m_key.toUtf8());
	EXPECT_STREQ(
		absolutePath,
		settings.m_value.toString().toUtf8());
}

TEST_F(ScriptsDirectoryConfigTest, RelativePath)
{
	const char* relativePath = "Path/To/Dir";
	settings.setValue(CONFIG_scriptsDirIniKey, relativePath);
	initWithSettings();
	ASSERT_TRUE( settings.contains(CONFIG_scriptsDirIniKey) );

	const QDir dir = scriptsDirectoryConfig.scriptsDirectory();
	EXPECT_STREQ( 
		(QString("C://") + QString(relativePath)).toUtf8(), 
		dir.path().toUtf8() );
	EXPECT_STREQ( 
		CONFIG_scriptsDirIniKey, 
		settings.m_key.toUtf8());
	EXPECT_STREQ(
		relativePath,
		settings.m_value.toString().toUtf8());
}

TEST_F(ScriptsDirectoryConfigTest, NotInSettings)
{
	initWithSettings();
	const QDir dir = scriptsDirectoryConfig.scriptsDirectory();
	EXPECT_STREQ( 
		"C://plugins/python", 
		dir.path().toUtf8() );
	EXPECT_STREQ( 
		CONFIG_scriptsDirIniKey, 
		settings.m_key.toUtf8());
	EXPECT_STREQ(
		"plugins/python/",
		settings.m_value.toString().toUtf8());
}
