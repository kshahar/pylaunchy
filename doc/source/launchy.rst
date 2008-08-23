:mod:`launchy` module ---API for Launchy plugins
===================================================

.. note:: This document is heavily based on Josh Karlin's 
   `Launchy 2.0 Plugin API Documentation <http://www.launchy.net/api2.0/>`_,
   adapted to PyLaunchy and Python.

.. automodule:: launchy

Plugin interface
-----------------
 
.. autoclass:: Plugin
   :members: 

Functions
----------
.. autofunction:: registerPlugin
.. autofunction:: hash
.. autofunction:: getLaunchyPath
.. autofunction:: getScriptsPath
.. autofunction:: getIconsPath
.. autofunction:: runProgram
   
Classes
---------

CatItem
~~~~~~~~~
.. autoclass:: CatItem
   :members:
   
InputData
~~~~~~~~~~
.. autoclass:: InputData
   :members:

ResultsList
~~~~~~~~~~~~
.. autoclass:: ResultsList
   :members:
