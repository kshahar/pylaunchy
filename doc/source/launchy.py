"""
The launchy module provides the required classes and functions for developing a
Launchy plugin in Python.

- :class:`Plugin`, represents a Launchy Python plugin

- :class:`CatItem`, a catalog entry
- :class:`InputData`, a user query
- :class:`ResultsList`, a catalog entry
"""

__docformat__ = 'restructuredtext'

class CatItem:
    """
    CatItem
    """
    pass

class InputData:
    """
    InputData shows one segment (between tabs) of a user's query. 
    A user's query is typically represented by List<InputData> and 
    each element of the list represents a segment of the query.

    E.g. query = "google <tab> this is my search" will have 2 InputData segments 
    in the list. One for "google" and one for "this is my search" 

    .. note:: This class cannot be created from Python, you can only get an 
             instance of it.
    """
                
    def setLabel(self, labelHashId):
        """
        Apply a label to this query segment. 
        """
        pass
      
    def hasLabel(self, labelHashId):
        """	
        Check if it has the given label applied to it.
        """
        pass
   
    def setID(self, hashId):
        """
        Set the id of this query.
        
        This can be used to override the owner of the selected catalog item, 
        so that no matter what item is chosen from the catalog, the given 
        plugin will be the one to execute it.
        """
        pass      
   
    def getId(self):
        """
        Returns the current owner id of the query. 
        """
        pass

    def getText(self):
        """
        Get the text of the query segment. 
        """
        pass
        
    def setText(self, text):
        """
        Set the text of the query segment.
        """
        pass
   
    def getTopResult(self):
        """
        :rtype: :class:`CatItem`
        
        Get a the best catalog match for this segment of the query.
        """
        pass
   
    def setTopResult(self, catItem):
        """
        :param catItem: :class:`CatItem`
        
        Change the best catalog match for this segment. 
        """
        pass

class ResultsList:
    """
    ResultsList holds the catalog items that are relevent to a search query.
    
    Plugins that want to add new catalog items for a search query should use
    this class - ::
    
       def getResults(self, inputDataList, resultsList):
          resultsList.push_back( launchy.CatItem(text,
             "PySimple: " + text,
             self.getID(), self.getIcon()) )
    
    **Implemenatation:** This is a thin wrapper for QList<CatItem>
    
    .. note:: This class cannot be created from Python, you can only get an 
              instance of it.
    """

    def append(self, catItem):
        """
        Add a catalog item to the end of the results list.
        """
        pass

    def prepend(self, catItem):
        """
        Add a catalog item to the begining of the results list.
        """
        pass

    def push_back(self, catItem):
        """
        Add a catalog item to the end of the results list. 
        """
        pass

    def push_front(self, catItem):
        """
        Add a catalog item to the begining of the results list.
        """
        pass


