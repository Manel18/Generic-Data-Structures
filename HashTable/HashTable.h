#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct htable* HashTable;

typedef void (*Updater) (void**, void*);
typedef int (*Comparator) (void *, void *); /* Compara dois values */
typedef void* (*Cloner) (void *);
typedef void (*Freer) (void *); /* Liberta a memória dos values */
typedef int (*HashFunc) (HashTable, void *);

typedef void* Key;
typedef void* Value;

/*
 * Allocates the necessary memory for an HashTable of size passed as argument.
 */
HashTable HT_create(unsigned int, float, Updater, Comparator, Cloner, Cloner, HashFunc, Freer, Freer);

/*
 * Puts the pair passed as argument in the HashTable.
 */
void HT_put(HashTable, Key, Value);

/*
 * Returns the Value associated with the key passed as an argument.
 */
void* HT_get(HashTable, Key);

/* 
 * Removes the pair associated with the Key, passed 
 * as an argument, from the HashTable.
 */
void HT_remove(HashTable, Key);

/* 
 * Returns the size of the HashTable. 
 */
int HT_size(HashTable);

/*
 * Returns how many pairs Key|Value are in the HashTable
 */
int HT_load(HashTable);

/* 
 * Free all the memory allocated for the HashTable structure.
 */
void HT_free(HashTable);

/* 
 * Returns an array of all the Keys.
 */
void** HT_keys(HashTable);

/* 
 * Returns an array of all the Values.
 */
void** HT_values(HashTable);

#endif
