#ifndef Precompiled_H_
#define Precompiled_H_

#if _MSC_VER >= 1300
#pragma warning (disable : 4100)
#endif

#include "pylaunchy_ezlogger_adapter.h"

// Python and Boost.Python
#include <Python.h>
#include <boost/python.hpp>
#include <boost/python/call.hpp>
#include <boost/python/exec.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/import.hpp>
#include <boost/python/list.hpp>
#include <boost/python/wrapper.hpp>
#include <boost/python/with_custodian_and_ward.hpp>

// Qt
#include <QApplication>
#include <QDir>
#include <QFile>
#include <QHash>
#include <QList>
#include <QMutex>
#include <QObject>
#include <QTemporaryFile>
#include <QtPlugin>

// Windows
#ifdef Q_WS_WIN
#include <windows.h>
#include <shlobj.h>
#include <tchar.h>
#endif

#endif // Precompiled_H_
