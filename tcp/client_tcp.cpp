// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <iostream>
#include <sstream>
// #define PORT 8088
#define PORT 8124
#include <math.h>
using namespace std;

char *ip_server = "127.0.0.1" ;

int kom = 0;
int main(int argc, char const *argv[]) 

{	
	int tilt_kom = 1;
	int int_tilt = 90;
	int int_pan = 40;

	string buf_eksekusi;
	
	int sock = 0, valread; 
	char *data_send;
	string data_all ;
	string robot;
	// int to string
	ostringstream tilt,pan;
	tilt<<int_tilt;
	pan<<int_pan;
	
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
	if (tilt_kom ==1 ) robot="31";   //berarti robot tiga nilai 1
	else robot = "10";


// ====================================================================

	
	data_all = robot+","+tilt.str()+","+pan.str();		// gabung semua ke string
	data_send = &data_all[0];					// konvert ke chart*

	send(sock , data_send , strlen(data_send) , 0); 
	valread = read( sock , buffer, 1024); 

	cout<<buffer<<endl;
	
	buf_eksekusi = buffer;
	//pengiriman adalah robot yang tidak berhenti/ yang melihat bola duluan
	if (buf_eksekusi == "tiga"||buf_eksekusi == "null"){
		kom = 0;
		cout<<"robot lain berhenti"<<endl;
	}
	else {
		kom = 1;
	}	
	return kom;
} 

