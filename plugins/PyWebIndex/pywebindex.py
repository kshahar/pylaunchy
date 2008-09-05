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
#
# Version 1.1:
#	* Changed DB file location to the Launchy config directory
#	* Added some documentation
# Version 1.0:
#	* First public release
#

#import rpdb2; rpdb2.start_embedded_debugger("password")
import launchy
import sys, os

import urllib2
from BeautifulSoup import BeautifulSoup

from PyQt4 import QtCore, QtGui
from PyQt4.QtCore import QVariant
from sip import wrapinstance, unwrapinstance

import sqlite3
import webbrowser # For launching URLs
import hashlib # For md5

class PyWebIndex(launchy.Plugin):
	__version__ = "1.0"
	initialized = False
	
	def __init__(self):
		launchy.Plugin.__init__(self)
		self.icon = os.path.join(launchy.getIconsPath(), "weby.png")
		self.hash = launchy.hash(self.getName())
		self.labelHash = launchy.hash("pywebindex")
		
		self.widget = None
		self.masterPages = []
		self.db = LinksDB()

	def init(self):
		if self.initialized:
			return
		self.initialized = True
		
		self.__readConfig()
		
	def getID(self):
		return self.hash
	
	def getName(self):
		return "PyWebIndex"
		
	def getIcon(self):
		return self.icon
		
	def getLabels(self, inputDataList):
		pass
		
	def getResults(self, inputDataList, resultsList):
		if len(inputDataList) != 2:
			return
		
		catItem = inputDataList[0].getTopResult()
		if catItem.id != self.getID():
			return
		
		# Get the master page that corresponds to catItem.shortName
		(masterPageId, name, url)  = self.db.getMasterPage( catItem.shortName )
		
		# Get it's subpages
		subPages = self.db.getSubPages(masterPageId, inputDataList[1].getText())
		
		# Add the pages to catalog
		for page in subPages:
			pageId, pageName, pageUrl = page
			resultsList.push_back( launchy.CatItem( str(pageId), pageName, self.getID(), self.getIcon() ) )
		
	def getCatalog(self, resultsList):
		for masterPage in self.masterPages:
			resultsList.push_back( launchy.CatItem( masterPage[1] + ".webindex", masterPage[1], self.getID(), self.getIcon() ) )
		
	def launchItem(self, inputDataList, catItemOrig):
		# Launch the requested URL
		
		catItem = inputDataList[-1].getTopResult()
		pageId = int(catItem.fullPath)
		
		# Fetch the page and it's master from DB
		masterPageId, name, pageUrl = self.db.getSubPage(pageId)
		masterPageName, masterPageUrl = self.db.getMasterPageById(masterPageId)
		
		fullUrl = urllib2.urlparse.urljoin(masterPageUrl, pageUrl)
		
		print_debug("Opening URL: " + fullUrl)
		webbrowser.open(fullUrl)
		
	def hasDialog(self):
		return True
		
	def doDialog(self, parentWidgetPtr):
		parentWidget = wrapinstance(parentWidgetPtr, QtGui.QWidget)
		
		if self.widget == None:
			self.widget = PyWebIndexUi(parentWidget)
			self.widget.show()
			
		return unwrapinstance(self.widget)
		
	def endDialog(self, accept):
		self.widget.hide()
		if accept:
			self.widget.writeSettings()
			self.__readConfig()
		
		del self.widget
		self.widget = None
		
	def launchyShow(self):
		pass
			
	def launchyHide(self):
		pass
	
	def __readConfig(self):
		settings = launchy.settings
		
		# Test if the settings file has PyWebIndex configuration
		version = settings.value("PyWebIndex/version", QVariant("0.0")).toString()
		print_debug("PyWebIndex version: " + version)
		if version == "0.0":
			settings.setValue("PyWebIndex/pagesHash", QVariant(""))
			
			settings.beginWriteArray("PyWebIndex/masterPages")
			settings.setArrayIndex(0)
			settings.setValue("name", QVariant("doclaunchy"))
			settings.setValue("url", QVariant("http://launchy.net/api2.0/doxydoc/classes.html"))
			settings.endArray()
		
		# Set our version
		settings.setValue("PyWebIndex/version", QVariant(self.__version__))
		
		# Read master pages from the settings file
		masterPages = []
		size = settings.beginReadArray("PyWebIndex/masterPages")
		for i in range(0, size):
			settings.setArrayIndex(i);
			masterPages.append( 
				( unicode(settings.value("name").toString()),
				  unicode(settings.value("url").toString()) )
			)
		settings.endArray()
		
		# Make a hash of the pages we just read
		newPagesHash = hashlib.md5()
		for page in masterPages:
			newPagesHash.update( page[0] + page[1] )
		
		# Test the new hash against the hash in the settings file
		pagesHash = settings.value("PyWebIndex/pagesHash").toString()
		if (newPagesHash.digest() != pagesHash) or (self.db.isDatabaseRebuilt):
			# Database rebuild is required since the hash changed
			print_debug("Rebuilding PyWebIndex Database")
			settings.setValue("PyWebIndex/pagesHash", QVariant(newPagesHash.digest()))
			self.__parseMasterPages(masterPages)
		
		self.masterPages = self.db.getMasterPages()
	
	def __parseMasterPages(self, masterPages):
		# Recreate tables in DB
		self.db.rebuildDatabase()
		
		# Download all master pages, get their links and add them to DB
		
		for masterPage in masterPages:
			(masterPageId, name, url) = self.db.addMasterPage(
				masterPage[0], masterPage[1] )
			
			print_debug(masterPageId, name, url)
			
			try:
				page = urllib2.urlopen(url)
				soup = BeautifulSoup(page)
				allLinks = soup.findAll('a')
			except Exception, msg:
				print >> sys.stderr, "PyWebIndex: Error opening url " + url
				continue
			
			for link in allLinks:
				if link.string and link.string != '' and link.has_key('href'):
					try:
						self.db.addSubPage( masterPageId, link.string, link['href'] )
					except Exception, msg:
						print >> sys.stderr, "PyWebIndex: Error parsing link " + link
		
		# Finished adding to DB
		self.db.commit()
		
