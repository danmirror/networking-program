#include <iostream>
#include <sstream> /* osstream*/
#include <stdio.h> 
#include <time.h>   
#include "swap.h"
// #include <strings.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h>
#include <sys/socket.h> 
#include <sys/types.h> 
#include <sys/time.h>
#include <sys/poll.h>
 
using namespace std;

#define PORT 8124
#define MAXLINE 1000 

//============================komunikasi robot===================
int sockfd;
int data_tilt = 0;
int result_kom = 0;

//set publick init
struct sockaddr_in servaddr; 
socklen_t len =  sizeof(servaddr);

/*
 *
 * Inisialisasi komunikasi antar robot
 *
 */
int init_kom(){

   char *ip_server = "127.0.0.1" ;

   // clear servaddr 
   bzero(&servaddr, sizeof(servaddr)); 
   servaddr.sin_addr.s_addr = inet_addr(ip_server); 
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
}

/*
 *
 * Komunikasi antar robot
 *
 */
int komunikasi(int tilt_kom,int int_tilt, int int_pan, int int_gyro, int int_ball, int int_count,int int_limit){
   int kom = 0;
   string buf_eksekusi;

   string checksum;
   string robot; 
   string data_all;
   string result_checksum;
   char *data_send;
   ostringstream tilt,pan,gyro,ball,count,limit,times,tilt_check,pan_check;
   tilt_check<<abs(int_tilt);
	pan_check<<abs(int_pan);
   tilt<<int_tilt;
   pan<<int_pan;
   gyro<<int_gyro;
   ball<<int_ball;
   count<<int_count;
   limit<<int_limit;

   /*get milli*/
   timeval curTime;
   gettimeofday(&curTime, NULL);
   int milli = curTime.tv_usec / 1000;
   
   /* get seconds*/
   time_t rawtime = time(NULL);
    
   if (rawtime == -1) {
        
      puts("The time() function failed");
      return 1;
   }
    
    struct tm *ptm = localtime(&rawtime);
    
   if (ptm == NULL) {
        
      puts("The localtime() function failed");
      return 1;
   }
   times<<ptm->tm_sec<<"."<<milli;

   cout<<times.str();
   char buffer[100]; 
   char *message = "Hello Server"; 



   //bit pertama nomer robot bit kedua nilai
   if (tilt_kom ==1 ) robot="31";   //berarti robot tiga nilai 0
   else robot = "30";

   checksum = robot+tilt_check.str()+pan_check.str()
               +gyro.str()+ball.str()
               +count.str()+limit.str();
   result_checksum = Swap::str(checksum);

   //convert data semua ke data all
   data_all = robot+","+tilt.str()
               +","+pan.str()+","+gyro.str()
               +","+ball.str()+","+count.str()
               +","+limit.str()+","+times.str()
               +","+result_checksum;

   data_send= &data_all[0];
   sendto(sockfd, data_send, strlen(data_send), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));

   //set polling
   struct pollfd ufds[1];
   ufds[0].fd = sockfd;
   ufds[0].events = POLLIN;            // For incoming packets

   int  poll_ret = poll(ufds, 1, 20); //set poll
   //printf("%d",poll_ret);

   if (poll_ret > 0)
   {
      int n = recvfrom(sockfd, buffer, sizeof(buffer),0, (struct sockaddr*)&servaddr,&len); //receive message from server 

      buffer[n] = '\0'; 
      puts(buffer); 
      buf_eksekusi = buffer;
      // cout<<buffer<<endl;
   }
   else
   {
      buf_eksekusi = "null";
   }


   if (buf_eksekusi == "31"||buf_eksekusi == "null")
   {
      kom = 0;
      cout<<"robot lain berhenti"<<endl;
   }
   else 
   {
      cout<<"mencoba berhenti-----------------------------------"<<endl<<endl<<endl<<endl;
      kom = 1;
   }
   return kom;
}

int main()
{
   init_kom();
   komunikasi(2,2, 2,360, 1, 0,100);

}
