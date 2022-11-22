#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<stdlib.h>
#define SA struct sockaddr
void main(){
	int s,k,len,on=1,n=0;
	char buf[100],msg[200],id[34];
	struct sockaddr_in servaddr,cliaddr,baddr;
	s=socket(PF_INET, SOCK_DGRAM,0);
	if(s==-1){
		printf("\nSocket creation failed...");
		exit(0);
	}
	printf("\nSocket created...");
	setsockopt(s,SOL_SOCKET,SO_BROADCAST,&on,sizeof(on));
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_port=htons(5000);
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=INADDR_ANY;
	if((bind(s,(SA*)&servaddr, sizeof(SA)))!=0){
		printf("\nSocket bind failed...");
		exit(0);
	}
	printf("\nSocket binded...");
	baddr.sin_family=AF_INET;
	baddr.sin_port=htons(6000);
	inet_pton(AF_INET,"192.168.0.255",&baddr.sin_addr);
	printf("\nEnter the msg to broadcast : ");
	while((msg[n++]=getchar())!='\n');
	sendto(s,msg,strlen(msg),0,(SA*)&baddr,sizeof(baddr));
	fflush(NULL);
	close(s);
}
