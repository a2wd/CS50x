#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int x = 0;
    do
    {
        printf("Enter an integer between 1 and 23: ");
        x = GetInt();
        if(x==0)
        {
            return 0;
        }
    }
    while(x>23 || x<1);
    
    for(int y = 0; y < x; y++)
    {
        for(int z = 1; z < (x-y); z++)
            printf(" ");
            
        for(int z = 0; z < y; z++)
            printf("#");

        printf("##\n");
    }   
    
    return 0;
}
