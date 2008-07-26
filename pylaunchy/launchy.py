
class Plugin:
	def init(self):
		pass
		
	def getID(self):
		"""
		Asks the Plugin for its ID Number.

		Launchy needs an unsigned int identification value for each loaded plugin. You supply your own here. Typically, this is the result of hashing a string, as shown in the example below.

		Warning: 
		Because we're hashing strings to integers.. it is theoretically possible that two plugin names will collide to the same plugin id.
		
		Example: 
		def getID(self):
			return launchy.hash("TestPlugin")
		"""
		pass
	
	def getName(self):
		pass
		
	def getIcon(self):
		pass
		
	def getLabels(self, inputDataList):
		"""
		Asks the plugin if it would like to apply a label to the current search query.

		It is sometimes useful to label user queries with plugin-defined tags. For instance, the weby plugin will tag input that contains "www" or ".com" or ".net" with the hash value of the string "HASH_WEBSITE". Then, other plugins that see the query can know that the current search is for a website.

		The InputData class stores the current user's query. It is in a List structure because each time "tab" is pressed by the user a new InputData is formed and appended to the list. In other words, if the user typed "google <tab> this is my query" then wParam would represent a list of 2 InputData classes, with the first representing "google", and the second, "this is my query". Each InputData can be tagged individually.

		Warning: This is called each time the user changes a character in his or her query, so make sure it's fast.
		
		Example: 
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
		"""
		pass
		
	def getResults(self, inputDataList, resultsList):
		pass
		
	def getCatalog(self, resultsList):
		pass
		
	def launchItem(self, inputDataList, catItem):
		pass
