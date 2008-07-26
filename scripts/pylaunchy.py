import sys, os, glob

# os.chdir('plugins/python')
sys.stdout = open('stdout.txt','w')
sys.stderr = open('stderr.txt','w')
print "Launchy Python plug-in system is up and running"

try:
	print __name__
	for pyfile in glob.glob("*.py"):
		if pyfile != "pylaunchy.py":
			print "Importing %s" % pyfile
			__import__(os.path.splitext(pyfile)[0], globals())
except Exception, inst:
	print inst
print "All plugins were imported"
for s in [sys.stdout, sys.stderr]: s.flush()	
	
# t = TestPlugin()
# print t

# sys.stdout.flush()
# sys.stderr.flush()	

# def getPlugin():
	# return t
	
# def getResults(inputData):
	# try:
		# print dir(inputData), inputData.getID,  inputData.getID()
	# except Exception, inst:
		# print type(inst)     # the exception instance
		# print inst.args      # arguments stored in .args
		# print inst           # __str__ allows args to printed directly
	# sys.stdout.flush()

# try:
	# import launchy
	# print "YEEEEEEEEEEESSSSSSSSSSSSSSS"
	# print launchy.add_five(5)
# except Exception, inst:
	# print type(inst)     # the exception instance
	# print inst.args      # arguments stored in .args
	# print inst           # __str__ allows args to printed directly
