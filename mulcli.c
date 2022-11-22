#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct sockaddr_in localSock;
struct sockaddr_in serad;
struct ip_mreq group;
int sd;
int datalen;
char databuf[1024];

int main(){
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sd < 0)
	{
		printf("socket is not created");
	}

	int reuse = 1;
	if(setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) < 0)
	{
		printf("socket option problem\n");
		close(sd);
		exit(1);
	}

	bzero((char *) &localSock,sizeof(localSock));
	localSock.sin_family = AF_INET;
	localSock.sin_port = htons(4321);
	localSock.sin_addr.s_addr = INADDR_ANY;

	if(bind(sd, (struct sockaddr*)&localSock, sizeof(localSock)))
	{
		printf("socket not binded\n");
		close(sd);
		exit(1);
	}
	
	printf("socket binded\n");
	
	group.imr_multiaddr.s_addr = inet_addr("226.1.1.1");
	group.imr_interface.s_addr = inet_addr("127.0.0.1");

	if(setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group, sizeof(group)) < 0){
		printf("multicast linking failed\n");
		close(sd);
		exit(1);
	}
	printf("multicast linking passed\n");

	datalen = sizeof(databuf);
	recvfrom(sd,databuf,datalen,0,(struct sockaddr *)&serad,&datalen);
	printf("The message from multicast server is: \"%s\"\n", databuf);	
	
	return 0;	
}
