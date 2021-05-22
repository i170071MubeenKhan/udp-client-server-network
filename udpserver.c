#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
int main(){
	
	struct sockaddr_in seraddr,cliaddr1, cliaddr2;
	int bt, sockfd;
	char buff1[100], buff2[100];
	
	socklen_t addr_size;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0){
		printf("Socket not Created!!!\n");
		return 0;
	}

	seraddr.sin_family=AF_INET;
	seraddr.sin_port=htons(3440);
	seraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	memset(seraddr.sin_zero,'\0',8);
	
	bt=bind(sockfd,(struct sockaddr *) &seraddr, sizeof(struct sockaddr));
	if(bt<0){
		printf("Binding Failed!!!\n");
		return 0;
	}
	
	addr_size = sizeof(struct sockaddr);
	recvfrom(sockfd, buff1, sizeof(buff1), 0, (struct sockaddr *) &cliaddr1, &addr_size);
	printf("Client1 Message: %s\n", buff1);

	recvfrom(sockfd, buff2, sizeof(buff2), 0, (struct sockaddr *) &cliaddr2, &addr_size);
	printf("Client2 Message: %s\n", buff2);
	
	sendto(sockfd, &buff1, sizeof(buff1), 0, (struct sockaddr *) &cliaddr2, addr_size);
	sendto(sockfd, &buff2, sizeof(buff2), 0, (struct sockaddr *) &cliaddr1, addr_size);

	close(sockfd);
	return 1;
}
