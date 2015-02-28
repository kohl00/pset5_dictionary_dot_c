/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>

#include "dictionary.h"

// arb size of hash
#define SIZE 1000000 

// linked list
typedef struct node
{
    char word[LENGTH+1];
    struct node* next;
}
node;

// creation of hashtable. set to null
node* hash_table[SIZE] = {NULL};

// hash function // http://www.cse.yorku.ca/~oz/hash.html
int hash(const char* word)
{
    int hash_place = 0;
    int n;
    for (int i = 0; word[i] != '\0'; i++)
    {
        // if is a letter
        if(isalpha(word[i]))
            n = word[i] - 'a' + 1;
        
        // ....comma
        else
            n = 27;
            
        hash_place = ((hash_place << 3) + n) % SIZE;
    }
    return hash_place;    
}

//counter for size of the dictionary
int dict_Size = 0;

bool check(const char* word)
{
    //2DO
    //store a lower-cased version of the word
    char tmp[LENGTH + 1];
    int len = strlen(word);
    for(int i = 0; i < len; i++)
        tmp[i] = tolower(word[i]);
        
    tmp[len] = '\0'; //null term at end
    
    // find index of tmp in hash function
    int index = hash(tmp);
    
    // if hashtable is empty at index, return false
    if (hash_table[index] == NULL)
    {
        return false;
    }
    
    // create cursor to compare to word
    node* cursor = hash_table[index];
    
    // if hashtable is not empty at index, iterate through words and compare
    while (cursor != NULL)
    {
        if (strcmp(tmp, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    // not there, return false
    return false;
    
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // 2DO
     // open
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL){
        return false;
    }
    // create an array for word to be stored in
    char word[LENGTH+1];
    
    // scan through the file, loading each word into the hash table
    while (fscanf(fp,"%s\n",word) != EOF)
    {
        // increment dictionary size
        dict_Size++;
        
        // allocate memory for new word 
        node* newWord = malloc(sizeof(node));
        
        // put word in the new node
        strcpy(newWord->word, word);
        
        // find what index of the array the word should go in
        int index = hash_place(word);
        
        // if hashtable is empty at index, insert
        if (hash_table[index] == NULL)
        {
            hash_table[index] = newWord;
            newWord->next = NULL;
        }
        
        // not empty at index, append
        else
        {
            newWord->next = hash_table[index];
            hash_table[index] = newWord;
        }      
    }
    
    // close file
    fclose(fp);
    
    // return true 
    return true;

}

 //Returns # of words in dictionary if loaded else 0 if not yet loaded.
unsigned int size(void)
{
    // 2DO
    if (dict_Size > 0)
    {
      return dict_Size;
    }
    else{
        return 0;
   }
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // 2DO
    // create a variable to go through index
    int index = 0;
    
    // iterate through entire hashtable array
    // SIZE constant defined up top.
    while (index < SIZE)
    {
        // if empty at index, next
        if (hash_table[index] == NULL)
        {
            index++;
        }
        // if hashtable not empty, iterate start freeing
        // once empty, go to next index
        else
        {
          while(hash_table[index] != NULL)
          {
            node* cursor = hash_table[index];
            hash_table[index] = cursor->next;
            free(cursor);
          }
           index++;
        }
    }
    // return true if successful
    return true;
}
