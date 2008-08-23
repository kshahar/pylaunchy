.. _settings:

Storing and retrieving Settings
================================

Settings in PyLaunchy are handled through an exported QSettings 
(see below) object.

The ``settings`` object is availible through ``launchy.settings`` and is shared
amongst all Launchy plugins (even non-python ones).

``launchy.settings`` is a QSettings object from PyQt4.QtCore. 
For more information, see the reference manual.

The examples in this page are taken from the :ref:`PyWebIndex <pywebindex>` plugin.

.. seealso::

   `QSettings <http://www.riverbankcomputing.co.uk/static/Docs/PyQt4/html/qsettings.html>`_
      Documentation of the QSettings class from PyQt4.

Reading a value
----------------
Read the value of ``pagesHash`` from the ``[PyWebIndex]`` section in the
settings file and convert it to string::

   settings = launchy.settings
   pagesHash = settings.value("PyWebIndex/pagesHash").toString()

Storing a value
----------------
Save a the value of ``__version__`` (string variable) to the ``[PyWebIndex]`` 
section in the settings file::

   settings = launchy.settings
   settings.setValue("PyWebIndex/version", QVariant(self.__version__))

Note the usage of ``QVariant``, QSettings works with objects of this type, so 
it should be used to convert values from Python to QT or vice versa.

Reading values from an array
------------------------------
Read all values from the ``masterPages`` array in the ``[PyWebIndex]`` section
into a list of tuples::

   masterPages = []
   size = settings.beginReadArray("PyWebIndex/masterPages")
   for i in range(0, size):
       settings.setArrayIndex(i);
       masterPages.append( 
          ( settings.value("name").toString(),
            settings.value("url").toString() )
       )
   settings.endArray()
   
   # masterPages now contains tuples of (name, url)

Storing values in an array
------------------------------
The following saves items from a QTableWidget to an array::

   settings.remove("PyWebIndex/masterPages")
   settings.beginWriteArray("PyWebIndex/masterPages")
   for i in range(0, table.rowCount()):
       settings.setArrayIndex(i)
       settings.setValue("name", QVariant(table.item(i,0).text()))
       settings.setValue("url", QVariant(table.item(i,1).text()))
   settings.endArray()

