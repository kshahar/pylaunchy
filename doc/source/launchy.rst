:mod:`launchy` --- Python plugin API for Launchy
===================================================

.. module:: launchy
   :synopsis: Python plugin API for Launchy.


This module provides the required classes and functions for developing a
Launchy plugin in Python.
 
InputData class
----------------

.. class:: InputData

   InputData shows one segment (between tabs) of a user's query A user's query
   is typically represented by List<InputData> and each element of the list 
   represents a segment of the query.

   E.g. query = "google <tab> this is my search" will have 2 InputData segments 
   in the list. One for "google" and one for "this is my search" 

   .. note:: This class cannot be created from Python, you can only get an 
             instance of it.
			    
.. method:: InputData.setLabel(labelHashId)

   Apply a label to this query segment. 
      
.. method:: InputData.hasLabel(labelHashId)

   Check if it has the given label applied to it.
         
.. method:: InputData.setID(hashId)

   Set the id of this query.
   
   This can be used to override the owner of the selected catalog item, so that
   no matter what item is chosen from the catalog, the given plugin will be the
   one to execute it.
   
.. method:: InputData.getId()

   Returns the current owner id of the query. 
   
.. method:: InputData.getText()

   Get the text of the query segment. 
   
.. method:: InputData.setText()

   Set the text of the query segment.

.. method:: InputData.getTopResult()

   Get a the best catalog match for this segment of the query.
   
.. method:: InputData.setTopResult

   Change the best catalog match for this segment. 
   