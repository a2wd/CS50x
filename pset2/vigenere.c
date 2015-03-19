#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <cs50.h>

string rotate(int key[], int teeth, string s);

int main(int argc, char *argv[])
{
    //For a ciphertext, C[i] = (P[i] + k) % 26
    //Eg, k or key = 13 for rot13

    if(argc != 2)
    {
        printf("This program rotates a plaintext through a key as in C[i] = (P[i] + k[i]) %% 26\n");
        printf("and requires exactly one command-line parameter, k\n");
        return 1;
    }

    //No need to check for 0 length key - we have already checked that there is an argument!
    string key = argv[1];
    int teeth = strlen(key);
    int k[teeth];
    for(int x=0; x<teeth; x++)
    {
        if(isupper(key[x]))
        {
            k[x] = key[x] - 'A';
        }
        else if(islower(key[x]))
        {
            k[x] = key[x] - 'a';
        }
        else
        {
            printf("Please enter an alphanumeric key for k\n");
            return 1;
        }
    }    
    string s = GetString();
    
    s = rotate(k, teeth, s);
    printf("%s\n",s);
    
    return 0;
}

string rotate(int key[], int teeth, string s)
{
    int t = 0;   
    for(int x=0; x<strlen(s); x++)
    {
        if(isalpha(s[x]))
        {
            if(islower(s[x]) && (s[x]+key[t]) > 'z')
                s[x] -= 26;        
            else if(isupper(s[x]) && (s[x]+key[t]) > 'Z')
                s[x] -= 26;                

            s[x] += key[t];
            t++;
            
            //Handle longer plaintext than key
            if(t>=teeth)
                t %= teeth;
        }
    }
    return s;
}
