import launchy

class MySimplePlugin(launchy.Plugin):
	def __init__(self):
		launchy.Plugin.__init__(self)
		self.hash = launchy.hash("MySimplePlugin")
	
	def init(self):
		pass
		
	def getID(self):
		return self.hash

	def getName(self):
		return "MySimplePlugin"

	def getIcon(self):
 		return "no_icon_used_here.png"
		
	def getLabels(self, inputDataList):
		pass	
		
	def getResults(self, inputDataList, resultsList):
		# Take the text from the first input item and add a new
		# Catalog item with our plugin id
		text = inputDataList[0].getText()
		resultsList.push_back( launchy.CatItem(text,
			"MySimplePlugin: " + text,
			self.getID(), "no_icon_used_here.png") )
		
	def getCatalog(self, resultsList):
		pass

	def launchItem(self, inputDataList, catItemOrig):
		# The user chose our catalog item, print it	  
		catItem = inputDataList[-1].getTopResult()
		print "I was asked to launch: ", catItem.fullPath
		
launchy.registerPlugin(MySimplePlugin)