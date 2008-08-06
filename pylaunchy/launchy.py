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
    def init(self):
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
        """
        pass
        
    def getIcon(self):
        """
        :rtype: string
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
        pass
        
    def launchItem(self, inputDataList, catItem):
        pass
