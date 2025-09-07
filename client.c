#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    const char *hello = "Hello Server, this is the Client.";

    // 1. Create the client socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    // 2. Prepare the server address structure
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // 3. Convert the server IP address from text to binary format
    // "127.0.0.1" is the standard IP address for localhost.
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Invalid address / Address not supported\n");
        return -1;
    }

    // 4. Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return -1;
    }

    // 5. Send a message to the server
    send(sock, hello, strlen(hello), 0);
    printf("Message sent to server.\n");

    // 6. Read the server's response
    // 'read' returns the number of bytes read. It's safer to use this value.
    int valread = read(sock, buffer, BUFFER_SIZE - 1);
    if (valread > 0) {
        buffer[valread] = '\0'; // Null-terminate the string for safety
        printf("Server says: %s\n", buffer);
    } else {
        printf("Server did not send a response or disconnected.\n");
    }

    // 7. Close the socket
    close(sock);
    return 0;
}