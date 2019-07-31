#include<iostream>
#include<string>
#include<sstream>
using namespace std;
int main()
{
	string msg,crc,encoded="",res;
	cout<<"Enter the msg";
	getline(cin,msg);
	cout<<"Enter the CRC generator:";
	getline(cin,crc);
	int m=msg.length(),n=crc.length();
	for(int i=0;i<=msg.length()-n;)
	{
		for(int j=0;j<n;j++)
		{
			msg[i+j]=msg[i+j]==crc[j]? '0':'1';
	 	}
			for(;i<msg.length()&&msg[i]!='1';i++);
	}
		cout<<msg;
		int res1=0;
		stringstream res(msg);
		res >> res1;
		if(res1==0)
		{
			cout<<"No Error";
		}	
		else
		{
			cout<<"Error";
		}
}
