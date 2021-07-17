import socket 
import commands
import os
import sys

#Python 2.7
#the client

if len(sys.argv) < 2: 
	print "USAGE python " + sys.argv[0] + " <FILE NAME>"

serverAddr = sys.argv[1]

serverPort = int(sys.argv[2])

dataBuffer = ""

serverSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

serverSock.connect((serverAddr, serverPort))

print "Connected to port: ", serverPort

numSent = 0
arg = ""


# ************************************************
# Receives the specified number of bytes
# from the specified socket
# @param sock - the socket from which to receive
# @param numBytes - the number of bytes to receive
# @return - the bytes received
# *************************************************
def recvAll(sock, numBytes):

	# The buffer
	recvBuff = ""
	
	# The temporary buffer
	tmpBuff = ""
	
	# Keep receiving till all is received
	while len(recvBuff) < numBytes:
		
		# Attempt to receive bytes
		tmpBuff =  sock.recv(numBytes)
		
		# The other side has closed the socket
		if not tmpBuff:
			break
		
		# Add the received bytes to the buffer
		recvBuff += tmpBuff
	
	return recvBuff
	

while (arg != "quit"):

	arg = raw_input("ftp> ")
	
	#Splits entered command
	line = arg
	line = line.split()
	if (arg == "quit"):
		serverSock.send("quit")
		print 'quit'
		msg = serverSock.recv(1024)
		if (msg == "close"):
			print 'Server told us that we it is closing the connection port\n'
		print 'Bye bye~'
		break;
		
	elif (2 < len(line) < 3):
		#call help function
		print 'You suck'
	
	else:	
		if line[0] == "get":
			serverSock.send("get")
			print 'Sent get cmd to server'
			
			#Get ephemeral port from server and connect it with server
			newPort = serverSock.recv(1024)
			print 'Got ephemeral port from server'
			print newPort
			fileSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
			fileSock.connect((serverAddr, int(newPort)))
			print 'Established connection with ephemeral port\n'
			
			#Tell server which file we want to get			
			serverSock.send(line[1])
			print 'Told server which file we want to get'
			
			#See whether file exists
			exist = serverSock.recv(1024)
			
			#Receive file
			if exist == "0":
				f = open(line[1], 'wb')
				print 'Retrieving file...'
				#retrFile = fileSock.recv(1024)
				retrFile = recvAll(fileSock, 40)
				while (retrFile):
					print 'Receiving...'
					f.write(retrFile)
					#retrFile = fileSock.recv(1024)
					retrFile = recvAll(fileSock, 40)
				print 'Received file\n'
				f.close()
			else:
				print 'File does not exist\n'
				
				
			#Close ephemeral port
			fileSock.close()
			msg = serverSock.recv(1024)
			if (msg == "close"):
				print 'Ephemeral port is closed\n'
			
		if line[0] == "put":
			serverSock.send("put")
			print 'Sent put cmd to server'
			
			#Get ephemeral port from server and connect it with server
			newPort = serverSock.recv(1024)
			print 'Got ephemeral port from server'
			print newPort
			fileSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
			fileSock.connect((serverAddr, int(newPort)))
			print 'Established connection with ephemeral port\n'
			
			#Check if file exist
			filename = line[1]
			if os.path.isfile(filename):
				print filename ,"exist. Proceed to upload file... \n"
				#Tell server file exists by sending filename
				serverSock.send(filename)
				#Wait for server acknowledgement
				serverSock.recv(1024)
				f = open(filename, 'rb')
				sendFile = f.read(1024)
				while (sendFile):
					print 'Sending...'
					fileSock.send(sendFile)
					sendFile = f.read(1024)
				print 'Sent ' + filename + ' to server'
				f.close()

			else:
				serverSock.send("0")
				print 'File does not exist\n' 
				
			#Close ephemeral port
			fileSock.close()
			msg = serverSock.recv(1024)
			if (msg == "close"):
				print 'Ephemeral port is closed\n'
			
		if line[0]== "ls":
			serverSock.send("ls")
			print 'Sent ls cmd to server'
			
			#Get ephemeral port from server and connect it with server
			newPort = serverSock.recv(1024)
			print 'Got ephemeral port from server'
			print newPort
			fileSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
			fileSock.connect((serverAddr, int(newPort)))
			print 'Established connection with ephemeral port\n'

			# Get number of lines needed
			numLines = serverSock.recv(1024)
			numLines = int(numLines)
			print numLines
			
			# Acknowlege that we got it
			gotNum = serverSock.send("ack")
			print 'Server acknowledged'
			
			# Receive and print lines
			for i in range (1, numLines):
				print fileSock.recv(1024)
			
			# Tells server that we are done
			serverSock.send("Done")
			
		if line[0]== "lls":
			for line in commands.getstatusoutput('ls -l'):
				print line

serverSock.close()

