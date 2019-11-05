// server code for UDP socket programming 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 


#define PORT_NO 15050 
#define NET_BUF_SIZE 9999


// driver code 
int main() 
{ 
	int sockfd, nBytes; 
	struct sockaddr_in addr_con; 
	int addrlen = sizeof(addr_con); 
	
	addr_con.sin_family = AF_INET; 
	addr_con.sin_port = htons(PORT_NO); 
	addr_con.sin_addr.s_addr = INADDR_ANY; 
	
	char net_buf[NET_BUF_SIZE] = {'\0'}; 


	// socket() 
	sockfd = socket(AF_INET, SOCK_DGRAM, 0); 

	// bind() 
	bind(sockfd, (struct sockaddr*)&addr_con, sizeof(addr_con));
	

	printf("\nWaiting for file name...\n"); 

	// receive file name 


        recvfrom(sockfd, net_buf, NET_BUF_SIZE, 0, (struct sockaddr*)&addr_con, &addrlen); 

	FILE * fp; 
	fp = fopen("rec.txt", "w"); 
	
	fputs(net_buf,fp);
	
	printf("%s","File rec in rec.txt\n");
	fclose(fp); 
	
	return 0; 
} 

