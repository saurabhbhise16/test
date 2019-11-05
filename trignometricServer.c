#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <math.h>
	
#define PORT 8090
char buffer[1024] = {0};
	
float evaluate(char *exp) 
{ 
	int len=strlen(exp);
	char newexp[len-1];
	
	for(int i=0;i<len-1;i++)
	{
	  newexp[i]=*(exp + i);
	}
	
	char delim[]= "(";	
	
	
	//Check if operator then assign it to delim
	
	//Splitting
	char *ptr = strtok(newexp, delim);

	char *ptr2 = ptr;
	float res;
	float angle;
	
	//loop to traverse and split further
	ptr = strtok(NULL, delim);

	sscanf(ptr,"%f",&angle);

	
			
	if (strcmp(ptr2,"sin") == 0)  res = sin(angle);
	
	
	else if ( strcmp(ptr2,"cos") == 0) res = cos(angle);
	else if ( strcmp(ptr2,"tan") == 0) res = tan(angle);
	
	return res; 
} 

int main() 
{ 
	int server_fd, new_socket, valread;

	//A sockaddr_in is a structure containing an internet address.
	struct sockaddr_in address; 
	
	int opt = 1; 
	int addrlen = sizeof(address); 
	 
	char result_str[5]; 
	
	// Creating socket file descriptor 
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	// Forcefully attaching socket to the port 8080 
	
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	// Forcefully attaching socket to the port 8080 
	bind(server_fd, (struct sockaddr *)&address, sizeof(address));

	listen(server_fd, 3);

	new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen);

	valread = read( new_socket , buffer, 1024); 
	//printf("%s\n",buffer ); 
	
	float res2;
	res2 = evaluate(buffer);
	sprintf(result_str, "%f", res2);
	send(new_socket , result_str , strlen(result_str) , 0 ); 
	return 0; 
} 

