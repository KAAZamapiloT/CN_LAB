# server.py
import socket

# The server's own IP address
HOST = '192.168.1.1' 
PORT = 65432        # Port to listen on

# Create a TCP/IP socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    # Bind the socket to the address and port
    server_socket.bind((HOST, PORT))
    
    # Start listening for incoming connections
    server_socket.listen()
    print("Server is listening on {}:{}".format(HOST, PORT))

    # Block execution and wait for a connection
    client_conn, client_addr = server_socket.accept()

    print("Connected by {}".format(client_addr))
    
    while True:
        try:
            # Get input from the server's user (use raw_input for older Python 2)
            message_to_send = raw_input("Enter message for client (or 'exit' to close): ")

            # Send the message to the client. Data must be in bytes.
            client_conn.sendall(message_to_send.encode('utf-8'))

            # If the server user types 'exit', break the loop and close
            if message_to_send.lower() == 'exit':
                print("Server initiated shutdown.")
                break
                
        except (socket.error, IOError):
            print("Client disconnected.")
            break
        except Exception as e:
            print("An error occurred: {}".format(e))
            break
finally:
    print("Closing server connection.")
    if 'client_conn' in locals():
        client_conn.close()
    server_socket.close()