class Plugin:
    """
    This class represents a Launchy Python plugin. By combining a script that
    has a class that inherits from :class:`Plugin` and the :mod:`launchy` 
    module itself, Python scripts can be added to Launchy as real plugins.
    
    Every plugin needs to be registered using the :func:`registerPlugin` 
    function::
    
        import launchy
        class MyPlugin(launchy.Plugin):
            pass # Real plugin code should come here
        launchy.registerPlugin( MyPlugin )
    
    The Plugin interface consists of the following functions:
    
    Basic functions:
     - :meth:`Plugin.init`
     - :meth:`Plugin.getID`
     - :meth:`Plugin.getName`
    
    Functions that operate on Launchy's Catalog.
     - :meth:`Plugin.getCatalog`
     - :meth:`Plugin.getLabels`
     - :meth:`Plugin.getResults`
     - :meth:`Plugin.launchItem`
    
    GUI functions (warning: still experminetal):
     - :meth:`Plugin.hasDialog`
     - :meth:`Plugin.doDialog`
     - :meth:`Plugin.endDialog`
    
    Event functions:
     - :meth:`Plugin.launchyShow`
     - :meth:`Plugin.launchyHide`
    
    """
    def init(self):
        """
        This message informs the plugin that it's being loaded.
        
        This is a good time to do any initialization work.
        """
        pass
        
    def getID(self):
        """
        :rtype: int
        
        Asks the Plugin for its ID Number.
        
        Launchy needs an unsigned int identification value for each loaded plugin. You supply your own here. Typically, this is the result of hashing a string, as shown in the example below.
                
        Example:: 
        
            def getID(self):
                return launchy.hash("TestPlugin")
        
        .. note:: Warning - Because we're hashing strings to integers.. it is theoretically possible that two plugin names will collide to the same plugin id.
        """
        pass

    def getName(self):
        """
        :rtype: string
        
        Asks the plugin for its string name. 
        """
        pass
    
    def getLabels(self, inputDataList):
        """
        :param inputDataList: User's search query
        :type inputDataList: List of :class:`InputData`
        
        Asks the plugin if it would like to apply a label to the current search query.

        It is sometimes useful to label user queries with plugin-defined tags. For instance, the weby plugin will tag input that contains "www" or ".com" or ".net" with the hash value of the string "HASH_WEBSITE". Then, other plugins that see the query can know that the current search is for a website.

        The :class:`InputData` class stores the current user's query. It is in a List structure because each time "tab" is pressed by the user a new :class:`InputData` is formed and appended to the list. In other words, if the user typed "google <tab> this is my query" then *inputDataList* would represent a list of 2 :class:`InputData` classes, with the first representing "google", and the second, "this is my query". Each :class:`InputData` can be tagged individually.
       
        Example::
        
            def getLabels(self, inputDataList):
               if len(inputDataList) > -1:
                   return

               # Apply a "website" label if we think it's a website
               text = inputDataList[-1].getText();

               if text.find("http://") > -1:
                   inputDataList[-1].setLabel(HASH_WEBSITE);
               elif text.find("https://") > -1:
                   inputDataList[-1].setLabel(HASH_WEBSITE);
               elif text.find(".com") > -1: 
                   inputDataList[-1].setLabel(HASH_WEBSITE);
               elif text.find(".net") > -1:
                   inputDataList[-1].setLabel(HASH_WEBSITE);
               elif text.find(".org") > -1:
                   inputDataList[-1].setLabel(HASH_WEBSITE);
               elif text.find("www.") > -1:
                   inputDataList[-1].setLabel(HASH_WEBSITE);  
        
        .. note:: Warning - This is called each time the user changes a character in his or her query, so make sure it's fast. 
        """
        pass
        
    def getResults(self, inputDataList, resultsList):
        """
        Asks the plugin for any results to a query.

        If your plugin returns catalog results on the fly to a query (e.g. a website query for weby or a calculator result), then this is the place to do so. The existing results are stored in a :class:`ResultsList` object, which is a :class:`CatItem`'s (short for Catalog Items) list. You can append your own results to it.
        """
        pass
        
    def getCatalog(self, resultsList):
        """
        :param resultsList: A :class:`ResultsList` object to append your new 
                entries to (these will be copied over to the primary catalog).
        
        Asks the plugin for a static catalog to be added to the primary 
        catalog. Some plugins will add permanent entries to Launchy's 
        primary catalog (until the catalog is rebuilt).
        
        For example, the pygo-y plugin adds two items to the catalog: 
        "Go" and "Focus". These will be used later on to determine that
        the user is typing a pygo-y query.
        
        The following code is from pygo-y::
        
            def getCatalog(self, resultsList):
                resultsList.push_back( launchy.CatItem( 
                    "Go.go-y", "Go", self.getID(), self.getIcon() ) )
                resultsList.push_back( launchy.CatItem( 
                    "Focus.go-y", "Focus", self.getID(), self.getIcon() ) )
        
        """
        pass
        
    def launchItem(self, inputDataList, catItem):
        """
        :param inputDataList: User's search query
        :type inputDataList: List of :class:`InputData`
        :param catItem: The user selected catalog item
        :type catItem: :class:`CatItem`
        
        instructs the plugin that one of its own catalog items was selected by 
        the user and should now be executed.

        If the plugin adds items to the catalog via :meth:`getResults` 
        or :meth:`getCatalog` and one of those items is selected by the user, 
        then it is up to the plugin to execute it when the user presses "enter". 
        This is where you perform the action. 
        
        The following code is from pygo-y::
        
            def launchItem(self, inputDataList, catItemOrig):
                catItem = inputDataList[-1].getTopResult()
                for window in self.topLevelWindows:
                    if catItem.shortName == window[1]:
                        self._goToWindow(window[0])
                        break
        
        Notes for the code above:
         1. At first, the function gets the user selected window name by 
            calling :meth:`InputData.getTopResult`.
         2. Then it searches the window name by using ``catItem.shortName`` 
            that was created in pygo-y's :meth:`getResults`.
         3. When the window is found, the ``self._goToWindow()`` method 
            does the actual work of activating the window.
        
        """
        pass
        
    def hasDialog(self):
        """
        Asks the plugin if it has a dialog to display in the 
        options menu. 
       
        Return ``true`` if the plugin has a dialog, or ``false`` otherwise.
        """
        pass

    def doDialog(self, parentWidget):
        """
        :param parentWidget: The parent widget of all plugin widgets. 
            Call ``wrapinstance`` to use it.
        :type parentWidget: ``void*``
        
        :rtype: ``void*`` - The result of ``unwrapinstance( myPluginWidget )``
        
        Tells the plugin that it's time to show its user interface. The function 
        should create the widget and return it.
        
        * The plugin is passed a raw C++ pointer. It should be converted to 
          QWidget by the user with SIP function ``wrapinstance``.
        * SIP documentation can be found 
          `here <http://www.riverbankcomputing.co.uk/static/Docs/sip4/sipref.html>`_.
        * The creation of plugin widgets should be done with PyQt4.
        * PyQt4 Documentation and Tutorial are available from
          `PythonInfo Wiki <http://wiki.python.org/moin/PyQt4>`_.
        
        Example::
        
            from PyQt4 import QtGui
            
            class MyPlugin(launchy.Plugin):
            # ...
                def doDialog(self, parentWidgetPtr):
                    # Get the real QWidget
                    parentWidget = wrapinstance(parentWidgetPtr, QtGui.QWidget)
                    
                    # self.widget was initialized to None
                    if self.widget: 
                        self.widget.show()
                    
                    # MyPluginWidget inherits from QtGui.QWidget
                    self.widget = MyPluginWidget(parentWidget)
                    
                    return unwrapinstance(self.widget)
        
        .. warning:: Usage of this function is considered experimental.
        """
        pass
    
    def endDialog(self, accept):
        """
        :param accept: Whether the plugin should accept changes made by the 
            user while the dialog was open 
        :type accept: bool
        
        Informs the plugin that it should close its dialog. 
        """
        pass
    
    def launchyShow(self):
        """
        This message informs the plugin that Launchy is now visible on the screen. 
        """
        pass
    
    def launchyHide(self):
        """
        This message informs the plugin that Launchy is no longer visible 
        on the screen. 
        
        Note: this function will not be called if another plugin function has 
        not returned yet (e.g. Launchy is hidden in the middle of 
        :meth:`launchItem`).
        """
        pass
