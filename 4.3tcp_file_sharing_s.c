// server code for UDP socket programming 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 

#define PORT_NO 8804
#define NET_BUF_SIZE 999999 

// driver code 
int main() 
{ 
	int sockfd,new_socket; 
	struct sockaddr_in addr_con; 
	int addrlen = sizeof(addr_con); 
	
	addr_con.sin_family = AF_INET; 
	addr_con.sin_port = htons(PORT_NO); 
	addr_con.sin_addr.s_addr = INADDR_ANY; 
	
	char net_buf[NET_BUF_SIZE]={'\0'}; 

	// socket() 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 

	// bind() 
	bind(sockfd, (struct sockaddr*)&addr_con, sizeof(addr_con));

	printf("\nWaiting for file name...\n"); 

	// receive file name 

	listen(sockfd,5);

	new_socket = accept(sockfd, (struct sockaddr *)&addr_con,(socklen_t*)&addrlen);

	//-------------------------------------------------------------------------------------------
	
	read(new_socket, net_buf, NET_BUF_SIZE, 0);
	FILE * fp; 
	fp = fopen("rec.txt", "w"); 
	
	fputs(net_buf,fp);
	
	printf("%s","File rec in rec.txt");
	fclose(fp); 
 
	return 0; 
} 

