#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
using namespace std;
	int main()
	{
		int client_socket;
		client_socket=socket(AF_INET,SOCK_STREAM,0);
		struct sockaddr_in server_address;
		server_address.sin_family=AF_INET;
		server_address.sin_port=htons(9008);
		server_address.sin_addr.s_addr=INADDR_ANY;
		int client_connection=connect(client_socket,(struct sockaddr*)&server_address,sizeof(server_address));
		//char msg[1024]={0};
		int no_fr,window_size,s;
		read(client_socket,(char*)&no_fr,sizeof(no_fr));
		read(client_socket,(char*)&window_size,sizeof(window_size));
		int frame[no_fr]={0};
		//cout<<"no_fr:"<<no_fr<<"\nwindow_size:"<<window_size;
		int m;
		read(client_socket,(char*)&frame,(window_size-1)*sizeof(frame));
		for(int i=0;i<window_size-1;i++)
		{
			cout<<"\nFrame:"<<i<<"\tstatus(Recieved)";
		}
		for(int i=0;i<window_size;i++)
		{
			if(frame[i]!=i)
			{
			 cout<<"\nFrame:"<<i<<"\tStatus(not Recieved)";
			  s=i;	
                          write(client_socket,(char*)&s,sizeof(s));
			}
		}
		
		read(client_socket,(char*)&frame[s],sizeof(frame[0]));
		cout<<"\nFrame:"<<s<<"\tStatus(Recieved)";
		int i=window_size,k=0;
		while(i<no_fr)
		{
			
			read(client_socket,(char*)&frame[i],(window_size)*sizeof(frame[1]));
			for(int j=i;j<i+window_size;j++)
			{
				cout<<"\nFrame:"<<j<<"\tStatus(Recieved)";
			}
			i+=window_size;
			//cout<<"\ni="<<i<<" "<<window_size;
			usleep(2000);
			if(k!=1)
			{
			write(client_socket,(char*)&i,sizeof(i));
			k++;
			}
			else
			{
				read(client_socket,(char*)&frame[i-window_size],(window_size)*sizeof(frame[1]));
				for(int j=i;j<i+window_size;j++)
				{
					cout<<"\nFrame:"<<j<<"\tStatus(Recieved)";
				}
			k++;
			}
			

		}

		//cout<<"\nlost:"<<frame[m];
		/*for(int i=0;i<9;i++)
		{
			read(client_socket,(char*)&c,sizeof(c));
			cout<<"Frame:"<<c<<" Recieves";
			if(c!=i)
			{
				write(client_socket,(char*)&i,sizeof(i));	
			}
			usleep(1000);

			write(client_socket,(char*)&c,sizeof(c));
		}*/
		//read(client_socket,(char*)&msg,sizeof(msg));
		//cout<<msg;
		close(client_socket);		
	}
