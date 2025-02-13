#include <stdio.h>       // printf(), perror()
#include <stdlib.h>      // exit(), malloc(), free()
#include <string.h>      // memset(), strcpy(), strlen()
#include <unistd.h>      // close(), read(), write()
#include <arpa/inet.h>   // sockaddr_in, inet_addr(), socket functions
#include <sys/socket.h>  // socket(), connect()

int main() {
    // 1. Create a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);  // sockfd is the client socket
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

    // 3. Connect to the server
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("CONNECTED TO SERVER!\n");

    // 4. Send message to server
    char message[1000];
    printf("Enter message to send: ");
    fgets(message, sizeof(message), stdin);
    write(sockfd, message, strlen(message));  // Send to server using sockfd

    // 5. Receive response from server
    char buffer[1024] = {0};
    int bytes_received = read(sockfd, buffer, sizeof(buffer));  // Read from server
    if (bytes_received > 0) {
        printf("Server replied: %s\n", buffer);
    }

    // 6. Close sockets
    close(sockfd);

    return 0;
}
