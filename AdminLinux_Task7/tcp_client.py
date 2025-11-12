import socket

MY_IP = '192.168.1.15'
MY_PORT = 5123

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

client_socket.connect((MY_IP, MY_PORT))
print(f"successfully connect on server socket: {MY_IP}:{MY_PORT}")

while True:
    msg = input("Client: ")
    client_socket.sendall(msg.encode())
    if msg.lower() == 'exit':
        break
    data = client_socket.recv(1024).decode()
    print("Server:", data)

client_socket.close()