#import rpdb2; rpdb2.start_embedded_debugger("pass")
import sys

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

sys.stdout = FlushedFile('stdout.txt')
sys.stderr = FlushedFile('stderr.txt')
print "pylaunchy is up and running"
