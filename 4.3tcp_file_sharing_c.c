// client code for UDP socket programming 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h>

#define PORT_NO 8804
#define NET_BUF_SIZE 5000 
 
// driver code 
int main() 
{ 
	int sockfd; 
	struct sockaddr_in addr_con; 
	int addrlen = sizeof(addr_con); 
	
	addr_con.sin_family = AF_INET; 
	addr_con.sin_port = htons(PORT_NO); 
	addr_con.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	FILE *fp;
	char net_buf[NET_BUF_SIZE]; 

	// socket() 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 

	connect(sockfd, (struct sockaddr *)&addr_con, sizeof(addr_con));
	
	//----------------------------------------------------------------------------------------
	printf("\nPlease enter file name :\n"); 		
	scanf("%s", net_buf); 
	
	fp = fopen(net_buf, "r"); 
	
	for (int i = 0; i < NET_BUF_SIZE; i++) 
	{ 
		net_buf[i] =  fgetc(fp); 
		
		if (net_buf[i] == EOF) 
		{
			net_buf[i] = '\0';
			break; 
		}
	}
	
	send(sockfd, net_buf, NET_BUF_SIZE, 0);
		
	printf("\n-------------------------------Data sent successfully to server !\n"); 
	return 0; 
} 

