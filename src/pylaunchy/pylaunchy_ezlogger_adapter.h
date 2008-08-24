#ifndef PyLaunchy_Log_H_
#define PyLaunchy_Log_H_

#define EZLOGGER_OUTPUT_FILENAME "PyLaunchy.log"
#define EZLOGGER_REPLACE_EXISTING_LOGFILE_

#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#endif //_WIN32
#include <ezlogger_headers.hpp>

#define LEVELS_OBJECT(severity) axter::levels(axter::log_default_verbosity_level, severity)

#define LOG_FATAL EZLOGGERVLPRINT(LEVELS_OBJECT(axter::fatal))
#define LOG_ERROR EZLOGGERVLPRINT(LEVELS_OBJECT(axter::error))
#define LOG_WARN EZLOGGERVLPRINT(LEVELS_OBJECT(axter::warn))
#define LOG_STATUS EZLOGGERVLPRINT(LEVELS_OBJECT(axter::status))
#define LOG_INFO EZLOGGERVLPRINT(LEVELS_OBJECT(axter::info))
#define LOG_DEBUG EZLOGGERVLPRINT(LEVELS_OBJECT(axter::debug))

#define LOG_FUNCTRACK EZLOGGERVLFUNCTRACKER(axter::log_rarely)

#endif //PyLaunchy_Log_H_