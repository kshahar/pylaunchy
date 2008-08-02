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

import win32gui
from win32con import SW_RESTORE

class PyGoY(launchy.Plugin):
	def __init__(self):
		launchy.Plugin.__init__(self)
		self.icon = os.path.join(launchy.getIconsPath(), "pygo-y.png")
		self.hash = launchy.hash(self.getName())
		self.labelHash = launchy.hash("go-y")

	def init(self):
		pass
		
	def getID(self):
		return self.hash
	
	def getName(self):
		return "PyGo-Y"
		
	def getIcon(self):
		return self.icon
		
	def getLabels(self, inputDataList):
		if len(inputDataList) < 2:
			return
		
		lowerText = inputDataList[0].getText().lower()
		if lowerText == "go" or lowerText == "focus":
			inputDataList[0].setLabel( self.labelHash )
		
	def getResults(self, inputDataList, resultsList):
		if len(inputDataList) != 2:
			return
			
		if not inputDataList[0].hasLabel(self.labelHash):
			return
		
		windowNameToMatch = inputDataList[1].getText().lower()
		if windowNameToMatch == "":
			return
		
		self.topLevelWindows = self._getTopLevelWindows()
		for window in self.topLevelWindows:
			if window[1].lower().find(windowNameToMatch ) > -1:
				resultsList.append( launchy.CatItem(window[1] + ".go", window[1], self.getID(), self.getIcon() ))
				
		# Icon for the window can be extracted with WM_GETICON, but it's too much for now
			
	def getCatalog(self, resultsList):
		resultsList.push_back( launchy.CatItem( "Go.go-y", "Go", self.getID(), self.getIcon() ) )
		resultsList.push_back( launchy.CatItem( "Focus.go-y", "Focus", self.getID(), self.getIcon() ) )
		
	def launchItem(self, inputDataList, catItemOrig):
		catItem = inputDataList[-1].getTopResult()
		for window in self.topLevelWindows:
			if catItem.shortName == window[1]:
				self._goToWindow(window[0])
				break
			
	def launchyShow(self):
		pass
			
	def launchyHide(self):
		pass
		
		
	def _goToWindow(self, hwnd):
		# Bascially copied from old Go-Y plugin
		
		windowPlacement = win32gui.GetWindowPlacement(hwnd)
		showCmd = windowPlacement[1]
		
		if showCmd == SW_RESTORE:
			win32gui.ShowWindow(hwnd, SW_RESTORE)
		else:
			win32gui.BringWindowToTop(hwnd)
		win32gui.SetForegroundWindow(hwnd)
		win32gui.SetActiveWindow(hwnd)
		
	def _getTopLevelWindows(self):
		""" Returns the top level windows in a list of tuples defined (HWND, title) """
		windows = []
		win32gui.EnumWindows(self._windowEnumTopLevel, windows)
		return windows
		
	def _windowEnumTopLevel(hwnd, windowsList):
		""" Window Enum function for getTopLevelWindows """
		title = win32gui.GetWindowText(hwnd)
		if win32gui.GetParent(hwnd) == 0 and title != '':
			windowsList.append((hwnd,title))
				
	_windowEnumTopLevel = staticmethod(_windowEnumTopLevel)

launchy.registerPlugin(PyGoY)
