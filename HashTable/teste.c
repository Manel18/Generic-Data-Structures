#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> /* To use pow in the hash fucntion */
#include "HashTable.h"

#define MAX_BUF_SIZ 256

void updater(Value*, Value);
int comparator(Key, Key);
void* cloner(Value);
void freer(Value);
int hash(HashTable, Key);

void menu();
int choose();
void createHashTable(HashTable*);
void putHashTable(HashTable);
void getHashTable(HashTable);
void remHashTable(HashTable);
void keysHashTable(HashTable);
void valsHashTable(HashTable); 

void propsHashTable(HashTable);

int main(int argc, char* argv[])
{
	HashTable ht = NULL;
	int op;

	menu();
	while((op = choose()))
	{
		switch(op)
		{
			case 1: createHashTable(&ht); break;
			case 2: putHashTable(ht); break;
			case 3: getHashTable(ht); break;
			case 4: remHashTable(ht); break;
			case 5: keysHashTable(ht); break;
			case 6: valsHashTable(ht); break;
			case 7: propsHashTable(ht); break;
			default:
				printf("Invalid option!\n");
		}
		menu();
	}

	if(ht != NULL)
		HT_free(ht);

	return 0;
}

void menu()
{
	char op1[10] = "1: Create";
	char op2[10] = "2: Put";
	char op3[10] = "3: Get";
	char op4[10] = "4: Remove";
	char op5[10] = "5: Keys";
	char op6[10] = "6: Values";
	char op7[10] = "7: Propts";

	printf("\n-- Menu --\n");
	printf(" %s\n %s\n %s\n %s\n %s\n %s\n %s\n", 
			 op1, op2, op3, op4, op5, op6, op7);
}

int choose()
{
	int i;
	printf("> ");
	scanf("%d", &i);
	return i;
}

void createHashTable(HashTable* ht)
{
	int s;
	float loadfactor;
	printf("Table's size: ");
	scanf("%d", &s);
	printf("Table's load factor: ");
	scanf("%f", &loadfactor);

	*ht = HT_create(s, loadfactor, updater, comparator, cloner, cloner, hash, freer, freer);
}

void putHashTable(HashTable ht)
{
	char* s = malloc(sizeof(char)*MAX_BUF_SIZ);
	printf("Because we're working with strings, key will be the same as value!\n");
	printf("Key/Value: ");
	scanf("%s", s);

	HT_put(ht, (void*) s, (void*) s);
	free(s);
}

void getHashTable(HashTable ht)
{
	char* sK = malloc(sizeof(char)*MAX_BUF_SIZ);
	char* sV = malloc(sizeof(char)*MAX_BUF_SIZ);
	
	printf("Key: ");
	scanf("%s", sK);

	sV = HT_get(ht, (void*) sK);

	printf("Key: %s, Value: %s\n", sK, sV);
	free(sV);
	free(sK);
}

void remHashTable(HashTable ht)
{
	char* s = malloc(sizeof(char)*MAX_BUF_SIZ);
	
	printf("Key: ");
	scanf("%s", s);

	HT_remove(ht, (void*) s);
	free(s);
}

void keysHashTable(HashTable ht)
{
	char** keys = (char**) HT_keys(ht);
	int i, size = HT_load(ht);

	for(i = 0; i < size; i++)
	{	
		printf("%s\n", keys[i]);
		free(keys[i]);
	}
	free(keys);
}

void valsHashTable(HashTable ht)
{
	char** values = (char**) HT_values(ht);
	int i, size = HT_load(ht);

	for(i = 0; i < size; i++)
	{	
		printf("%s\n", values[i]);
		free(values[i]);
	}
	free(values);
}

void propsHashTable(HashTable ht)
{
	printf("Table's size: %d\n", HT_size(ht));
	printf("Table's load: %d\n", HT_load(ht));
}

/*
 * We're going to use string as our data type
 * so the functions we'll be passing to the HashTable
 * are basically going to be from string.h
 */

void updater(Value* s1, Value s2)
{
	char* temp = (char*) s1;
	*s1 = s2;
	free(temp);
}

int comparator(Key s1, Key s2)
{
	return !strcmp((char*) s1, (char*) s2);
}

void* cloner(Value s)
{
	return strdup((char*) s);
}

int hash(HashTable ht, Key k)
{
	int hash = 0;
	int i = 1;
	char* c = (char*) k;

	while(c[0])
	{
		hash += c[0] * i++;
		c++;
	}

	return hash % HT_size(ht);
}

int hash2(HashTable ht, Key k)
{
	int hash = 0;
	char* c = (char*) k;
	double len = (double) strlen(c);
	int i = 1;

	while(c[0])
	{
		hash += (int) pow(c[0]*31, (double) len - i++);
		c++;
	}

	return hash % HT_size(ht);
}

void freer(Value v)
{
	free(v);
}
