#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <stdatomic.h>

#define PORT 8086
#define MAX 100

int clients[MAX];
int client_count = 0;
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void *handle_client(void *arg) {
    int c = *((int *)arg);
    free(arg);
    char buffer[1024];

    while (1) {
        int bytes = recv(c, buffer, sizeof(buffer) - 1, 0);
        if (bytes <= 0) {
            printf("Client disconnected.\n");
            close(c);

            pthread_mutex_lock(&clients_mutex);
            for (int i = 0; i < client_count; i++) {
                if (clients[i] == c) {
                    clients[i] = clients[client_count - 1];
                    client_count--;
                    break;
                }
            }
            pthread_mutex_unlock(&clients_mutex);

            break;
        }

        buffer[bytes] = '\0';
        printf("CLIENT SAYS: %s", buffer);

        pthread_mutex_lock(&clients_mutex);
        for (int i = 0; i < client_count; i++) {
            if (clients[i] != c) {
                send(clients[i], buffer, strlen(buffer), 0);
            }
        }
        pthread_mutex_unlock(&clients_mutex);
    }

    return NULL;
}

int main() {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        perror("SOCKET CREATION FAILED");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in srvaddr;
    srvaddr.sin_family = AF_INET;
    srvaddr.sin_port = htons(PORT);
    srvaddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (struct sockaddr*)&srvaddr, sizeof(srvaddr)) < 0) {
        perror("FAILED TO BIND");
        exit(EXIT_FAILURE);
    }
    printf("SUCCESSFULLY BINDED\n");

    if (listen(s, 5) < 0) {
        perror("FAILED TO LISTEN");
        exit(EXIT_FAILURE);
    }
    printf("SERVER LISTENING ON PORT %d\n", PORT);

    while (1) {
        struct sockaddr_in caddr;
        socklen_t addrlen = sizeof(caddr);
        int c = accept(s, (struct sockaddr*)&caddr, &addrlen);
        if (c < 0) {
            perror("CLIENT SOCKET NOT ACCEPTED");
            continue;
        }

        printf("CLIENT CONNECTED FROM %s:%d\n",
               inet_ntoa(caddr.sin_addr),
               ntohs(caddr.sin_port));

        pthread_mutex_lock(&clients_mutex);
        if (client_count < MAX) {
            clients[client_count++] = c;
        } else {
            printf("Max clients reached. Connection refused.\n");
            close(c);
            pthread_mutex_unlock(&clients_mutex);
            continue;
        }
        pthread_mutex_unlock(&clients_mutex);

        pthread_t tid;
        int *new_sock = malloc(sizeof(int));
        *new_sock = c;

        if (pthread_create(&tid, NULL, handle_client, (void*)new_sock) != 0) {
            perror("THREAD NOT CREATED");
            close(c);
            free(new_sock);
        }

        pthread_detach(tid);
    }

    return 0;
}
