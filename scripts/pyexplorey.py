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

#import rpdb2; rpdb2.start_embedded_debugger("")
import launchy

import comtypes
from comtypes.client import CreateObject, GetModule

import sys, os
from os import path
import urllib
import time

fileUrlPrefix = "file:///"

GetModule("shdocvw.dll")
SHDocVw = comtypes.gen.SHDocVw
shellWindows = CreateObject(SHDocVw.ShellWindows)

# Returns a list of the current directories opened by Explorer
def listOpenExplorerDirectories():
	dirs = []
	for explorer in shellWindows:
		locationUrl = explorer.LocationURL
		if locationUrl.startswith(fileUrlPrefix):
			path = locationUrl[len(fileUrlPrefix):]
			dirs.append( urllib.unquote(path) )
			
	return dirs
	
class PyExplorey(launchy.Plugin):
	cacheTimeThreshold = 30 # 30 seconds to rebuild cache
	
	def init(self):
		self.icon = os.path.join(launchy.getIconsPath(), "python.ico")
		self.hash = launchy.hash(self.getName())
		self.fileCache = []
		self.lastCacheUpdate = 0 # Should cause cache on first time
		listOpenExplorerDirectories()
		
	def getID(self):
		return self.hash
	
	def getName(self):
		return "PyExplorey"
		
	def getIcon(self):
		return self.icon
		
	def getLabels(self, inputDataList):
		pass
		
	def getResults(self, inputDataList, resultsList):
		try:
			if len(inputDataList) > 1:
				return
			text = inputDataList[0].getText()
			if len(text) == 0:
				return
			
			self._cacheFilesFromOpenDirs()
			
			for fileEntry in self.fileCache:
				if fileEntry[0].startswith(text):
					filePath = path.join(fileEntry[1], fileEntry[0])
					resultsList.append( launchy.CatItem(filePath, fileEntry[0], self.hash, filePath) )
		except Exception, inst:
			print inst
		
	def getCatalog(self, resultsList):
		pass
		
	def launchItem(self, inputDataList, catItem):
		try:
			os.system(catItem.fullPath)
			#launchy.runProgram( catItem.fullPath, "" )
		except Exception, inst:
			print inst
			
	def launchyShow(self):
		pass
			
	def launchyHide(self):
		pass
		
	def _cacheFilesFromOpenDirs(self):
		currentTime = time.time()
		if currentTime - self.lastCacheUpdate < self.cacheTimeThreshold:
			return
			
		self.lastCacheUpdate = currentTime
		
		self.fileCache = []
		openDirectories = listOpenExplorerDirectories()
		for dir in openDirectories:
			for entry in os.listdir(dir):
				#if not path.isfile(entry): continue
				splitext = path.splitext(entry)
				if len(splitext) <= 1: continue
				
				#if splitext[1] in ['.bat', '.lnk']:
				self.fileCache.append( (entry, dir) )

launchy.addPlugin(PyExplorey())