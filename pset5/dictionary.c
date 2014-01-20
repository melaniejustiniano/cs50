/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// hash function

unsigned int hash(const char *word)
{
    // start hash at the prime number 5381
    unsigned long hash = 5381;
    int c;

    // iterate through each letter of the word
    while ((c = *word++))
        //bitwise left shift 5, add hash, add c
        hash = ((hash << 5) + hash) + c;

    // make sure our hash is in the array
    return hash % BUCKETS;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // makes lowercase version of word
    // this is because hash functions are stupid
    char lowercase[LENGTH + 1];
    for (int i = 0, n = strlen(word) + 1; i < n; i++)
    {
        if (isupper(word[i]))
            lowercase[i] = tolower(word[i]);
        else
            lowercase[i] = word[i];
    }
    
    int bucket = hash(lowercase);
    
    // create node to traverse list
    node* checker = hashtable[bucket];
    
    // compare word to checker
    while (checker != NULL)
    {
        if (strcasecmp(checker->word, lowercase) == 0)
        {
            // if word is the same as checker
            return true;
        }
        
        else
        {
            // checker is next word in dictionary
            checker = checker->next;
        }
    }
    
    // if word not found in dictionary
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
 
// counter for size of dictionary
int dictionarysize = 0; 
 
bool load(const char* dictionary)
{    
    // open dictionary
    FILE* file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open %s!", dictionary);
        return false;
    }
    
    // load dictionary into hash table
    while (true)
    {
        // create memory location for node
        node* nodes = malloc(sizeof(node));
        if (nodes == NULL)
        {
            printf("Could not create node!");
            return false;
        }
        
        // break out of loop at end of file or error
        if (fscanf(file, "%s", nodes->word) == EOF)
        {
            free(nodes);
            break;
        }
        
        // put word into hash table
        else
        {
            // hash word
            int bucket = hash(nodes->word);
            
            // put into hash table
            nodes->next = hashtable[bucket];
            hashtable[bucket] = nodes;

            // count nodes (words in dictionary)
            dictionarysize++;
        }
    }
    
    // close dictionary file
    fclose(file);
    return true;
}


/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dictionarysize;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // for each bucket
    for (int i = 0; i < BUCKETS; i++)
    {
        // free nodes without memory leaks
        node* anchor = hashtable[i];
        while (anchor != NULL)
        {
            node* nodes = anchor;
            anchor = anchor->next;
            free(nodes);
        }
    }

    return true;
}
