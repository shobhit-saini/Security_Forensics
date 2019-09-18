#include<iostream>
#include<fstream>
#include<sstream>
#include<string.h>
using namespace std;
int main()
{
	ifstream Myfile("out.tr");
	  if(!Myfile.is_open())
	  {
	  	cout<<"File  can't be open";
	  }
	  string a;
	  string b ,str1;
	  string line;
	  int drop = 0, packet = 0;
	  while(getline(Myfile,line))
	  {
	  	stringstream ss(line);//Used to divide into words
	  	getline(ss,a,' ');
	  	getline(ss,b,'\n');
	  	if(strcmp(a.c_str(),"d") == 0)
	  	{
	  		drop++;
	  	}
	  	packet++;
	  }
	 cout<< "No. of packets drop:" << drop <<"\n";
	 cout<< "Total no. of packets are:" << packet<<"\n";
}
