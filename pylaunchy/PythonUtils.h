#ifndef PythonUtils_H_
#define PythonUtils_H_

inline void* voidPtrFromObject(boost::python::object result)
{
	PyObject* resultPtr = result.ptr();

	const bool isLong = 
		PyObject_IsInstance(resultPtr, (PyObject*)&PyLong_Type) ||
		PyObject_IsInstance(resultPtr, (PyObject*)&PyInt_Type);

	if (isLong) {
		return PyLong_AsVoidPtr(resultPtr);
	}
	else {
		return NULL;
	}
}

/** Call a python function and catch exceptions
 */
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

/** Export a custom converted type. Based on Boost.Python FAQ:
	"Why is my automatic to-python conversion not being found?"
 */
#define BOOST_PYTHON_EXPORT_CUSTOM_TYPE(name, variable) \
	.add_property(name, \
		make_getter(variable, return_value_policy<return_by_value>()), \
		make_setter(variable, return_value_policy<return_by_value>())) \
//

#endif