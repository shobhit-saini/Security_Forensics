#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
int main()
{
  char server_message[256]="hi";
int server_socket;
 server_socket=socket(AF_INET,SOCK_STREAM,0);

  //define the server address
  struct sockaddr_in server_address;
   server_address.sin_family=AF_INET;
   server_address.sin_port=htons(9005);//htons():Convert from Little to Big Endian
   server_address.sin_addr.s_addr=INADDR_ANY;

  //Bind the socket 
  int bindfd = bind(server_socket,(struct sockaddr*)&server_address,sizeof(server_address));
	if(bindfd < 0)
	{	
		perror("Error");
		return 1;
	}
  listen(server_socket,5);
  
  int client_socket;
  client_socket=accept(server_socket,NULL,NULL);
   char c;
  FILE *fp;
  fp=fopen("A1.txt","r");
  while((c=fgetc(fp))!=EOF)
 {
    write (client_socket, (char *)&c, sizeof(c));
    printf("%c", c);
 }
char s=EOF;
write(client_socket,(char *)&s, sizeof(s));
//close the socket
close(server_socket);
  return 0;
}
