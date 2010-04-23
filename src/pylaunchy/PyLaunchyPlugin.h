#ifndef PyLaunchyPlugin_H_
#define PyLaunchyPlugin_H_

#include "launchy/plugin_interface.h"
#include <memory>

class PyLaunchyPlugin : public QObject, public PluginInterface
{
	Q_OBJECT
	Q_INTERFACES(PluginInterface)

public:
	/** Interface for Launchy */
	//@{
	PyLaunchyPlugin();
	~PyLaunchyPlugin();
	virtual int msg(int msgId, void* wParam = NULL, void* lParam = NULL); 
	//@}

private:
	struct PrivateImpl;
	std::auto_ptr<PrivateImpl> m_pImpl;

	void init();
};

#endif //PyLaunchyPlugin_H_