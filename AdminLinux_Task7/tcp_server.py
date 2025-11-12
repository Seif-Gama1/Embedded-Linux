import socket

MY_IP = '192.168.1.15'
MY_PORT = 5123

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((MY_IP, MY_PORT))
server_socket.listen(1)
print(f"Server successfully listening on {MY_IP}:{MY_PORT}")

conn, addr = server_socket.accept()
print("Connected by", addr)

while True:
    data = conn.recv(1024).decode()
    if not data or data.lower() == 'exit':
        print("Client disconnected.")
        break
    print("Client:", data)
    msg = input("Server reply: ")
    conn.sendall(msg.encode())

conn.close()
server_socket.close()