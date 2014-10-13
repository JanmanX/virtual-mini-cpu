HALT 	= 0
LOAD0	= 1
LOAD1	= 2
ADD	= 3
BEEP 	= 4
STORE	= 5
PRINT	= 6

from sys import argv

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
	op = string.split(line)
	
	op1 = lower(op[0])	

	if op1 == "halt":
		return HALT
	elif op1 == "load0":
		if len(op) < 2 or int(op[1]):
			print "[ERROR] Line %d, bad op \"%s\"" % (current_line,line)
		else:
			file_bytes.append(LOAD0)
			file_bytes.append(int(op[1]))
	elif op1 == "load1":
		if len(op) < 2 or int(op[1]):
			print "[ERROR] Line %d, bad op \"%s\"" % (current_line,line)
		else:
			file_bytes.append(LOAD1)
			file_bytes.append(int(op[1]))

	elif op1 == "add":
		file_bytes.append(ADD)

	elif op1 == "beep":
		file_bytes.append(BEEP)

	elif op1 == "store":
		if len(op) < 2 or int(op[1]):
			print "[ERROR] Line %d, bad op \"%s\"" % (current_line,line)
		else:
			file_bytes.append(STORE)
			file_bytes.append(int(op[1]))
	
	elif op1 == "print":
		if len(op) < 2 or int(op[1]):
			print "[ERROR] Line %d, bad op \"%s\"" % (current_line,line)
		else:
			file_bytes.append(PRINT)
			file_bytes.append(int(op[1]))
		
	current_line += 1



# Write the array to file
byte_array = bytearray(file_bytes)
fd_translated.write(byte_array)
fd_translated.close()

print "Finished..."
