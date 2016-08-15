#include <stdlib.h>
#include "HashTable.h"

/*
 * Info: Currently developing the open address version;
 *
 * TODO: A closed addressing version | Read all of what Introduction to Algorithms has to say about Hash Tables;
 *       We'll have to add a way for the user to choose what kind of addressing he wants;
 *		 Resolver o problema das key's (não devia ser preciso pedir uma função de free e clone para key's e value's)
 */

#define O 1 /* Entry Occupied */
#define F 0 /* Entry Free */
#define R 2 /* Entry Removed */

typedef struct entry
{
	char flag;
	void* key;
	void* value;
}Entry;

typedef struct htable
{
	unsigned int size;
	unsigned int load;
	float loadfactor;
	Entry** table; 
	Updater update;
	Comparator compare;
	Cloner cloneV;
	Cloner cloneK;
	HashFunc hash;
	Freer freeV;
	Freer freeK;
}HTable;

static void HT_createEntry(Entry* e, void* key, void* value);
static Entry* HT_initEntry();
static void HT_rehash(HTable*);
static void HT_freeEntry(HashTable, Entry*);

HTable* HT_create(unsigned int size, float lf, Updater update, Comparator compare, 
				  Cloner cloneV, Cloner cloneK, HashFunc hash, Freer freeV, Freer freeK)
{
	int i;
	HTable* htable = malloc(sizeof(struct htable));
	htable->size = size;
	htable->load = 0;
	htable->loadfactor = lf;
	htable->table = malloc(sizeof(Entry*)*size);
	htable->update = update;
	htable->compare = compare;
	htable->cloneV = cloneV;
	htable->cloneK = cloneK;
	htable->hash = hash;
	htable->freeV = freeV;
	htable->freeK = freeK;

	for(i = 0; i < size; i++)
		htable->table[i] = HT_initEntry();

	return htable;
}

void HT_free(HashTable ht)
{
	int i;
	for(i = 0; i < ht->size; i++)
	{
		HT_freeEntry(ht, ht->table[i]);
	}

	free(ht->table);
	free(ht);
}

static void HT_freeEntry(HashTable ht, Entry* e)
{
	if(e->flag != O)
		free(e);
	else
	{
		ht->freeK(e->key);
		ht->freeV(e->value);
		free(e);
	}
}

static Entry* HT_initEntry()
{
	Entry* e = malloc(sizeof(Entry));
	e->flag = F;
	e->key = NULL;
	e->value = NULL;

	return e;
}

static void HT_createEntry(Entry* e,void* key, void* value)
{
	e->flag = O;
	e->key = key;
	e->value = value;
}

void HT_put(HTable* ht, void* key, void* value)
{
	int hash;
	int count = ht->size;
	
	ht->load += 1;

	float alfa = ht->load / ht->size;
	if(alfa >= ht->loadfactor) HT_rehash(ht);

	hash = ht->hash(ht, key);
	while(ht->table[hash]->flag == O && count--)
	{
		if(ht->compare(ht->table[hash]->key, key))
		{
			ht->update(&(ht->table[hash]->value), value);
			return;
		}
		hash = (hash+1) % ht->size;
	}
	/* If i == hash tqqhen we need to rehash but thats never gonna happen 
	   because we check the load before we put something in the table,
	   and if we need to, we rehash... before */
	
	HT_createEntry(ht->table[hash],ht->cloneK(key), ht->cloneV(value));

}

static void HT_rehash(HTable* ht)
{
	int i, j;
	int hash;
	int old_size = ht->size;
	Entry** old_table = ht->table;
	
	Entry** new_table = malloc(sizeof(Entry*) * ht->size * 2);
	for(j = 0; j < ht->size * 2; j++) new_table[j] = HT_initEntry();
	
	/* Setting new table and adjusting the size and used vars */
	ht->table = new_table;
	ht->size *= 2;
	/* 
	 * We set ht->load to 1 because, if we think about it, we call rehash in HT_put after we increment ht->load
	 * and then, here we loop throught the old_table and put the entry on the new using HT_put
	 * HT_put increments ht->load, so because we havent yet inserted the new element on the table
	 * when we finish rehashing, ht->load was incremented by the amount of entries on the old table, i.e.
	 * ht->load would have it's old value. So if we have to make ht->load, 1. Because when rehash finishes
	 * and we go back to HT_put in the stack we insert the new element in the new rehashed table but we never
	 * incremented the load for that entry, so we set it here to one to account for the new entry.
	 * Hope that makes sense xD
	 */
	ht->load = 1;

	for(i = 0; i < old_size; i++)
	{
		if(old_table[i]->flag == O)
		{
			HT_put(ht, old_table[i]->key, old_table[i]->value);
			HT_freeEntry(ht, old_table[i]);
		}
	}

	free(old_table);
}

void* HT_get(HTable* ht, void* key)
{
	int hash = ht->hash(ht, key);
	int counter = ht->size;
	void* ret = NULL;

	while(ht->table[hash]->flag != F && counter--)
	{
		if(ht->compare(ht->table[hash]->key, key))
		{
			ret = ht->cloneV(ht->table[hash]->value);
			break;
		}

		hash = (hash+1) % ht->size;
	}

	if(ht->table[hash]->flag == F || !ret) 
		return NULL;
	else 
		return ret;
}

void HT_remove(HTable* ht, void* key)
{
	int hash = ht->hash(ht, key);
	int count = ht->size;
	void* ret = NULL;

	while(ht->table[hash]->flag != F && count--)
	{
		if(ht->compare(ht->table[hash]->key, key))
		{
			ret = ht->table[hash]->value;
			break;
		}
		hash = (hash+1) % ht->size;
	}

	if( ht->table[hash]->flag == F || !ret) return;
	else
	{
		/* CHANGE FLAG TO R */
		ht->table[hash]->flag = R; 
		
		/* Free memory */
		ht->freeK(ht->table[hash]->key);
		ht->freeV(ht->table[hash]->value);
		
		/* Default to NULL */
		ht->table[hash]->key = NULL;
		ht->table[hash]->value = NULL;
	}
}

/*
 * We need to provide a func to get the table 
 * size so that the user can make a hash func
 */
int HT_size(HTable* ht)
{
	return ht->size;
}

int HT_load(HTable* ht)
{
	return ht->load;
}

void** HT_values(HashTable ht)
{
	void** vals = malloc(sizeof(Value)*ht->load);
	int i, j = 0;

	for(i = 0; i < ht->size; i++)
	{	
		if(ht->table[i]->flag == O)
			vals[j++] = ht->cloneV(ht->table[i]->value);
	}
	return vals;
}

void** HT_keys(HashTable ht)
{
	void** keys = malloc(sizeof(Key)*ht->load);
	int i, j = 0;

	for(i = 0; i < ht->size; i++)
	{	
		if(ht->table[i]->flag == O)
			keys[j++] = ht->cloneK(ht->table[i]->key);
	}
	return keys;
}
