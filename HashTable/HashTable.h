#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct htable* HashTable;

typedef void (*Updater) (void *, void *);
typedef int (*Comparator) (void *, void *);
typedef void (*Cloner) (void *);
typedef void (*Freer) (void *);
typedef int (*HashFunc) (HashTable, void *);

typedef void* Key;
typedef void* Value;

HashTable HT_create(unsigned int, float, Updater, Comparator, Cloner, HashFunc, Freer);

void HT_put(HashTable, Key, Value);

void* HT_get(HashTable, Key);

void HT_remove(HashTable, Key);

#endif