class LinksDB:
	"""
	Provides an interface to database that contains master (index pages) and
	the links they contain.
	
	Database is composed of two tables: 
	 * master_pages - contains the page name and full URL
	 * sub_pages - contains pages linked from a master page, the link name and
	    a partial or full URL.
	"""
	
	def __init__(self):
		self.dbFile = os.path.join(launchy.getConfigPath(), 'pywebindex.db')
		
		self.conn = None
		self.isDatabaseRebuilt = False
		
		if os.path.exists(self.dbFile):
			self.conn = sqlite3.connect(self.dbFile)
			self.cursor = self.conn.cursor()
		else: 
			self.rebuildDatabase()
			self.isDatabaseRebuilt = True
			
	def rebuildDatabase(self):
		if self.conn:
			self.conn.close()
		if os.path.exists(self.dbFile):
			os.unlink(self.dbFile)
			
		self.conn = sqlite3.connect(self.dbFile)
		self.cursor = self.conn.cursor()
							
		self.cursor.execute('''CREATE TABLE master_pages (
			id  INTEGER PRIMARY KEY ,
			name TEXT,
			url TEXT
		)''')

		self.cursor.execute('''CREATE TABLE sub_pages (
			id  INTEGER PRIMARY KEY ,
			masterPage INTEGER,
			name TEXT,
			url TEXT
		)''')
		
	
	def addMasterPage(self, name, url):
		self.cursor.execute('''INSERT INTO master_pages
			VALUES(null, "%s", "%s")''' % (name, url))
		
		self.cursor.execute('''SELECT * FROM master_pages
			WHERE name="%s" ''' % name)
		
		row = self.cursor.fetchone()
		return row
	
	def getMasterPages(self):	
		self.cursor.execute('''SELECT * FROM master_pages''')
		return self.cursor.fetchall()
	
	def getMasterPage(self, name):
		self.cursor.execute('''SELECT id, name, url FROM master_pages
			WHERE name LIKE "%s" ''' % name)
		return self.cursor.fetchone()
		
	def getMasterPageById(self, id):
		self.cursor.execute('''SELECT name, url FROM master_pages
			WHERE id=%d ''' % id)
		return self.cursor.fetchone()

	def addSubPage(self, masterPageId, name, url):
		self.cursor.execute('''INSERT INTO sub_pages
			VALUES(null, %d, "%s", "%s")''' % (masterPageId, name, url))
	
	def getSubPages(self, masterPageId, userQuery=''):
		if userQuery == '':
			self.cursor.execute('''SELECT id, name, url FROM sub_pages
				WHERE masterPage=%d ''' % masterPageId)
		else:
			self.cursor.execute('''SELECT id, name, url from sub_pages 
				WHERE masterPage=%d AND name LIKE "%%%s%%" ''' 
				% (masterPageId, userQuery))
		
		return self.cursor.fetchall()
		
	def getSubPage(self, pageId):
		self.cursor.execute('''SELECT masterPage, name, url FROM sub_pages
			WHERE id=%d ''' % pageId)
		return self.cursor.fetchone()
	
	def commit(self):
		self.conn.commit()

