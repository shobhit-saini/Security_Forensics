#include<iostream>
#include<string.h>
using namespace std;
int swap(char *a, char *b)
{
    char temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    char k[1000], p[1000];
    int i;
    cout << "Enter the key:";
    cin >> k;
    cout << "Enter the Plain text:";
    cin >> p;
    char s[256];
    ///////////////KSA////////////////////////////
   
    for(i = 0; i < 256; i++)
    {
        s[i] = i;
    }
   
    int j = 0;
    for(int i = 0; i < 255; i++)
        {
            j = (j + s[i] + k[i%strlen(k)])% 256;
               swap(&s[i], &s[j]);
        }
       
        //////////////PRGA////////////////////////
       
    i = 0, j = 0;
   
    int len = strlen(p);
    char c[len], key[len];
    int l = 0, m = 0, t;
    while (m != len)
    {
        i = (i + 1)% 256;
        j = (j + s[i])% 256;     
        swap(&s[i], &s[j]);
        t = (s[i] + s[j])% 256;
        key[m] = s[t];
        c[m] = p[m] ^ key[m];
        m++;
    }
   
    //////////////Decryption////////
    char d[1000];
    m = 0;
    cout << "Decrypted message:";
    while (m != len)
    {
        d[m] = c[m] ^ key[m];
        cout << d[m];
        m++;
    }

}

