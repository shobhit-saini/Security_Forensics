#include<iostream>
#include<string.h>
using namespace std;
int main()
{
	string msg,crc,encoded="";
	cout<<"Enter the msg";
	getline(cin,msg);
	cout<<"Enter the CRC generator:";
	getline(cin,crc);
	int m=msg.length(),n=crc.length();
	encoded+=msg;
	for(int i=0;i<n-1;i++)
	{
		encoded+='0';
	}
	for(int i=0;i<=encoded.length()-n;)
	{
		for(int j=0;j<n;j++)
		{
			encoded[i+j]=encoded[i+j]==crc[j]? '0':'1';
			//encoded[i+j]=(encoded[i+j]^crc[j]);
	 	}
			for(;i<encoded.length()&&encoded[i]!='1';i++);
	}
	cout<<encoded.substr(encoded.length()-n+1);
	
}
