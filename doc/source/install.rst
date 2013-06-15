.. _install:

Installing pylaunchy
=====================

pylaunchy can be installed in several ways:

#. Using an installer
#. Using a binary package
#. Using a source package

Requirements
--------------
* Download and install Python 2.7 from 
  `www.python.org <http://www.python.org>`_ .
* Make sure you have Launchy 2.5 and above

Using the installer (PyLaunchy-|version|.exe)
----------------------------------------------
Download the latest setup file from the Downloads page, then run it and follow
the instructions.

**Note:** 
The installer only unpacks the files in the Launchy directory and creates
an uninstaller. If this is not desirable, you can use the manual method described 
below.

Manual/portable installation
-------------------------------------------------------
#. Download the installer (PyLaunchy-|version|.exe) and  
   `Inno Setup Unpacker <http://sourceforge.net/projects/innounp/>`_.
#. From command line, run -

       innounp -x PyLaunchy-|version|.exe
       
#. Copy the contents of the generated {app} directory to the **root** Launchy
   directory. For example, if Launchy was installed in
   ``C:\Program Files\Launchy``, copy the files to 
   ``C:\Program Files\Launchy``.
#. After unpacking, the *boost_python-vc80-mt-1_35.dll* file should in the
   same directory as *Launchy.exe*.
   
Using the source package (PyLaunchy-src-|version|.zip)
-------------------------------------------------------
See the Building.txt file in the ZIP file.
