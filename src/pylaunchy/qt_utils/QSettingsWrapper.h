#ifndef QSettingsWrapper_H_
#define QSettingsWrapper_H_

#include <QString.h>
#include <QVariant.h>
class QSettings;

namespace qt_utils {

/** Provides a simple interface for QSettings and allows easy testing of 
	classes	which require it.
	Basically, it just delegates all calls to a QSettings object.
 */
class QSettingsWrapper {
public:
	QSettingsWrapper();
	
	//! Be sure to call this function before passing it to a code
	//! that needs to read/write settings.
	virtual void setQSettings(QSettings* pSettings);

	virtual QSettings* getQSettings() const;

	virtual bool contains(const QString &key) const;

	virtual QString fileName() const;

    virtual void setValue(const QString &key, const QVariant &value);

    virtual QVariant value(const QString &key, const QVariant &defaultValue = QVariant()) const;

private:
	QSettings* m_pSettings;
};

}

#endif