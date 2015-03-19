#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cs50.h>

typedef struct node {
    int n;
    struct node* next;
} node;

void add(int i, node *ptr);

int main(void)
{
    bool exit = false;
    node* ptr = NULL;
    
    while(!exit)
    {
        printf("Menu:\n");
        printf("1. Add an int\n");
        printf("2. Quit\n");
        int i = GetInt();
        
        switch(i)
        {
            case 1: add(i, ptr); break;
            case 2: exit = true; break;
        }
    }
    
    return 0;
}

void add(int i, node* ptr)
{
    if(ptr == NULL)
    {
        printf("Null pointer\n");
        exit(1);
    }
    node* last = ptr;
    while(ptr->next != NULL)
    {
        if(ptr->n >= i)
        {
            node* tmp = last;
            ptr->last->
        }
    }
}

