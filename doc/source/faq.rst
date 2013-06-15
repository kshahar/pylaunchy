.. _faq: 

Frequently Asked Questions
========================================

.. contents::

How can I check if PyLaunchy is working?
------------------------------------------
* Bring up Launchy (Alt+Space) 
* Right-Click and choose **Options**
* Choose the **Plugins** tab
* Check if **PyLaunchy** is in the plugins list

Can I use PyLaunchy in Portable mode?
---------------------------------------
Sure. Download the PyLaunchy-bin-X.zip file (X is version number) and unpack
it by following the :ref:`install instructions <install>`.

PyLaunchy should work right after you restart Launchy.

**Note:** You might encouter problems if you previously installed Launchy in
regular mode, switched to Portable mode and moved the Launchy directory. See 
this `forum thread 
<http://sourceforge.net/forum/message.php?msg_id=5208806>`_ for more details.

Where are the Python plugins?
------------------------------
In ``<Launchy>\plugins\python``

How to check the log files?
----------------------------
Python output is availible in the following files:

* ``<Launchy>\plugins\python\stdout.txt``
* ``<Launchy>\plugins\python\stderr.txt``

Also, PyLaunchy writes log to the following file:

* ``<Launchy>\PyLaunchy.log``

I want to write plugins
--------------------------
Start here: :ref:`devdoc`.

Also, please post the plugin the forums and contact me so I can add a link to 
your plugin.

Can I use another language instead of Python?
----------------------------------------------
No, PyLaunchy is specfically developed to work with Python. However, PyLaunchy
added a plugin manager mechanism for Launchy plugin API that is language
independent. Moreover, some parts of the code are generic so they can be used 
to write a Launchy plugin that interfaces with another language 
(LUA, C#, Ruby, etc.).

Is there a Linux version?
---------------------------------------
PyLaunchy can be installed on Linux by building from the source code.
See the Building.txt file in the source package for more details.

Binary packages for all distributions are very welcome.
