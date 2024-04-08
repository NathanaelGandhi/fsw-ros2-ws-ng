import socket
import time

HOST = "127.0.0.1"
PORT = 50006
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
print("Connected to socket " + HOST + " on port " + str(PORT))

sender_id = 1
fc = 2
val = 5
msg = str(sender_id) + " " + str(fc) + " " + str(val)
s.sendall(msg.encode())
print("msg sent: " + msg)

# time.sleep(1)

result = b""
while True:
    data = s.recv(1024)
    if not data:
        continue
    result += data
    if len(result) >= 0:  # assuming you are expecting at least 4 bytes for an integer
        break

result = result.decode()
result = result.split()
result = int(result[-1])
print("Result: " + str(result))
s.close()
print("Disconnected from socket " + HOST + " on port " + str(PORT))
