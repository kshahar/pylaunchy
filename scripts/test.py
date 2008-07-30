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
import sys,os

class TestPlugin(launchy.Plugin):
	def init(self):
		self.icon = os.path.join(launchy.getIconsPath(), "python.ico")
		self.hash = launchy.hash(self.getName())
		
	def getID(self):
		return self.hash
	
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
		try:
			print "WHOOO"
			print catItem.fullPath(), catItem.shortName(), catItem.lowName(), catItem.icon(), catItem.usage(), catItem.id()
		except Exception, inst:
			print type(inst)     # the exception instance
			print inst.args      # arguments stored in .args
			print inst           # __str__ allows args to printed directly	
		for s in [sys.stdout, sys.stderr]: s.flush()

try:
	testPlugin = TestPlugin()
	launchy.addPlugin(TestPlugin())
except Exception, inst:
	print inst           # __str__ allows args to printed directly	
for s in [sys.stdout, sys.stderr]: s.flush()	