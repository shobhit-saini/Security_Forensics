#include<iostream>
#include<string>
#include<sstream>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
using namespace std;
int main()
{
	string crc;
	cout<<"Enter the CRC generator:";
	getline(cin,crc);
    int n=crc.length();
	   int net_socket;
   net_socket=socket(AF_INET,SOCK_STREAM,0);
   /*AF_INET:Family of IPV4
     SOCK_STREAM:For TCP*/

   //2.Specify an address for the socket
   struct sockaddr_in server_address;
   server_address.sin_family=AF_INET;
   server_address.sin_port=htons(9007);//htons():Convert from Little to Big Endian
   server_address.sin_addr.s_addr=INADDR_ANY;

   int connection_status=connect(net_socket,(struct sockaddr*)&server_address,sizeof(server_address));

  // check for error with the connection
if(connection_status<0)
{
  printf("Error");
}
  //Recieve data from the server
  char server_response[1024];
  read(net_socket,server_response,1024);
 string msg = server_response;
 cout<<"received msg\t"<<msg<<endl;
   cout<<"received msg len\t"<<msg.length()<<endl;
//print out the server's reponse
//printf("The server Sent the data:%s\n",server_response);


	for(int i=0;i<=msg.length()-n;)
	{
		for(int j=0;j<n;j++)
		{
			msg[i+j]=msg[i+j]==crc[j]? '0':'1';
	 	}
			for(;i<msg.length()&&msg[i]!='1';i++);
	}
	/*	int res1=stoi(msg);
		if(res1==0)
		{
			cout<<"No Error";
		}	
		else
		{
			cout<<"Error";
		}*/
	for(int i=0;i<msg.length();i++)
	{
	    if(msg[i]=='1')
	    {
	        cout<<"Error in msg";
	        return 0;
	    }
	    
	}	
	cout<<"Msg received correctly";
	
		
	//close the socket()
    close(net_socket);
return 0;
}
