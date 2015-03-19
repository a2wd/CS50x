/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    //Initialise counter to index the word[] array and a temporary ch
    int counter=0;
    int ch;
    node* this = root;
    
    //If there is no word or dictionary, return false
    if(word == NULL || this == NULL)
        return false;
    
    //Iterate till end of word
    while(word[counter] != '\0')
    {
        //Handle case sensitivity & apostrophe
    	if(word[counter] >= 'A' && word[counter] <= 'Z')
    	    ch = (int) (word[counter] - 'A');
    	else if(word[counter] == '\'')
    	    ch = LETTERS-1;
    	else if(word[counter] >= 'a' && word[counter] <= 'z')
    	    ch = (int) (word[counter] - 'a');
    	else
    	    return false;
    	
    	if(this->link[ch] == NULL)
    	    return false;
    	else    
            this = this->link[ch];
    	    
        counter++;
    }
    
    //Check this node is a word
    if(this->word == true)
        return true;
    else
        return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    //Begin by opening a file pointer to dictionary
    FILE* dict = fopen(dictionary, "r");
    if(dict == NULL)
    {
        printf("Unable to load dictionary at %s\n", dictionary);
        return false;
    }
    
    //Malloc memory for root
    root = malloc(sizeof(node));
    
    //Initialise dict_items variable to track number of words
    dict_items = 0;
    
    //Process each word (assumed one per line, of maximum length given in LENGTH)
    char word[LENGTH+1];
    int index = 0;
    
    while((word[index++] = fgetc(dict)) != EOF)
    {
        if(word[index-1] == '\n')
        {
            word[index-1] = '\0';
            index = 0;
            
            //Add word[] to the trie struct
            //add() returns false on error
            if(!add(word))
            {
                fclose(dict);
                return false;
            }
        }
    }
    
    fclose(dict);
    
    return true;
}

// Adds next word to trie
bool add(char* word)
{
    //Check word is not a null pointer
    if(word == NULL)
        return false;
        
    node* this = root;
    int index = 0;
    
    while(word[index] != '\0')
    {
    	//Transform a character to a value 0-27 (a-z & ')
        if(word[index] == '\'')
            word[index] = LETTERS - 1;
        else
            word[index] -= 'a';
            
        //Check if we need to malloc any new nodes
        if(this->link[(int)word[index]] == NULL)
            this->link[(int)word[index]] = malloc(sizeof(node));
        
        //Move on to next node
        this = this->link[(int)word[index]];
        
        //Increment counter for word[] array
        index++;
    }
    this->word = true;
    dict_items++;
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if(root != NULL)
        return dict_items;
    else
        return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    if(root == NULL)
    {   
        return false;
    }
    else
    {
        node* next;
        
        for(int x=0; x<LETTERS; x++)
        {
            next = root->link[x];
            if(next != NULL)
            {
                unload_recursive(next);
                free(next);
            }
        }
    }
    
    free(root);
    
    return true;
}

void unload_recursive(node* this)
{
    node* next;
    
    for(int x=0; x<LETTERS; x++)
    {
        if(this->link[x] != NULL)
        {
            next = this->link[x];
            unload_recursive(next);
            free(next);
        }
    }
}
