#include<iostream>
#include<string.h>
#include <bits/stdc++.h> 

using namespace std;
int main()
{
	string msg,crc,encoded="",bin_msg="",str1="",bin_msg1="";
	int i,val,len,j;
	cout<<"Enter the msg";
	getline(cin,msg);
	for(i=0;i<msg.length();i++)
	{
	    val=(int)msg[i];
	    bin_msg="";
	 // Convert ASCII value to binary 
        while (val > 0) 
        { 
         
            (val % 2)? bin_msg.push_back('1') : 
                       bin_msg.push_back('0'); 
            val /= 2; 
        } 
       reverse(bin_msg.begin(), bin_msg.end());
       bin_msg1+=bin_msg; 
        
    }
  cout<<bin_msg1<<endl;
	cout<<"Enter the CRC generator:";
	getline(cin,crc);
	int m=msg.length(),n=crc.length();
	encoded+=bin_msg1;
	for(i=0;i<n-1;i++)
	{
		encoded+='0';
	}
	for( i=0;i<=encoded.length()-n;)
	{
		for(int j=0;j<n;j++)
		{
			encoded[i+j]=encoded[i+j]==crc[j]? '0':'1';
	 	}
			for(;i<encoded.length()&&encoded[i]!='1';i++);
	}
	bin_msg1.append(encoded.substr(encoded.length()-n+1));
	//cout<<encoded.substr(encoded.length()-n+1);
	cout<<"newmsg:"<<bin_msg1;
	
}
