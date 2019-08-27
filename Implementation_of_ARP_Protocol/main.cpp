#include<iostream>
#include<sstream>
#include<fstream>

using namespace std;
int ARP()
{

	fstream f("ip_mac_database.txt");
	string IP_address, line, MAC_address, IP;
	cout<< "Enter the IP_address:";
	cin>> IP_address;
	
	//check whether the file is open or not
	if(!f.is_open())
	{
		cout<< "!!!!!!!!Unable to open the file!!!!!!!!!!";
		return 0;
	}
	
	while(getline(f,line))
	{
		stringstream ss(line);
		getline(ss, IP, ' ');
		if(IP == IP_address)
		{
			getline(ss, MAC_address, '\n');
			cout<< MAC_address;
			return 0;
		}
	}
	
	cout<<"You are not connected with this IP address";
return 0;
}

int main()
{
	ARP();
return 0;
}
