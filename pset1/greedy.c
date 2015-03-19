#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    int i = -1;
    int coins = 0;
    do
    {
        printf("Enter the amount of change to calculate: ");
        float f = GetFloat();    
        i = round(f * 100);
    }
    while(i < 0);
    
    //Counting coins
    while(i>=25)
    {
        i -=25;
        coins++;
    }
    while(i>=10)
    {
        i -= 10;
        coins++;
    }
    while(i>=5)
    {
        i-= 5;
        coins++;
    }

    //Add remaining cents
    coins += i;
    
    printf("%d\n",coins);
    
    return 0;
}
