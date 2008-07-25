#pragma once

#include <Python.h>
#include <boost/python.hpp>
#include <boost/python/call.hpp>
#include <boost/python/exec.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/import.hpp>
#include <boost/python/list.hpp>
#include <boost/python/wrapper.hpp>
#include <boost/python/with_custodian_and_ward.hpp>

#include <QHash>
#include <QUrl>
#include <QFile>
#include <QRegExp>
#include <QTextCodec>
#include <QTextStream>

#include <QtGui>
#include <QTextEdit>

#ifdef Q_WS_WIN
#include <windows.h>
#include <shlobj.h>
#include <tchar.h>
#endif
