HALT 	= 0
LOAD0	= 1
LOAD1	= 2
ADD	= 3
BEEP 	= 4
STORE	= 5
PRINT	= 6

from sys import argv
from string import *


# Open files for reading
fd = open(argv[1], 'r')
fd_translated = open(argv[1]+"_translated",'w')

# read content and close
lines = fd.readlines()
fd.close()


# List with bytes to be written to file
file_bytes = []

# Run through every line in file
current_line = 1

for line in lines:
	op = split(line)
	
	# Handle blank lines
	if len(op) == 0:
		continue

	op1 = upper(op[0])	

	if op1 == "HALT":
		file_bytes.append(HALT)

	elif str.isdigit(op1):
		file_bytes.append(int(op1))		

	elif op1 == "LOAD0":	
		if len(op) < 2:
			print "[ERROR] Line %d, bad op \"%s\"" % (current_line,line)
		else:
			file_bytes.append(LOAD0)
			file_bytes.append(int(op[1]))
	
	elif op1 == "LOAD1":
		if len(op) < 2:
			print "[ERROR] Line %d, bad op \"%s\"" % (current_line,line)
		else:
			file_bytes.append(LOAD1)
			file_bytes.append(int(op[1]))

	elif op1 == "ADD":
		file_bytes.append(ADD)

	elif op1 == "BEEP":
		file_bytes.append(BEEP)

	elif op1 == "STORE":
		if len(op) < 2:
			print "[ERROR] Line %d, bad op \"%s\"" % (current_line,line)
		else:
			file_bytes.append(STORE)
			file_bytes.append(int(op[1]))
	
	elif op1 == "PRINT":
		if len(op) < 2:
			print "[ERROR] Line %d, bad op \"%s\"" % (current_line,line)
		else:
			file_bytes.append(PRINT)
			file_bytes.append(int(op[1]))
		
	current_line += 1



# Write the array to file
print "Writing bytes to write:"
print file_bytes

byte_array = bytearray(file_bytes)
fd_translated.write(byte_array)
fd_translated.close()

print "Finished..."
