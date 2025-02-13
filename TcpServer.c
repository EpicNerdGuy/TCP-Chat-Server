#include <stdio.h>       // printf(), perror()
#include <stdlib.h>      // exit()
#include <string.h>      // memset(), strlen()
#include <unistd.h>      // close(), read(), write()
#include <arpa/inet.h>   // sockaddr_in, inet_pton(), socket functions
#include <sys/socket.h>  // socket(), bind(), listen(), accept()

int main() {
    // 1. Create a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 2. Configure the server address
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));  // Zero out the structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);  // Port number

    // Convert IP address from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("Invalid address / Address not supported");
        exit(EXIT_FAILURE);
    }

    // 3. Bind the socket
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // 4. Listen for connections
    if (listen(sockfd, 5) == -1) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    printf("SERVER IS LISTENING ON PORT 8888...\n");

    // 5. Accept a client connection
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_sock = accept(sockfd, (struct sockaddr*)&client_addr, &client_len);
    if (client_sock == -1) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    printf("CLIENT CONNECTED!\n");

    // 6. Receive data from the client
    char buffer[1024] = {0};
    int bytes_received = read(client_sock, buffer, sizeof(buffer));
    if (bytes_received > 0) {
        printf("Received: %s\n", buffer);
    } else if (bytes_received == 0) {
        printf("Client disconnected.\n");
    } else {
        perror("Read error");
    }

    // 7. Send a response to the client
    char message[1000];
    printf("Enter message to send: ");
    fgets(message, sizeof(message), stdin);
    write(client_sock, message, strlen(message));

    // 8. Close sockets
    close(client_sock);
    close(sockfd);

    return 0;
}
