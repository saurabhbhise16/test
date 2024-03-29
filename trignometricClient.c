// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8090

int main(int argc, char const *argv[]) 
{ 
	int sock = 0, valread; 
	
	struct sockaddr_in serv_addr; 
	
	char *hello; 
	char buffer[1024] = {0}; 
	
	scanf("%s",hello);
	sock = socket(AF_INET, SOCK_STREAM, 0);

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
	
	connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	send(sock , hello , strlen(hello) , 0 ); 
	valread = read( sock , buffer, 1024); 
	printf("%s\n",buffer ); 
	return 0; 
} 
