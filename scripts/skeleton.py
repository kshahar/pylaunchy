# Copyright (c) 2008 Shahar Kosti
#
# This program is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation; either version 2 of the License, or (at your option) any later
# version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with
# this program; if not, write to the Free Software Foundation, Inc.,
# 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

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
		print "You have chosen to launch " + catItem.fullPath
			
	def launchyShow(self):
		pass
			
	def launchyHide(self):
		pass

launchy.addPlugin(SkeletonPlugin())
