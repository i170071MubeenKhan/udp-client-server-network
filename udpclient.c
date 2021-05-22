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
	
	struct sockaddr_in seraddr,cliaddr;
	int bt, sockfd;
	char buff[100];
	
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
	
	scanf("%[^\n]%*c", buff);
	addr_size = sizeof(struct sockaddr);
	sendto(sockfd, &buff, sizeof(buff), 0, (struct sockaddr *) &seraddr, addr_size);
	
	memset(buff, '\0', sizeof(buff));
	recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr *) &seraddr, &addr_size);
	printf("Server Message: %s\n", buff);
	
	close(sockfd);
	return 0;
}
