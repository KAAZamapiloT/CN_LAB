# client.py
import socket

# The IP address of the SERVER to connect to
HOST = '192.168.1.1' 
PORT = 65432

# Create a TCP/IP socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    # Connect the socket to the server's address and port
    client_socket.connect((HOST, PORT))
    print("Successfully connected to server at {}:{}".format(HOST, PORT))

    # Loop to receive data from the server
    while True:
        # Wait to receive data from the server
        data = client_socket.recv(1024)

        # If recv() returns an empty byte string, the server has closed the connection
        if not data:
            break

        # Decode the received bytes into a string and print it
        message = data.decode('utf-8')
        print("Message from server: {}".format(message))
        
        # If the server sends 'exit', the client also closes the connection
        if message.lower() == 'exit':
            break

except socket.error as e:
    print("Socket error: {}. Is the server at {} running?".format(e, HOST))
except Exception as e:
    print("An error occurred: {}".format(e))
finally:
    print("Connection closed.")
    client_socket.close()