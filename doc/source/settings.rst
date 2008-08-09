.. _settings:

Storing and retrieving Settings
================================

Settings in PyLaunchy are handled through an exported `QSettings <http://www.riverbankcomputing.co.uk/static/Docs/PyQt4/html/qsettings.html>`_ object.

The ``settings`` object is availible through ``launchy.settings`` and is shared
amongst all Launchy plugins (even non-python ones).

Usage example - ::

   # ...
   def init(self):
       settings = launchy.settings

The ``launchy.settings`` object is a QSettings object from PyQt4.QtCore. 
For more information, see the `QSettings 
<http://www.riverbankcomputing.co.uk/static/Docs/PyQt4/html/qsettings.html>`_ 
reference manual.