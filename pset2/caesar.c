#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <cs50.h>

string rotate(int key, string s);

int main(int argc, char *argv[])
{
    //For a ciphertext, C[i] = (P[i] + k) % 26
    //Eg, k or key = 13 for rot13

    if(argc != 2)
    {
        printf("This program rotates a plaintext through a key as in C[i] = (P[i] + k) %% 26\n");
        printf("and requires exactly one command-line parameter, k\n");
        return 1;
    }
    int k = atoi(argv[1]);
    if(k < 0)
    {
        printf("Enter a key, k greater than 0\n");
        return 1;
    }
    
    string s = GetString();
    
    s = rotate(k, s);
    printf("%s\n",s);
    
    return 0;
}

string rotate(int key, string s)
{
    key %= 26;
    for(int x=0; x<strlen(s); x++)
    {
        if(isalpha(s[x]))
        {
            if(islower(s[x]) && (s[x]+key) > 'z')
                s[x] -= 26;        
            else if(isupper(s[x]) && (s[x]+key) > 'Z')
                s[x] -= 26;                

            s[x] += key;
        }
    }
    return s;
}
