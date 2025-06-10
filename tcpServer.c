#include <arpa/inet.h>
#include<sys/types.h> //including data types
#include<sys/socket.h> //listening
#include<netdb.h> //provide network db operations
#include<fcntl.h> //open the connection
#include<unistd.h> 
#include<stdio.h> 
#include <netinet/in.h>
#include <stdlib.h>
#include<string.h>

int main(){
    int sockfd,new_socket; 
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(8086);
    server_addr.sin_addr.s_addr=INADDR_ANY;
    char buffer[1024]; // recieving data
    char sendline[1024];
    char client_ip[INET_ADDRSTRLEN];

    // create a socket
    sockfd=socket(AF_INET,SOCK_STREAM,0);

    if(sockfd<0){
        perror("SOCKET CREATION FAILED\n");
        exit(EXIT_FAILURE);
    }

    // set a socket
    int opt = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt failed\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("SOCKET SET UP SUCCESSFUL\n");
    // bind a socket bind(sockfd, sockaddr *addr, socklen_t addrlen);
    if(bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr))<0){
        perror("FAILED BINDING\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("BIND SUCCESSFUL\n");
    // Listen to socket listen(sockfd, backlog);
    if(listen(sockfd,2)<0){
        perror("FAILED TO LISTEN TO SOCKET\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("LISTEN SUCCESSFUL\n");
    // accept to socket new_socket= accept(sockfd, sockaddr *addr, socklen_t *addrlen);
    socklen_t addrlen = sizeof(client_addr);
    new_socket=accept(sockfd,(struct sockaddr *)&client_addr,&addrlen);
    if(new_socket<0){
        perror("FAILED TO CONNECT TO SOCKET\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("CONNECTED SOCKET\n");
    inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
    printf("Connection accepted from: %s\n", client_ip);

    
    printf("CONNECTION ESTABLISHED\n");

    // recv( sockfd, *buf, len, flags);
    while(1){
        memset(buffer, 0, sizeof(buffer));
        int bytes_recv=recv(new_socket,buffer,sizeof(buffer),0);
        if(bytes_recv<=0){
            printf("CLIENT IS DISCONNECTED\n");
            break;
            
        }
        buffer[bytes_recv]='\0';
        printf("CLIENT: %s",buffer);
        printf("\nYour message:\n");
        fgets(sendline,sizeof(sendline),stdin);
        sendline[strcspn(sendline, "\n")] = '\0'; // Optional cleanup
        if (send(new_socket, sendline, strlen(sendline), 0) < 0) {
        perror("send failed\n");
}


       
    }
    close(new_socket);
    close(sockfd);

}