#ifndef SimpleSettings_H_
#define SimpleSettings_H_

#include <QString.h>
#include <QVariant.h>

/** Simplified interface for QSettings
 */
class SimpleSettings {
public:
	virtual bool contains(const QString &key) const = 0;
    virtual void setValue(const QString &key, const QVariant &value) = 0;
    virtual QVariant value(const QString &key, const QVariant &defaultValue = QVariant()) const = 0;
};

#endif // SimpleSettings_H_
