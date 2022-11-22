#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
struct in_addr localInterface;
struct sockaddr_in groupSock;
int sd;
char databuf[1024];
int datalen = sizeof(databuf);

int main (){

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sd < 0){
		  printf("socket is not created\n");
		  exit(1);
	}
	
	printf("socket created\n");

	  
	bzero((char *) &groupSock,sizeof(groupSock));
	groupSock.sin_family = AF_INET;
	groupSock.sin_addr.s_addr = inet_addr("226.1.1.1");
	groupSock.sin_port = htons(4321);
	localInterface.s_addr = inet_addr("127.0.0.1");


	//local interface is multicasting here 

	if(setsockopt(sd, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface, sizeof(localInterface)) < 0)
	{
  		perror("Setting local interface error");
		exit(1);
	}
	printf("Setting the local interface...OK\n");

  	printf("Enter the msg to multicasted:");
	scanf("%s",databuf);


  	if(sendto(sd, databuf, datalen, 0, (struct sockaddr*)&groupSock, sizeof(groupSock)) < 0){
  		printf("message not send\n");
  	}
	printf("message sent\n");
	
	return 0;
}
