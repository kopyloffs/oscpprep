#!/usr/bin/python

import socket
i = 1
while i < 255:
	print "10.11.1." + str(i)
	try:
		sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		sock.settimeout(45)
		sock.connect(("10.11.1." + str(i), 25))
		banner = sock.recv(1024)
		print banner
		sock.send("VRFY dad\r\n")
		result = sock.recv(1024)
		print result
		sock.close()
	except socket.error as msg:
		print "Service is closed or something else went wrong"
		print msg
		continue
	finally:
		i += 1	
