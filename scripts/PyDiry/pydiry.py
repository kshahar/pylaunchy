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

import glob
from CaselessDict import CaselessDict
from future_ntpath import expandvars

from PyQt4 import QtCore, QtGui
from PyQt4.QtCore import QVariant
from sip import wrapinstance, unwrapinstance

# http://www.doughellmann.com/PyMOTW/glob/glob.html

class PyDiry(launchy.Plugin):
	__version__ = "1.0"
	
	def __init__(self):
		launchy.Plugin.__init__(self)
		self.icon = os.path.join(launchy.getIconsPath(), "pydiry.ico")
		self.hash = launchy.hash(self.getName())
		self.labelHash = launchy.hash("pydiry")
		
		self.dirs = CaselessDict()
	
	def init(self):
		self.__readConfig()
		sys.path.append( os.path.join( launchy.getLibPath(), 'PyDiry' ) )
		pass
	
	def getID(self):
		return self.hash
	
	def getName(self):
		return "PyDiry"
	
	def getIcon(self):
		return self.icon
	
	def getLabels(self, inputDataList):
		pass
	
	def getResults(self, inputDataList, resultsList):
		if len(inputDataList) != 2:
			return
		
		firstText = inputDataList[0].getText()
		if not self.dirs.has_key(firstText):
			return
		
		path = self.dirs[firstText]
		query = inputDataList[1].getText()
		
		if query == '':
			# Default query is '*'
			query = '*'
		elif not query.startswith('*') and not query.endswith('*'):
			# Add * at both sides to ease searching
			query = '*%s*' % query
		
		pathContents = glob.glob(os.path.join(path, query))
		
		for itemPath in pathContents:
			try:
				shortName = os.path.split(itemPath)[1]
			except:
				shortName = itemPath
			resultsList.append( launchy.CatItem(itemPath, shortName, self.getID(), itemPath ))
		
	def getCatalog(self, resultsList):
		for name,path in self.dirs.items():
			resultsList.push_back( launchy.CatItem( name + ".pydiry", name, self.getID(), self.getIcon() ) )
		
	def launchItem(self, inputDataList, catItemOrig):
		pass
		
	def hasDialog(self):
		return True
		
	def doDialog(self, parentWidgetPtr):
		parentWidget = wrapinstance(parentWidgetPtr, QtGui.QWidget)
		
		import PyDiryGui
		self.widget = PyDiryGui.PyDiryUi(parentWidget)
		self.widget.show()
			
		return unwrapinstance(self.widget)
		
	def endDialog(self, accept):
		self.widget.hide()
		if accept:
			self.widget.writeSettings()
			self.__readConfig()
		
		del self.widget
		self.widget = None
	
	def __readConfig(self):
		settings = launchy.settings
		
		# Test if the settings file has PyDiry configuration
		version = settings.value("PyDiry/version", QVariant("0.0")).toString()
		print_debug("PyDiry version: " + version)
		if version == "0.0":
			settings.beginWriteArray("PyDiry/dirs")
			settings.setArrayIndex(0)
			settings.setValue("name", QVariant("My Documents"))
			settings.setValue("path", QVariant("%USERPROFILE%\\My Documents"))
			settings.endArray()
		
		# Set our version
		settings.setValue("PyDiry/version", QVariant(self.__version__))
		
		self.dirs.clear()
		
		# Read directories from the settings file
		size = settings.beginReadArray("PyDiry/dirs")
		for i in range(0, size):
			settings.setArrayIndex(i);
			name = unicode(settings.value("name").toString())
			path = unicode(settings.value("path").toString())
			self.dirs[name] = expandvars(path)
		settings.endArray()

launchy.registerPlugin(PyDiry)
