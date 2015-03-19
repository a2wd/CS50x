/****************************************************************************
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Declares a dictionary's functionality.
 ***************************************************************************/

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

//Number of letters to point to in trie - 26 alphabetical plus apostrophe (')
#define LETTERS 27

/**
 *  We will use a trie to store the words in this dictionary
 */
typedef struct node
{
    bool word;
    struct node* link[LETTERS];
} node;
 
node* root;


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

//To speed up size, we will calculate number of words when loading dictionary
//And store it in the global variable dict_items
unsigned int dict_items;

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

//Helper function for unload - recursive function that takes a node* as input
void unload_recursive(node* this);

/**
 * Add() takes a character string and adds it to the node* dictionary.
 * Returns true is successful, false if not
 */
bool add(char* word);

#endif // DICTIONARY_H