class PyWebIndexUi(QtGui.QWidget):
	def __init__(self, parent=None):
		QtGui.QWidget.__init__(self, parent)
		self.ui = Ui_Form()
		self.ui.setupUi(self)
		
		self.ui.forceDatabaseRebuildBox.setChecked(False)
		
		settings = launchy.settings
		table = self.ui.entriesTable
		
		size = settings.beginReadArray("PyWebIndex/masterPages")
		table.setRowCount(size)
		
		for i in range(0, size):
			settings.setArrayIndex(i);
			nameItem = QtGui.QTableWidgetItem( settings.value("name").toString() )
			urlItem = QtGui.QTableWidgetItem( settings.value("url").toString() )
			table.setItem(i, 0, nameItem)
			table.setItem(i, 1, urlItem)
		
		settings.endArray()
		
	def addEntry_clicked(self):
		table = self.ui.entriesTable
		table.insertRow(table.rowCount())
		table.setCurrentCell(table.rowCount()-1, 0)
	
	def removeEntry_clicked(self):
		currentRow = self.ui.entriesTable.currentRow()
		if currentRow != -1:
			self.ui.entriesTable.removeRow(currentRow)
		
	def writeSettings(self):
		settings = launchy.settings
		table = self.ui.entriesTable
		
		if self.ui.forceDatabaseRebuildBox.isChecked():
			# Invalidate the pages hash
			settings.setValue("PyWebIndex/pagesHash", QVariant(""))
		
		# Remove all empty rows
		itemsToRemove = []
		for i in range(0, table.rowCount()):
			nameItem = table.item(i,0)
			urlItem = table.item(i,1)
			if nameItem == None or urlItem == None:
				itemsToRemove.append(i)
			elif nameItem.text() == "" or urlItem == "":
				itemsToRemove.append(i)
		
		for item in itemsToRemove:
			table.removeRow(i)
		
		# Add all rows to the masterPages array
		settings.remove("PyWebIndex/masterPages")
		settings.beginWriteArray("PyWebIndex/masterPages")
		for i in range(0, table.rowCount()):
			settings.setArrayIndex(i)
			settings.setValue("name", QVariant(table.item(i,0).text()))
			settings.setValue("url", QVariant(table.item(i,1).text()))
		settings.endArray()
		
debugOn = False
def print_debug(*args):
	if debugOn:
		print args

launchy.registerPlugin(PyWebIndex)
