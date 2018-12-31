// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

int wordcount = 0;

typedef struct node
{
    bool is_word;
    struct node *children[27];
} node;

node *root;

void unload_ed(node *cursor)
{
    if(cursor == NULL)
        return;
    
    for(int i = 0; i < 27; i++)
    {
        unload_ed(cursor -> children[i]);
    }
    free(cursor);
}

node *node_init(void)
{
    node *sampnode = (node *)malloc(sizeof(node));
    if(!sampnode)
    {
        return NULL;
    }
    
    sampnode -> is_word = false;
    
    for(int i = 0; i < 27; i++)
    {
        sampnode -> children[i] = NULL;
    }
    
    return sampnode;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *cursor = root;
    for(int i = 0; word[i] != '\0'; i++)
    {
        int bindex = index(word[i]);
        if(cursor -> children[bindex] != NULL)
        {
            cursor = cursor -> children[bindex];
        }
        else
        {
            return false;
        }
    }
    if (cursor -> is_word == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (!dict)
    {
        return false;
    }
    
    root = node_init();
    if (!root)
    {
        return false;
    }
    
    node *cursor = NULL;
    
    int filecursor = 0;
    
    while((filecursor = fgetc(dict)) != EOF)
    {
        cursor = root;
        
        for(; filecursor != '\n'; filecursor = fgetc(dict))
        {
            int bindex = index(filecursor);
            if((cursor -> children[bindex]) == NULL)
            {
                cursor -> children[bindex] = node_init();
                if(!cursor -> children[bindex])
                {
                    return false;
                }
                cursor = cursor -> children[bindex];
            }
            else
            {
                cursor = cursor -> children[bindex];
            }
        }
        cursor -> is_word = true;
        wordcount++;
    }
    
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (wordcount != 0)
    {
        return wordcount;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *cursor = root;
    unload_ed(cursor);
    return true;
}

int index(int letter)
{
    if(letter == (int)'\'')
    {
        return 26;
    }
    else
    {
        return tolower((char)letter) - 'a';
    }
}