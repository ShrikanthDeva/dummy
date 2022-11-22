#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<stdlib.h>
#define SA struct sockaddr
void main(){
	int s,k,len,on=1;
	char buff1[100], msg[200],id[34];
	struct sockaddr_in servaddr, cliaddr;
	s=socket(PF_INET, SOCK_DGRAM,0);
	if(s==-1){
		printf("\nSocket creation failed...");
		exit(0);
	}
	printf("\nSocket created...");
	setsockopt(s,SOL_SOCKET,SO_REUSEADDR,&on, sizeof(on));
	bzero(&servaddr,sizeof(servaddr));
	cliaddr.sin_port=htons(6000);
	cliaddr.sin_family=AF_INET;
	cliaddr.sin_addr.s_addr=INADDR_ANY;
	len=sizeof(struct sockaddr_in);
	if((bind(s,(SA*)&cliaddr,sizeof(SA)))!=0){
		printf("\nSocket bind failed...");
		exit(0);
	}
	printf("\nSocket binded...");
	recvfrom(s,buff1,sizeof(buff1),0,(SA*)&servaddr,&len);
	printf("\nMessage from server : %s\n",buff1);
	close(s);
}
