#include <stdlib.h>
#include "HashTable.h"

/*
 * Info: Currently developing the open address version;
 *
 * TODO: A closed addressing version | Read all of what Introduction to Algorithms has to say about Hash Tables;
 *       We'll have to add a way for the user to choose what kind of addressing he wants;
 */

#define O 1 /* Entry Occupied */
#define F 0 /* Entry Free */
#define R 2 /* Entry Removed */

typedef struct pair
{
	void* key;
	void* value;
}Pair;

typedef struct entry
{
	char flag;
	Pair* pair;
}Entry;

typedef struct htable
{
	unsigned int size;
	unsigned int load;
	float loadfactor;
	Entry** table; /* Quero um  array de apontadores para Entry ou array de Entry!? */ 
	Updater update;
	Comparator compare;
	Cloner clone;
	HashFunc hash;
	Freer free;
}HTable;

static Entry* HT_createEntry(void* key, void* value);

HTable* HT_create(unsigned int size, float lf, Updater update, Comparator compare, Cloner clone, HashFunc hash, Freer free)
{
	HTable* htable = malloc(sizeof(struct htable));
	htable->size = size;
	htable->load = 0;
	htable->loadfactor = lf;
	htable->table = malloc(sizeof(Entry*)*size);
	htable->update = update;
	htable->compare = compare;
	htable->clone = clone;
	htable->hash = hash;
	htable->free = free;

	return htable;
}

static Entry* HT_createEntry(void* key, void* value)
{
	Entry* new_entry = malloc(sizeof(Entry));
	new_entry->flag = O;
	new_entry->pair = malloc(sizeof(Pair));
	new_entry->pair->key = key;
	new_entry->pair->value = value;

	return new_entry;
}

void HT_put(HTable* ht, void* key, void* value)
{
	int hash;
	int i;
	
	ht->load += 1;

/*  TODO: Uncomment when HT_rehash is done
	float alfa = ht->load / ht->size;
	if(alfa >= ht->loadfactor) HT_rehash(ht);
*/
	hash = ht->hash(ht, key);
	i = hash;
	while(ht->table[i]->flag == O)
	{
		i = (i+1) % ht->size;
		if(i == hash) break;
	}

	/* If i == hash then we need to rehash but thats never gonna happen 
	   because we check the load before we put something in the table,
	   and if we need to, we rehash... before
	 */
	
	ht->table[i] = HT_createEntry(key, ht->clone(value));

}

void* HT_get(HTable* ht, void* key)
{
	int hash = ht->hash(ht, key);
	i = hash;
	void* ret = null;

	while(ht->table[i]->flag != F && !ret)
	{
		if(ht->compare(ht->table[i]->pair->key, key))
			ret = ht->clone(ht->table[i]->pair->value);

		i = (i+1) % ht->size;
		if(i == hash) break;
	}

	if(i == hash || ht->table[i]->flag == F) return null;
	else return ht->clone(ht->table[i-1]->pair->value);
}

void HT_remove(HTable* ht, void* key)
{
	int hash = ht->hash(ht, key);
	i = hash;
	void* ret = null;

	while(ht->table[i]->flag != F && !ret)
	{
		if(ht->compare(ht->table[i]->pair->key, key))
			ret = ht->clone(ht->table[i]->pair->value);

		i = (i+1) % ht->size;
		if(i == hash) break;
	}

	if( i == hash || ht->table[i]->flag == F) return;
	else
	{
	}
}
