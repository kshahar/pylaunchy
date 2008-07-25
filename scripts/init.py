import sys, os
import launchy
os.chdir('plugins/python')
sys.stdout = open('stdout.txt','w')
sys.stderr = open('stderr.txt','w')
print "Launchy Python plug-in is up and running"

sys.stdout.flush()
sys.stderr.flush()

class TestPlugin(launchy.Plugin):
	def init(self):
		self.icon = os.path.join(launchy.getIconsPath(), "python.ico")
		self.hash = launchy.hash(self.getName())
		
	def getID(self):
		return 999
	
	def getName(self):
		return "TestPythonPlugin"
		
	def getIcon(self):
		return self.icon
		
	def addLabels(self, inputDataList):
		try:
			for inputData in inputDataList:
				print inputData.getText()
		except Exception, inst:
			print type(inst)     # the exception instance
			print inst.args      # arguments stored in .args
			print inst           # __str__ allows args to printed directly	
		for s in [sys.stdout, sys.stderr]: s.flush()
		
	def addResults(self, inputDataList, resultsList):
		try:
			print launchy.getIconsPath()
			resultsList.append( launchy.CatItem("bla bla", inputDataList[0].getText(), self.hash, self.icon) )
			#launchy.getIconsPath()+"
		except Exception, inst:
			print type(inst)     # the exception instance
			print inst.args      # arguments stored in .args
			print inst           # __str__ allows args to printed directly	
		for s in [sys.stdout, sys.stderr]: s.flush()
		
	def getCatalog(self, resultsList):
		pass
		
	def launchItem(self, inputDataList, catItem):
		print "WHOOOO", catItem.fullPath
		for s in [sys.stdout, sys.stderr]: s.flush()

t = TestPlugin()
print t

sys.stdout.flush()
sys.stderr.flush()	

def getPlugin():
	return t
	
# def getResults(inputData):
	# try:
		# print dir(inputData), inputData.getID,  inputData.getID()
	# except Exception, inst:
		# print type(inst)     # the exception instance
		# print inst.args      # arguments stored in .args
		# print inst           # __str__ allows args to printed directly
	# sys.stdout.flush()

# try:
	# import launchy
	# print "YEEEEEEEEEEESSSSSSSSSSSSSSS"
	# print launchy.add_five(5)
# except Exception, inst:
	# print type(inst)     # the exception instance
	# print inst.args      # arguments stored in .args
	# print inst           # __str__ allows args to printed directly
