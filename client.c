#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#define PORT 8086
void *send_handler(void *arg){
	int c=*((int *) arg);
	char message[1024];
	while(1){
		fgets(message,sizeof(message),stdin);
		send(c,message,sizeof(message),0);
	}
}

void *recv_handler(void *arg){
	int c=*((int *) arg);
	char buffer[1024];
	int length;
	while((length=recv(c,buffer,sizeof(buffer)-1,0))>0){
		buffer[length]='\0';
		printf("OTHER USER-%s",buffer);
	}
	printf("DISCONNECTED FROM SERVER\n");
	exit(0);
}





int main(){
	struct sockaddr_in caddr;
	int c=socket(AF_INET,SOCK_STREAM,0);
	caddr.sin_family=AF_INET;
	caddr.sin_port=htons(PORT);
	caddr.sin_addr.s_addr=inet_addr("127.0.0.1");

	if(connect(c,(struct sockaddr*)&caddr,sizeof(caddr))!=0){
		perror("FAILED TO CONNECT TO SERVER");
		close(c);
		exit(EXIT_FAILURE);
	}

	pthread_t sid,recvid;
	pthread_create(&sid,NULL,send_handler,&c);
	pthread_create(&recvid,NULL,recv_handler,&c);
	pthread_join(sid,NULL);
	pthread_join(recvid,NULL);
	printf("BOTH THREADS ARE FINISHED WORKING\n");
	return 0;


}