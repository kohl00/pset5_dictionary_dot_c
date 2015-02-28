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
        if(isalpha(word[i])){
            n = word[i] - 'a' + 1;
        
        // ....comma
        }else{
            n = 27;
        }   
        hash_place = ((hash_place << 3) + n) % SIZE;
    }
    return hash_place;    
}

//counter for size 
  int dict_Size = 0;

bool check(const char* word)
{
    //store a lower-cased version of the word
   char tmp[LENGTH + 1];
   int len = strlen(word);
   for(int i = 0; i < len; i++){
        tmp[i] = tolower(word[i]);
   }
   tmp[len] = '\0'; //null term at end
    // find index of tmp in hash function
   int index = hash(tmp);
    // if hashtable is empty at index, return false
   if (hash_table[index] == NULL)
   {
     return false;
   }
    // compare to word
   node* comparer = hash_table[index];
    // if hashtable is not empty at index, iterate through words and compare
   while(comparer != NULL){
     if(strcmp(tmp, comparer->word) == 0){
       return true;
     }
     comparer = comparer->next;
   }
    // not there, return false
   return false;
  //  
}

 // Loads dictionary into memory.true if successful else false.
bool load(const char* dictionary)
{
     // open
  FILE* fp = fopen(dictionary, "r");
  if (fp == NULL){
     return false;
  }
    // create an array for word to be stored in
  char word[LENGTH+1]; 
    // scan through the file, loading each word into the hash table
  while (fscanf(fp,"%s\n",word) != EOF){
    dict_Size++;  
    // allocate memory for new word 
    node* add_word = malloc(sizeof(node));
        // put word in the new node
    strcpy(add_Word->word, word);
        // find what index of the array the word should go in
    int index = hash_place(word);
        // if hashtable is empty at index, insert
    if (hash_table[index] == NULL){
        hash_table[index] = add_word;
        add_word->next = NULL;
     }else{ // not empty,append node/word
        add_word->next = hash_table[index];
        hash_table[index] = add_word;
     }      
  }
    // close the open file
  fclose(fp);
    // and return true 
  return true;

}
 //Returns # of words in dictionary if loaded else 0 if not yet loaded.
unsigned int size(void)
{
    // 2DO
  if (dict_Size > 0){
   return dict_Size;
      //returns the size
  }else{
   return 0;
  }
}

// Unloads dictionary from memory.  Returns true if successful else false.

bool unload(void){
    // create a variable to go through index
  int point = 0;
    
    // iterate through entire hashtable array
    // SIZE constant defined up top.
  while (point < SIZE){
        // if empty at index, next
     if (hash_table[point] == NULL){
          point++;
     }else{
       // if hashtable not empty, iterate start freeing
       // once empty, go to next index
       while(hash_table[point] != NULL){
         node* comparer = hash_table[point];
         hash_table[point] = comparer->next;
         free(comparer);
       }
        point++;
      }
    }
    return true;
}
