// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <iostream>
#define PORT 8088
#include <math.h>
using namespace std;
char *ip_server = "127.0.0.1" ;

int kom = 0;
int main(int argc, char const *argv[]) 

{	
	int tilt_kom = 1;

	string buf_eksekusi;
	char data[2] ;
	//data[0] = {1,2};
	int sock = 0, valread; 
	char *robot ;

	struct sockaddr_in serv_addr; 
	
	
	char buffer[1024] = {0}; 
	

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, ip_server, &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	} 
	if (tilt_kom ==1 ) robot="21";   //berarti robot tiga nilai 1
	else robot = "20";
	
	
	//sprintf(data,"%c",tilt_kom);
	send(sock , robot , strlen(robot) , 0 ); 
	valread = read( sock , buffer, 1024); 

	cout<<buffer<<endl;
	
	buf_eksekusi = buffer;
	//pengiriman adalah robot yang tidak berhenti/ yang melihat bola duluan
	if (buf_eksekusi == "dua"||buf_eksekusi == "null"){
		kom = 0;
		cout<<"robot lain berhenti"<<endl;
	}
	else {
		kom = 1;
	}	
	return kom;
} 

