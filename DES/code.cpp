#include<bits/stdc++.h> 
using namespace std;
 string hex2bin(string s){ 
   // hexadecimal to binary conversion 
    map<char, string> mp; 
    mp['0']= "0000"; 
    mp['1']= "0001"; 
    mp['2']= "0010"; 
    mp['3']= "0011"; 
    mp['4']= "0100"; 
    mp['5']= "0101"; 
    mp['6']= "0110"; 
    mp['7']= "0111"; 
    mp['8']= "1000"; 
    mp['9']= "1001"; 
    mp['A']= "1010"; 
    mp['B']= "1011"; 
    mp['C']= "1100"; 
    mp['D']= "1101"; 
    mp['E']= "1110"; 
    mp['F']= "1111"; 
    string bin=""; 
    for(int i=0; i<s.size(); i++){ 
        bin+= mp[s[i]]; 
    } 
    return bin; 
} 
string initial_perm(string pt)
{
	string per = "";int i;
		//Initial Permutation Table 
   int initial_perm[64]=  
   {    58,50,42,34,26,18,10,2, 
        60,52,44,36,28,20,12,4, 
        62,54,46,38,30,22,14,6, 
        64,56,48,40,32,24,16,8, 
        57,49,41,33,25,17,9,1, 
        59,51,43,35,27,19,11,3, 
        61,53,45,37,29,21,13,5, 
        63,55,47,39,31,23,15,7 
    };
   for(i = 0; i < 64; i++)
 	{
 		per+= pt[initial_perm[i]-1]; 
 	}
 	return per;
}

string Expansion_permutation(string pt)
{
	 //Expansion D-box Table 
    int exp_d[48]=  
    {    32,1,2,3,4,5,4,5, 
        6,7,8,9,8,9,10,11, 
        12,13,12,13,14,15,16,17, 
        16,17,18,19,20,21,20,21, 
        22,23,24,25,24,25,26,27, 
        28,29,28,29,30,31,32,1 
    };
    
}
int main()
{
	string pt, key;
	char p[64];
	int i;
	//cout << "Enter plain_text in hex:";
	pt = "123456ABCD132536"; 
	key = "AABB09182736CCDD";

    pt = hex2bin(pt);
    cout << pt << "\n";
 	
	pt = initial_perm(pt);
	//Splitting the plain text into two halves 
    string left= pt.substr(0, 32); 
    string right= pt.substr(32, 32);
    

    
      
}
