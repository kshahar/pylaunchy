#ifndef PythonInitializer_H_
#define PythonInitializer_H_

class PythonInitializer {
public:
	//! Main init function, calls all the other functions in the correct order
	void initPython(void* pQSettingsObject);

private:
	bool initPythonSystem();

	void initPythonBindings();

	/** Puts the QSettings object of Launchy in the python module.
		
		After calling this function, the object can be accessed by using 
		launchy.__settings. It should be converted to a PyQt QSettings object
		by using the following SIP/PyQt code:
\code
from sip import wrapinstance, unwrapinstance
from PyQt4 import QtCore
launchy.settings = wrapinstance(launchy.__settings, QtCore.QSettings)
\endcode
	*/
	void setQSettingsObject(void* pQSettingsObject);

	void executePythonInitScript();
};

#endif // PythonInitializer_H_