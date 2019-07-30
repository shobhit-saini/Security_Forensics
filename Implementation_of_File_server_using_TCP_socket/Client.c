#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
int main()
{
   //1.Create a socket
   int net_socket;
   net_socket=socket(AF_INET,SOCK_STREAM,0);
   /*AF_INET:Family of IPV4
     SOCK_STREAM:For TCP*/

   //2.Specify an address for the socket
   struct sockaddr_in server_address;
   server_address.sin_family=AF_INET;
   server_address.sin_port=htons(9005);//htons():Convert from Little to Big Endian
   server_address.sin_addr.s_addr=INADDR_ANY;

   int connection_status=connect(net_socket,(struct sockaddr*)&server_address,sizeof(server_address));

  // check for error with the connection
if(connection_status<0)
{
  printf("Error");
}
  //Recieve data from the server
  char server_response[256];
 // recv(net_socket,&server_response,sizeof(server_response),0);
  FILE *fp;
  char c;
   fp=fopen("A2.txt","w");
  do
  {
 	read(net_socket,(char *)&c, sizeof(c));
  	printf("%c", c);
  	if(c != EOF)
     fputc(c,fp);
  }while(c!=EOF);
  
  
//print out the server's reponse
printf("The server Sent the data:%s\n",server_response);

//close the socket()
   close(net_socket);
   return 0;
}
