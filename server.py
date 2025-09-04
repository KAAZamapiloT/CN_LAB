# server.py
import socket

# Use '0.0.0.0' to listen on all available network interfaces.
# This is important for a server in a network environment.
HOST = '192.168.1.1
'
PORT = 12345

print("Starting server...")

# This outer try/except handles errors in setting up the server socket itself
try:
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server_socket.bind((HOST, PORT))
    server_socket.listen(3)
    
    hostname = socket.gethostname()
    ip_address = socket.gethostbyname(hostname)
    print("Server is listening on {}:{}...".format(ip_address, PORT))

    # Main loop to continuously accept new connections
    while True:
        print("\nWaiting for a new client to connect...")
        # Accept a connection
        # conn is the socket for the client, addr is their address
        conn, address = server_socket.accept()
        
        # This inner try/except/finally handles the communication with a single client
        try:
            print("Connected by {}".format(address))
            # Receive data from the client
            data = conn.recv(1024)
            if data:
                decoded_data = data.decode('utf-8')
                print("Client says: {}".format(decoded_data))
                
                # Send a response back to the client
                response = "Hello Client, message received by Python server!"
                conn.sendall(response.encode('utf-8'))
                print("Response sent to client.")
            else:
                print("Client disconnected without sending data.")
        
        except socket.error as e:
            print("Error during communication with {}: {}".format(address, e))
        
        finally:
            # Crucially, close the connection to this specific client
            # The server will then loop back and wait for another one
            conn.close()
            print("Connection with {} closed.".format(address))

except socket.error as e:
    print("Server setup error: {}".format(e))
except KeyboardInterrupt:
    print("\nServer shutting down due to user interrupt (Ctrl+C).")
finally:
    if 'server_socket' in locals():
        server_socket.close()
    print("Server socket closed.")

