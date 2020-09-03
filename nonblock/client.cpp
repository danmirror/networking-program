
#include <fcntl.h>
// udp client driver program 
#include <stdio.h> 
// #include <strings.h> 
#include <sys/types.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include<netinet/in.h> 
#include<unistd.h> 
#include<stdlib.h> 
#include<iostream>
#include <string.h>
// #include <stdio.h>
#include <fcntl.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/poll.h>

#define PORT 8124
#define MAXLINE 1000 

// Driver code 
int main() 
{ 
    char *ipp = "127.0.0.1";

	int sockfd, n; 
	char buffer[100]; 
	char *message = "31,12,12,12"; 
	struct sockaddr_in servaddr; 
	socklen_t len =  sizeof(servaddr);
	// clear servaddr 
	bzero(&servaddr, sizeof(servaddr)); 
	servaddr.sin_addr.s_addr = inet_addr(ipp); 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_family = AF_INET; 
	
	// create datagram socket 
	sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
	
	// connect to server 
	if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) 
	{ 
		printf("\n Error : Connect Failed \n"); 
		exit(0); 
	} 

    // Setup for polling
    struct pollfd ufds[1];
    ufds[0].fd = sockfd;
    ufds[0].events = POLLIN;            // For incoming packets
	

	// request to send datagram 
	// no need to specify server address in sendto 
	// connect stores the peers IP and port 
	sendto(sockfd, message, strlen(message), 0, (struct sockaddr*)&servaddr, sizeof(servaddr)); 
	
   int  poll_ret = poll(ufds, 1, 100);
//    printf("%d",poll_ret);
    if (poll_ret > 0){
        n = recvfrom(sockfd, buffer, sizeof(buffer),0, (struct sockaddr*)&servaddr,&len); //receive message from server 

        buffer[n] = '\0'; 
        puts(buffer); 
    }

	close(sockfd); 
} 
