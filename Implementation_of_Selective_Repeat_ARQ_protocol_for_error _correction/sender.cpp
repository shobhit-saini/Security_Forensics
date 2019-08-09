#include<iostream>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
using namespace std;
	int main()
	{
		int server_socket;
		server_socket=socket(AF_INET,SOCK_STREAM,0);
		struct sockaddr_in server_address;
		server_address.sin_family=AF_INET;
		server_address.sin_port=htons(9008);
		server_address.sin_addr.s_addr=INADDR_ANY;
		int bindfd=bind(server_socket,(struct sockaddr*)&server_address,sizeof(server_address));
		if(bindfd<0)
		{
			perror("ERROR");
			return 1;
		}
		listen(server_socket,5);
		int length=sizeof(server_address);
		int client_socket=accept(server_socket,(struct sockaddr*)&server_address,(socklen_t*)&length);
		if(client_socket<0)
		{
			perror("ERROR");
			return 1;
		}
		int no_fr;
		int window_size;
		cout<<"Enter the no. of frame:";
		cin>>no_fr;
		cout<<"Enter the window size:";
		cin>>window_size;
		int frame[no_fr]={0};
		write(client_socket,(char*)&no_fr,sizeof(no_fr));
		write(client_socket,(char*)&window_size,sizeof(window_size));
		for(int i=0;i<no_fr;i++)
		{
			frame[i]=i;
			
		}
		int c,k=0;
		write(client_socket,(char*)&frame[0],(window_size-1)*sizeof(frame[1]));
		read(client_socket,(char*)&c,sizeof(c));
		cout<<"\nNAK:"<<c<<"\nResending";
		write(client_socket,(char*)&frame[c],sizeof(frame[1]));
		int i=window_size;
		//c++;
		while(c<no_fr)
		{
			k++;
			write(client_socket,(char*)&frame[c],(window_size)*sizeof(frame[1]));
			//i+=window_size;
			//cout<<i;
			usleep(1000);
			if(k!=1)
			{
			read(client_socket,(char*)&c,sizeof(c));
			cout<<"\nACK:"<<c<<"\tstatus(Recieved)";
			k++;
			}
			else
			{
			usleep(5000);
			cout<<"\nACK-Not-Recieve-Timeout-Resending";
			write(client_socket,(char*)&frame[c-window_size],(window_size)*sizeof(frame[1]));
			k++;
			}
			
		}
		/*int c,j=0,i,k=0;
		while(j<no_fr-1)
		{
		for(i=j;i<window_size+k;i++)
		{
			write(client_socket,(char*)&frame[i],sizeof(frame[1]));
			usleep(3000);
			read(client_socket,(char*)&c,sizeof(c));
			cout<<"ack:"<<c<<" Recieves\n";
		}
		k=i;
		j=i+1;
		cout<<j;
		}*/
		
		//char msg[20]="Message from server";
		//write(client_socket,(char*)&msg,sizeof(msg));
		//send(server_socket,msg.c_str(),sizeof(msg),0);
		close(server_socket);
	}
