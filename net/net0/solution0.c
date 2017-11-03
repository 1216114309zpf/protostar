#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 2999
void fatal(const char* err){
   printf("%s/n",err);
   exit(-1);
}


int main()
{
   int sockfd;
   struct sockaddr_in target_addr;
   unsigned char buffer[1024];
   unsigned char result[1024];

   if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
         fatal("in socket");

   target_addr.sin_family = AF_INET;
   target_addr.sin_port = htons(PORT);
   target_addr.sin_addr.s_addr =inet_addr("192.168.209.158");
   memset(&(target_addr.sin_zero), '\0', 8); // Zero the rest of the struct.

   if (connect(sockfd, (struct sockaddr *)&target_addr, sizeof(struct sockaddr)) == -1)
      fatal("connecting to target server");

   if(recv(sockfd,buffer,1024,0)==-1)
      fatal("recv erro");

   char *start = strchr(buffer,'\'')+1;
   char *end = strchr(start,'\'');

   int wanted = 0;
   while(start != end){
      wanted*=10;
      wanted+=(*start)-'0';
      start++;
   }

   if(send(sockfd,&wanted,sizeof(wanted),0)==-1)
      fatal("send erro");

   if(recv(sockfd,result,1024,0)==-1)
      fatal("recv erro");

   //buffer[strlen(buffer)]='\0';
   printf("%s",buffer);
   printf("%s",result);
}
