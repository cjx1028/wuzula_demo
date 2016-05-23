#encoding=utf8

''' using python2.7'''

import socket


HOST = '127.0.0.1'
PORT = 8008

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(1)

conn, addr = s.accept()
print 'Connected by ', addr

while 1:
    data = conn.recv(1024);
    if not data: break
    print 'Recieved data:', data
    conn.sendall('Hi, wuzula');
conn.close()

