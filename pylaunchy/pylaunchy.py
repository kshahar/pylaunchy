#import rpdb2; rpdb2.start_embedded_debugger("pass")
import sys, os
import launchy

__name__ = launchy.__name__

def redirectOutput():
	# If I write code such as sys.stdout = open('stdout.txt', 'w'), 
	# I have to flush the file after writing to it (using "print" for example).
	# The following class saves the need to flush the file each time.

	class FlushedFile:
		""" Provides an output file that is immediately flushed after write """
		def __init__(self, filepath):
			try:
				self.file = open(filepath, 'w')
			except Exception:
				self.file = None
				
		def write(self, str):
			if self.file == None:
				return
			self.file.write(str)
			self.file.flush()

	# Redirect stdout and stderr
	sys.stdout = FlushedFile(os.path.join(launchy.getScriptsPath(), 'stdout.txt'))
	sys.stderr = FlushedFile(os.path.join(launchy.getScriptsPath(), 'stderr.txt'))
	print "pylaunchy is up and running"


def setSettingsObject():
	# Set the launchy.settings object
	try:
		# Based on http://lists.kde.org/?l=pykde&m=108947844203156&w=2
		
		from sip import wrapinstance, unwrapinstance
		from PyQt4 import QtCore
		
		launchy.settings =  wrapinstance(launchy.__settings, QtCore.QSettings)
	except ImportError, inst:
		print >> sys.stderr, inst
	except NameError:
		print >> sys.stderr, "Could not find __settings object"
	except Exception, inst:
		print >> sys.stderr, inst

		
redirectOutput()

# Add the 'python' directory to module path
sys.path.insert( 0, os.path.realpath( launchy.getScriptsPath() ) )

setSettingsObject()