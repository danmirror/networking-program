// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <iostream>
#define PORT 8124

using namespace std;

void komunikasi(){
	
	string buf; 
	
	char nilai1[3];
	char nilai2[3];
	int t1,t2;
	
	
	
	int server_fd, new_socket, valread; 
	struct sockaddr_in address; 
	int opt =1; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 
	char *sending ; 
	
	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	// Forcefully attaching socket to the port 8080 
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	// Forcefully attaching socket to the port 8080 
	if (bind(server_fd, (struct sockaddr *)&address,sizeof(address))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	if (listen(server_fd, 3) < 0) 
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen))<0) 
	{ 
		perror("accept"); 
		exit(EXIT_FAILURE); 
	} 
	valread = read( new_socket , buffer, 1024); 
	printf(buffer); 
	 
	
	
	buf = buffer[0];
	
	cout<<endl<<buf<<endl;
	sending="trial";

	/*if (buf== "1"){
		for (int i=1; i<=strlen(buffer);i++) nilai1[i-1]=buffer[i];
		sscanf(nilai1, "%d", &t1);
		cout<<"\n tilt robot1 = "<<t1<<endl;
		
		}
	if (buf== "2"){
		for (int i=1; i<=strlen(buffer);i++) nilai2[i-1]=buffer[i];
		sscanf(nilai2, "%d", &t2);
		cout<<"\n tilt robot2 = "<<t2<<endl;
		}
		
	if (t1<t2) {
		sending="satu"; 
		printf(" robot 1 berhenti \n");
	}
	else if(t1>t2) {
		sending ="dua"; 
		printf(" robot 2 berhenti \n");
	}*/
	send(new_socket , sending , strlen(sending) , 0 );
	
	close(server_fd);
	

}
int main(int argc, char const *argv[]) 
{ 	
	
	while(true){
		komunikasi();
		
		
	}
	
	return 0; 
} 

