#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *hello = "Hello Client, message received!";

    // 1. Create the server socket file descriptor
    // Use '< 0' for error checking, as socket() returns -1 on failure.
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 2. Set socket options to allow reuse of the address and port
    // This helps avoid "Address already in use" errors on restart.
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    // 3. Prepare the sockaddr_in structure
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Listen on all available network interfaces
    address.sin_port = htons(PORT);

    // 4. Bind the socket to the specified IP and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // 5. Put the server socket in listening mode
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // 6. Main loop to accept and handle multiple clients sequentially
    while (1) {
        printf("\nWaiting for a new client connection...\n");
        
        // Accept an incoming connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE); // Or continue, depending on desired robustness
        }
        
        // Announce the new connection
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &address.sin_addr, client_ip, INET_ADDRSTRLEN);
        printf("Connection accepted from %s:%d\n", client_ip, ntohs(address.sin_port));

        // Read the message from the client
        // 'read' returns the number of bytes read. It's safer to use this value.
        int valread = read(new_socket, buffer, BUFFER_SIZE - 1);
        if (valread > 0) {
            buffer[valread] = '\0'; // Null-terminate the string for safety
            printf("Client says: %s\n", buffer);

            // Send a response back to the client
            send(new_socket, hello, strlen(hello), 0);
            printf("Response sent to client.\n");
        } else {
            printf("Client disconnected or read error.\n");
        }

        // Close the socket for this specific client
        close(new_socket);
    }

    // The server will loop forever, so this part is not reached in this simple example.
    // In a real application, you would have a signal handler to gracefully shut down.
    close(server_fd);

    return 0;
}