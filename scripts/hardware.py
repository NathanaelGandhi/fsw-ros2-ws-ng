import socket

HOST = ""  # Symbolic name meaning all available interfaces
PORT = 50007  # Arbitrary non-privileged port

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(1)

conn, addr = s.accept()

while 1:
    data = conn.recv(1024)
    if not data:
        break
    val = int(data) + 1
    conn.sendall(str(val))

conn.close()
