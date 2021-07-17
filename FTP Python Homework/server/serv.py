import socket
import commands
import sys
import os

#Python 2.7
#server

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
def sendAll(sock, theFile, numBytes):

	sendBuff = ""
	
	# The temporary buffer
	tmpBuff = ""
	
	# Keep sending till all is sent
	while len(sendBuff) < numBytes:
		
		# Attempt to send bytes
		tmpBuff =  sock.send(theFile)
		
		# The other side has closed the socket
		if not tmpBuff:
			break
		
		# Add the received bytes to the buffer
		sendBuff += str(tmpBuff)

if len(sys.argv) < 2:
	print "USAGE python " + sys.argv[0] + " <FILE NAME>"

serverAddr = "127.0.0.1"

listenPort = int(sys.argv[1])
welcomeSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
welcomeSock.bind((serverAddr, listenPort))
welcomeSock.listen(1)

while True:
	print "Waiting for connections..." 

	ftpData =""

	#wait for client to accept, and return addr and sock num
	clientSock, addr = welcomeSock.accept()
	clientSockNum = welcomeSock.getsockname()[1]
	print "\n"
	
	#print address and port number
	print "Accepted connection from client: ", addr
	print "Port: ", clientSockNum
	print "\n"
	
	#buffer for FTP commands recieved	
	ftpCommand = ""
	#buffer for data of the file transferred
	fileData = ""

	#retrieve file size and type cast
	fileSize = 1024
	fileSizeBuff = ""
	#fileSizeBuff = recvAll(clientSock, 10)
	#fileSize = int(fileSizeBuff)
	#print "File Size is: ", fileSize

	#run a loop to keep accepting FTP commands until QUIT
	while (True):
		print 'Is waiting for client FTP command'
		#ftpCommand = recvAll(clientSock, fileSize)
		ftpCommand = clientSock.recv(1024)
		print ftpCommand
		
		if (ftpCommand == "get"):
			print 'Running get command'
			
			#Make and send ephemeral port number to client
			import ephemeral
			print 'Made ephemeral port'
			ephemeral.welcomeSocket.listen(1)
			print 'Now listening...\n'
			
			print 'Sending ephemeral port number to client'
			ephemeralSockNum = ephemeral.welcomeSocket.getsockname()[1]
			clientSock.send(str(ephemeralSockNum))
			print 'Sent ephemeral port to client'
			fileSock, addr = ephemeral.welcomeSocket.accept()
			print 'Client accepted\n'
			print "Accepted connection from client: ", addr
			print "Port: ", ephemeralSockNum
			print "\n"
			
			# Print cwd
			thisdirname = os.path.dirname(os.path.realpath(__file__))
			print 'We are in this directory: ' + thisdirname + '\n'

			# Print requested filename
			queriedFile = clientSock.recv(1024);
			print 'Got requested filename ' + queriedFile
			
			# If filename exist, then send
			if os.path.isfile(queriedFile):
				print 'File exists. Proceed to send file...\n'
				clientSock.send("0")
				f = open(queriedFile, 'rb')
				sendFile = f.read(1024)
				while (sendFile):
					print 'Sending...'
					sendAll(fileSock, sendFile, 1024)
					sendFile = f.read(1024)
				print 'Sent ' + queriedFile + ' to client'
				f.close()
			else:
				print 'File does not exist\n'
				#Tell client that file does not exist
				clientSock.send("1")
			
			# Close socket
			fileSock.close()
			clientSock.send("close");
			print 'Told client that we closed the ephemeral port\n'
			
		if (ftpCommand == "put"):
			print 'Running put command'
			
			#Make and send ephemeral port number to client
			import ephemeral
			print 'Made ephemeral port'
			ephemeral.welcomeSocket.listen(1)
			print 'Now listening...\n'
			print 'Sending ephemeral port number to client'
			ephemeralSockNum = ephemeral.welcomeSocket.getsockname()[1]
			clientSock.send(str(ephemeralSockNum))
			print 'Sent ephemeral port to client'
			fileSock, addr = ephemeral.welcomeSocket.accept()
			print 'Client accepted\n'
			print "Accepted connection from client: ", addr
			print "Port: ", ephemeralSockNum
			print "\n"
			
			filename = clientSock.recv(1024)
			
			#Receive file
			if filename != "0" and filename != "1":
				f = open(filename, 'wb')
				print 'Retrieving file...'
				clientSock.send("5")
				retrFile = fileSock.recv(1024)
				while (retrFile):
					print 'Receiving...'
					f.write(retrFile)
					retrFile = fileSock.recv(1024)
				print 'Received file\n'
				f.close()
			else:
				print 'File does not exist\n'
				#Tell client that file does not exist
				clientSock.send("1")
				
			# Close socket
			fileSock.close()
			clientSock.send("close");
			print 'Told client that we closed the ephemeral port\n'
		
		if (ftpCommand == "ls"):
			print 'Running ls command'
			
			#Make and send ephemeral port number to client
			import ephemeral
			print 'Made ephemeral port'
			ephemeral.welcomeSocket.listen(1)
			print 'Now listening...\n'
			print 'Sending ephemeral port number to client'
			ephemeralSockNum = ephemeral.welcomeSocket.getsockname()[1]
			clientSock.send(str(ephemeralSockNum))
			print 'Sent ephemeral port to client'
			fileSock, addr = ephemeral.welcomeSocket.accept()
			print 'Client accepted\n'
			print "Accepted connection from client: ", addr
			print "Port: ", ephemeralSockNum
			print "\n"
			
			fileList = []
			# Save lines in list
			for line in commands.getstatusoutput('ls -l'):
				strline = str(line)
				fileList.append(strline)
				
			# Tell client num of lines in list
			print 'Telling client number of lines in list'
			numFileList = str(len(fileList))
			clientSock.send(numFileList)
			
			# Get acknowlegement from client
			clientAck = clientSock.recv(1024)
			print clientAck
			print 'Client knows number of lines'
			
			# Send the lines
			print 'Sending lines...'
			for elements in fileList:
				strline = str(elements)
				fileSock.send(strline)
			
			# Waits for client to acknowledge that it's done
			clientSock.recv(1024)
			
			
		if (ftpCommand == "quit"):
			# Tell client that we are closing the connection
			clientSock.send("close")
			print 'Told client that we are closing the port\n'
			break
	
	clientSock.close()
	print 'Bye bye~'
	break
