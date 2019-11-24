"""TCP Server in future will analyze received packet
and send back requested data
Author: Mateusz Szewczyk"""

import socket
def tcp_server():
    port = 1001
    address = '127.0.0.1'
    buffer_size = 1024 #typical size

    print("Listen on port: ", address)
    # AF_INET - IPv4, SOCK_STREAM - TCP
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((address, port))
    s.listen(1)

    conn, addr = s.accept()
    print ('Connection address:', addr)
    while 1:
        data = conn.recv(buffer_size)
        # when there`s no more data the connection is interrupted
        if not data: break
        print("received data:", data)
    conn.close()


# when the connection is stopped, server starts listening for further connection
while(1):
    tcp_server()