# client.py
import socket

# --- Configuration ---
# The server's hostname or IP address. Use '127.0.0.1' for localhost.
HOST = '192.1.1.2'  
# The port used by the server
PORT = 12345        

# The message to send to the server
message = "Hello Server, this is Client."

print(f"Attempting to connect to server at {HOST}:{PORT}...")

try:
    # 1. Create a socket object
    # The 'with' statement ensures the socket is automatically closed
    # when the block is exited.
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
        
        # 2. Connect to the server
        client_socket.connect((HOST, PORT))
        print("Successfully connected to the server.")

        # 3. Send a message to the server
        # The string message must be encoded into bytes before sending.
        client_socket.sendall(message.encode('utf-8'))
        print("Message sent to server.")

        # 4. Receive the response from the server
        # The argument (1024) is the maximum number of bytes to receive.
        data = client_socket.recv(1024)
        
        # Decode the received bytes back into a string and print it.
        print(f"Server says: {data.decode('utf-8')}")

# Handle specific exceptions for better error feedback
except ConnectionRefusedError:
    print("Connection failed. Please ensure the server is running and accessible.")
except socket.timeout:
    print("Connection timed out. The server might be too busy or unresponsive.")
except socket.error as e:
    print(f"A socket error occurred: {e}")

# The 'with' statement automatically closes the socket here.
print("Connection closed.")