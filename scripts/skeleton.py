import launchy
import sys, os

class SkeletonPlugin(launchy.Plugin):
	def init(self):
		self.icon = os.path.join(launchy.getIconsPath(), "python.ico")
		self.hash = launchy.hash(self.getName())
		
	def getID(self):
		return self.hash
	
	def getName(self):
		return "SkeletonPlugin"
		
	def getIcon(self):
		return self.icon
		
	def getLabels(self, inputDataList):
		for inputData in inputDataList:
			print inputData.getText()
		
	def getResults(self, inputDataList, resultsList):
		text = inputDataList[0].getText()
		resultsList.append( launchy.CatItem(text, "From python: " + text, self.hash, self.icon) )
		
	def getCatalog(self, resultsList):
		pass
		
	def launchItem(self, inputDataList, catItem):
		print "You have chosen to launch " + catItem.fullPath()
			
	def launchyShow(self):
		pass
			
	def launchyHide(self):
		pass

launchy.addPlugin(SkeletonPlugin())
