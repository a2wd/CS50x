#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int* p = malloc(sizeof(int));
    *p = 234;
    
    printf("%i is pointed to and at address %p\n", *p, p);
    
    return 0;
}
