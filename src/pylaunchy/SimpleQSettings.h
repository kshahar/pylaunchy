#ifndef SimpleQSettings_H_
#define SimpleQSettings_H_

#include "SimpleSettings.h"
#include <QSettings.h>

/** Delegates all calls to QSettings object
 */
class SimpleQSettings: public SimpleSettings {
public:
	SimpleQSettings(QSettings& settings): m_settings(settings) {}

	virtual bool contains(const QString &key) const
	{
		return m_settings.contains(key);
	}

    virtual void setValue(const QString &key, const QVariant &value)
	{
		m_settings.setValue(key, value);
	}

    virtual QVariant value(const QString &key, const QVariant &defaultValue = QVariant()) const
	{
		return m_settings.value(key, defaultValue);
	}

private:
	QSettings& m_settings;
};

#endif // SimpleQSettings_H_
