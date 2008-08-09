.. _debugging: 

Debugging scripts
==================

PyLaunchy is an embedded Python environment, which means you have no 
console output. In general, there are two ways to debug:

1. Logging with ``print`` statements or with the `Python logging module 
   <http://docs.python.org/lib/module-logging.html>`_.
   For example, the following script will print a line which can be seen in 
   ``plugins/python/stdout.txt``::

       import launchy  
       print "I was printed from python!"  

2. Using Winpdb and `Embedded Debugging <http://winpdb.org/?page_id=9>`_.
   For example, the following script will halt Launchy and wait for 
   Winpdb to attach::
   
      import rpdb2; rpdb2.start_embedded_debugger("mypassword")  
      import launchy  