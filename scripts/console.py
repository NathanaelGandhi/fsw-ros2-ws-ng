import socket

HOST = "127.0.0.1"
PORT = 50006
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))

sender_id = 1
fc = 2
val = 5
msg = str(sender_id) + " " + str(fc) + " " + str(val)
s.sendall(msg.encode())

result = s.recv(1024)
result = int(result.decode())
print(result - 1 == val)
s.close()
