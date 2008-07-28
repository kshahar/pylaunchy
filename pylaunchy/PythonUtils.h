#ifndef PythonUtils_H_
#define PythonUtils_H_

#define GUARDED_CALL_TO_PYTHON(expr) do { \
		try { \
			expr \
		} \
		catch(boost::python::error_already_set const &) { \
			PyErr_Print(); \
			PyErr_Clear(); \
			LOG_WARN("Error in Python script, see stderr.txt file for more details"); \
		} \
	} while (0); \
//

#endif