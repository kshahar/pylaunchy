#include "Precompiled.h"
#include "QSettingsWrapper.h"
#include <QSettings>

namespace qt_utils {

QSettingsWrapper::QSettingsWrapper(): 
m_pSettings(0)
{
}

void QSettingsWrapper::setQSettings(QSettings* pSettings)
{
	m_pSettings = pSettings;
}

QSettings* QSettingsWrapper::getQSettings() const
{
	return m_pSettings;
}

bool QSettingsWrapper::contains(const QString &key) const
{
	if (m_pSettings) {
		return m_pSettings->contains(key);
	}
	else {
		return false;
	}
}

QString QSettingsWrapper::fileName() const
{
	if (m_pSettings) {
		return m_pSettings->fileName();
	}
	else {
		return QString::null;
	}
}

void QSettingsWrapper::setValue(const QString &key, const QVariant &value)
{
	if (m_pSettings) {
		m_pSettings->setValue(key, value);
	}
}

QVariant QSettingsWrapper::value(const QString &key, const QVariant& defaultValue) const
{
	if (m_pSettings) {
		return m_pSettings->value(key, defaultValue);
	}
	else {
		return defaultValue;
	}
}

} // qt_utils