#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct linkedlist* LinkedList;

typedef int (*Comparator) (const void*, const void *);

typedef void* (*Cloner) (const void*);

typedef void (*Freer) (void *);

void teste();

LinkedList LL_create(Comparator, Cloner, Freer); /* creates a generic linked list with a comparator a cloner and a freer */ 

void LL_free(LinkedList);

void LL_insert(LinkedList, void*); /* Standard insert function, inserts at the head of the list */

void LL_remove(LinkedList, void*); /* removes the first occurence equal to the data passed by argument */  

void LL_removePos(LinkedList, int); /* removes node at position passed by argument */

int LL_lookUp(LinkedList, void*); /* checks if a certain data passed by argument is present in the list */ 

void* LL_peek(LinkedList); /* returns the data stored in the first node of the list */

int LL_size(LinkedList); /* returns the size of the list */

/* I did this because i wanted to iterate over the list a print the elements but i couldnt because its encapsulated*/
void** LL_getData(LinkedList); /* returns the data of all nodes inside an array */  

#endif
