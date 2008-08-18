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

import urllib2
from BeautifulSoup import BeautifulSoup

import sqlite3
import win32api

#~ [PyWebIndex]
#~ masterPages\1\name=doclaunchy
#~ masterPages\1\url=http://launchy.net/api2.0/doxydoc/classes.html
#~ masterPages\1\baseUrl=http://launchy.net/api2.0/doxydoc/
#~ masterPages\size=1

class LinkInfo:
	def __init__(self, name, url):
		self.name = name
		self.url = url
		
	def __repr__(self):
		return "(%s, %s)" % (self.name, self.url)



class PyWebIndex(launchy.Plugin):
	def __init__(self):
		launchy.Plugin.__init__(self)
		self.icon = os.path.join(launchy.getIconsPath(), "pysimple.png")
		self.hash = launchy.hash(self.getName())
		self.labelHash = launchy.hash("pywebindex")
		
		self.db = LinksDB()

	def init(self):
		from PyQt4 import QtCore
		from PyQt4.QtCore import QVariant
		settings = launchy.settings
		
		version = settings.value("PyWebIndex/version", QVariant("0.0")).toString()
		print "PyWebIndex version: " + version
		if version == "0.0":			
			settings.beginWriteArray("PyWebIndex/masterPages")
			settings.setArrayIndex(0)
			settings.setValue("name", QVariant("doclaunchy"))
			settings.setValue("url", QVariant("http://launchy.net/api2.0/doxydoc/classes.html"))
			settings.setValue("baseUrl", QVariant("http://launchy.net/api2.0/doxydoc/"))
			settings.endArray()
		
		settings.setValue("PyWebIndex/version", QVariant("1.0"))
		
		masterPages = []
		size = settings.beginReadArray("PyWebIndex/masterPages")
		for i in range(0, size):
			settings.setArrayIndex(i);
			masterPages.append( 
				( unicode(settings.value("name").toString()),
				  unicode(settings.value("url").toString()),
				  unicode(settings.value("baseUrl").toString()) )
			)
		settings.endArray()
		
		self.__parseMasterPages(masterPages)
		
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
		
		(masterPageId, name, url, baseUrl)  = self.db.getMasterPage( catItem.shortName )
				
		subPages = self.db.getSubPages(masterPageId, inputDataList[1].getText())
		for page in subPages:
			pageId, pageName, pageUrl = page
			fullUrl = urllib2.urlparse.urljoin(baseUrl, pageUrl)
			resultsList.push_back( launchy.CatItem( fullUrl, pageName, self.getID(), self.getIcon() ) )
		
	def getCatalog(self, resultsList):
		for masterPage in self.masterPages:
			resultsList.push_back( launchy.CatItem( masterPage[1] + ".webindex", masterPage[1], self.getID(), self.getIcon() ) )
		
	def launchItem(self, inputDataList, catItemOrig):
		catItem = inputDataList[-1].getTopResult()
		url = catItem.fullPath
		print "Opening URL: " + url
		win32api.ShellExecute(0, "open", url, None, ".", 0)
		
	def launchyShow(self):
		pass
			
	def launchyHide(self):
		pass
	
	def __parseMasterPages(self, masterPages):
		for masterPage in masterPages:
			(masterPageId, name, url, baseUrl) = self.db.addMasterPage(
				masterPage[0], masterPage[1], masterPage[2])
			
			print masterPageId, name, url, baseUrl
			
			page = urllib2.urlopen(url)
			soup = BeautifulSoup(page)
			allLinks = soup.findAll('a')
			
			for link in allLinks:
				if link.string and link.string != '':
					self.db.addSubPage( masterPageId, link.string, link['href'] )
		
		self.db.commit()
		
		self.masterPages = self.db.getMasterPages()

class LinksDB:
	def __init__(self):
		dbFile = os.path.join(launchy.getScriptsPath(), 'pywebindex.db')
		if os.path.exists(dbFile):
			os.unlink(dbFile)
			
		self.conn = sqlite3.connect(dbFile)
		self.cursor = self.conn.cursor()
		
		self.cursor.execute('''CREATE TABLE master_pages (
			id  INTEGER PRIMARY KEY ,
			name TEXT,
			url TEXT,
			baseUrl TEXT
		)''')

		self.cursor.execute('''CREATE TABLE sub_pages (
			id  INTEGER PRIMARY KEY ,
			masterPage INTEGER,
			name TEXT,
			url TEXT
		)''')
	
	def addMasterPage(self, name, url, baseUrl):
		self.cursor.execute('''INSERT INTO master_pages
			VALUES(null, "%s", "%s", "%s")''' % (name, url, baseUrl))
		
		self.cursor.execute('''SELECT * FROM master_pages
			WHERE name="%s" ''' % name)
		
		row = self.cursor.fetchone()
		return row
	
	def getMasterPages(self):	
		self.cursor.execute('''SELECT * FROM master_pages''')
		return self.cursor.fetchall()
	
	def getMasterPage(self, name):
		self.cursor.execute('''SELECT id, name, url, baseUrl FROM master_pages
			WHERE name LIKE "%s" ''' % name)
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
	
	def commit(self):
		self.conn.commit()

launchy.registerPlugin(PyWebIndex)
