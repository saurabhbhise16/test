// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8091
	char buffer[1024] = {0};
	// A utility function to check if a given character is operand 
int isOperand(char c) { return (c >= '0' && c <= '9'); } 

int evaluate(char *exp) 
{ 
		
	char delim[] = "";	
	
	
	//Check if operator then assign it to delim
	for (int i = 0; exp[i]; i += 1) 
	{
		if (!isOperand(exp[i]))
		{
			delim[0] = exp[i];
		}
	}
	
	//Splitting
	char *ptr = strtok(exp, delim);
	
	int arr[2];
	int i = 0;
	
	//loop to traverse and split further
	while(ptr != NULL)
	{
		//accepts string and converts it to integer and stores it in arr
		sscanf(ptr, "%d", &arr[i]);
		
		//traverse to next delimiter
		ptr = strtok(NULL, delim);
		i++;
	}
	
	//printf("%d %d",arr[0],arr[1]);
	
	int res = arr[0];
	
	if (delim[0] == '+')	 res += arr[1]; 
	else if (delim[0] == '-') res -= arr[1];
	else if (delim[0] == '*') res *= arr[1];
	else if (delim[0] == '/') res /= arr[1];
 

	return res; 
} 

int main(int argc, char const *argv[]) 
{ 
	int server_fd, new_socket, valread,result; 
	
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
	result = evaluate(buffer);
	sprintf(result_str, "%d", result);
	send(new_socket , result_str , strlen(result_str) , 0 ); 
	return 0; 
} 

