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

#import rpdb2; rpdb2.start_embedded_debugger("password")
import launchy
import sys, os

import subprocess
from subprocess import Popen, PIPE

class PyVerby(launchy.Plugin):
	def __init__(self):
		launchy.Plugin.__init__(self)
		self.icon = os.path.join(launchy.getIconsPath(), "pysimple.png")
		self.hash = launchy.hash(self.getName())
		self.labelHash = launchy.hash("pyverby")

	def init(self):
		pass
		
	def getID(self):
		return self.hash
	
	def getName(self):
		return "PyVerby"
		
	def getIcon(self):
		return self.icon
		
	def getLabels(self, inputDataList):
		pass
		
	def getResults(self, inputDataList, resultsList):
		if len(inputDataList) < 1:
			return
		
		text = inputDataList[0].getText()
		isVerbyQuery = ( text[-4:-1] == "   " )
		print "%s##%s##%s" % (text, text[-4:-1], isVerbyQuery)
		if not isVerbyQuery:
			return
		
		text = text[:-4]
		isFileOrDir = os.path.isdir(text) or os.path.isfile(text)
		print "%s##%s" % (text, isFileOrDir)
		if not isFileOrDir:
			return
		
		runmenuApp = 'C:\\Program Files\\Launchy\\plugins\\python\\runmenu\\runmenu.exe'
		runmenu = Popen([runmenuApp, "/list", text], stdout=PIPE, startupinfo=self.__startupinfo)
		output = runmenu.stdout.read()
		
		splitted = output.split("\r\n")		
		for command in splitted:
			if command == "":
				continue
				
			verbIdx = command.rfind("(Verb:")
			if verbIdx > -1:
				commandToExec = command[:verbIdx]
			else:
				commandToExec = command
				
			resultsList.append( launchy.CatItem(text, commandToExec, self.getID(), self.getIcon() ))
		
	def getCatalog(self, resultsList):
		pass
		
	def launchItem(self, inputDataList, catItemOrig):
		catItem = inputDataList[-1].getTopResult()
		print catItem.fullPath, catItem.shortName
		runmenuApp = 'C:\\Program Files\\Launchy\\plugins\\python\\runmenu\\runmenu.exe'
		runmenu = Popen([runmenuApp, '/exec:%s' % catItem.shortName, catItem.fullPath], stdout=PIPE, startupinfo=self.__startupinfo)
		
		print runmenu.stdout.read()
		
	def launchyShow(self):
		pass
			
	def launchyHide(self):
		pass
	
	__startupinfo = subprocess.STARTUPINFO()
	__startupinfo.dwFlags |= subprocess.STARTF_USESHOWWINDOW
	__startupinfo.wShowWindow = subprocess.SW_HIDE


launchy.registerPlugin(PyVerby)
