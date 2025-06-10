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

int main(int argc, char *argv[]){
	int sockfd;
	struct sockaddr_in client_addr;

	client_addr.sin_family=AF_INET;
    client_addr.sin_port=htons(8086);
    if (argc != 2) {
    printf("Usage: %s <server_ip>\n", argv[0]);
    exit(EXIT_FAILURE);
}
    client_addr.sin_addr.s_addr = inet_addr(argv[1]);


    char buffer[1024];
    char sendline[1024];
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
    	perror("SOCKET CREATION FAILED");
    	exit(EXIT_FAILURE);
    }
    int addrlen=sizeof(client_addr);
    // connect(sockfd, sockaddr *addr, socklen_t addrlen);
    if (connect(sockfd, (struct sockaddr*)&client_addr, addrlen) < 0) {
    	perror("CONNECTION FAILED");
    	exit(EXIT_FAILURE);
    }

    while(1){
    	printf("\nYour message: \n");
        fflush(stdout);
        if (fgets(sendline, sizeof(sendline), stdin) == NULL) {
        printf("Input error or EOF detected. Exiting.\n");
        break;
    }

        sendline[strcspn(sendline, "\n")] = '\0'; // Optional cleanup
         if (send(sockfd, sendline, strlen(sendline), 0) < 0) {
        perror("send failed\n");
        }

    	memset(buffer,0,sizeof(buffer));
    	int bytes_recv=recv(sockfd,buffer,sizeof(buffer),0);
    	if(bytes_recv<=0){
    		printf("SERVER IS DISCONNECTED\n");
    		break;
    	}
    	buffer[bytes_recv]='\0';
        printf("SERVER: %s",buffer);
    }
    close(sockfd);



}