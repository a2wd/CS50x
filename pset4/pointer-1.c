#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int n;
    struct node* next;
} node;

int main(void)
{
    node first;
    
    first.n = 123;
    printf("%i\n", first.n);
    
    first.next = malloc(sizeof(node));
    node* next;
    next = first.next;
    
    next->n = 456;
    printf("%i\n", next->n);
    
    return 0;
}
