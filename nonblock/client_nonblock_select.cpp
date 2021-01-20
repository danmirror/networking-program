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
// #include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>

#define PORT 8124
#define MAXLINE 1000 

// Driver code 
int main() 
{ 
	int sockfd, n; 
	fd_set rfds;
    struct timeval tv;
    int retval;

   /* Watch stdin (fd 0) to see when it has input. */
    FD_ZERO(&rfds);
    FD_SET(sockfd, &rfds);

   /* Wait up to five seconds. */
    tv.tv_sec = 0;
    tv.tv_usec = 10;




    char *ipp = "127.0.0.1";


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

	// request to send datagram 
	// no need to specify server address in sendto 
	// connect stores the peers IP and port 
	sendto(sockfd, message, strlen(message), 0, (struct sockaddr*)&servaddr, sizeof(servaddr)); 
	
    // send(sockfd , message , strlen(message) , 0); 
	// waiting for response 
	// recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)NULL, NULL); 
	retval = select(1, &rfds, NULL, NULL, &tv);
    /* Don't rely on the value of tv now! */

   if (retval == -1)
        perror("select()");
    else {
        printf("Data is available now.\n");

		n = recvfrom(sockfd, buffer, sizeof(buffer),0, (struct sockaddr*)&servaddr,&len); //receive message from server 

		buffer[n] = '\0'; 
		puts(buffer); 
	}
        /* FD_ISSET(0, &rfds) will be true. */
    // else
    //     printf("No data within five seconds.\n");


    
	// close the descriptor 
	close(sockfd); 
} 
