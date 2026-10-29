#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXSIZE 100
#define PORT 8080
#define SA struct sockaddr

void comm(int connfd){
	char msg[MAXSIZE];
	while(true){
		memset(msg, 0, sizeof(msg));
		read(connfd,msg,sizeof(msg));
		printf("%s", msg);
		memset(msg,0,MAXSIZE);
		
		for(int n=0; n <= MAXSIZE; n++){
			msg[n] = getchar();
			if(msg[n] != '\n'){ break; }
		}
	}
}

int main(){
 int sockfd, connfd, len; 
    struct sockaddr_in servaddr, cli; 

    sockfd = socket(AF_INET, SOCK_STREAM, 0);  
    memset(&servaddr,0,sizeof(servaddr));

    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT);

    if(bind(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0){
	printf("bind error\n");
	exit(0);
    } else {
	printf("bind successful\n");
    }

    if((listen(sockfd, 5)) != 0){
	printf("listen error\n");
	exit(0);
    } else printf("listening\n");

    connfd = accept(sockfd, (SA*)&cli, &len);
    if(connfd < 0){
	printf("accept fail");
	exit(0);
    } else printf("accepted");

    comm(connfd);
    close(sockfd);
}
