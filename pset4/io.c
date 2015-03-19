#include <stdio.h>

int main(void)
{
    char buffer[100], tmp;
    int i=0;
    do
    {
        tmp = getchar();
        if(tmp == '\n')
        {
            buffer[i] = '\0';
            i = 100;
        }
        else
        	buffer[i] = tmp;
        	
        i++;
    }
    while(i < 100);
    
    printf("%s\n", buffer);
}
