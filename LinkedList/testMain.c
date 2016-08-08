#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "LinkedList.h"

/*
 * A test of my implementation of a Generic Linked List, in this particular test the data im storing in each node is a string, making the linked list used a Linked List of strings
 * 
 * TODO:
 * I definitely should test this with different data types
 * Tidy up the code a little bit, somethings could definitely be done better
 */

#define MAX_BUFFER_SIZE 256

int compara(const void*, const void*);
void* clone(const void *);

void menu();
int choose();
void insertString(LinkedList);
void removeString(LinkedList);
void lookupString(LinkedList);
void printData(LinkedList);

int main(int argc, char* argv[])
{
	LinkedList ll =  LL_create(compara, clone, free);
	printf("Linked List created successfully!\n");

	int op;
	menu();

	while((op = choose()))
	{
		switch(op)
		{
			case 0: break;
			case 1: insertString(ll); break;
			case 2: removeString(ll); break;
			case 3: lookupString(ll); break;
			case 4: printData(ll); break;
			default: printf("Invalid option!");
		}
		menu();
	}
	
	LL_free(ll);
	printf("Linked List freed successfully!\n");
	return 0;
}

int compara(const void* s1, const void* s2)
{
	return strcmp((char*) s1, (char*) s2);
}

void* clone(const void* string)
{
	return (void*) strdup((char*) string);
}

void menu()
{
	char op1[10] = "1: Insert";
	char op2[10] = "2: Remove";
	char op3[10] = "3: Lookup";
	char op4[10] = "4: Print";

	printf("\n-Menu-\n");
	printf("%s\n", op1);
	printf("%s\n", op2);
	printf("%s\n", op3);
	printf("%s\n", op4);
}

int choose()
{
	int i;
	scanf("%d", &i);
	return i;
}

void insertString(LinkedList l)
{
	char* s = malloc(sizeof(char)*MAX_BUFFER_SIZE);
	scanf("%s", s);
	LL_insert(l, (void*) s);
	free(s); /* because the string that was inserted was a clone, so i need to free this one */
}

void removeString(LinkedList l)
{
	char* s = malloc(sizeof(char)*MAX_BUFFER_SIZE);
	scanf("%s", s);
	LL_remove(l, (void*) s);
	free(s);
}

void lookupString(LinkedList l)
{
	int found;
	char* s = malloc(sizeof(char)*MAX_BUFFER_SIZE);
	scanf("%s", s);
	found = LL_lookUp(l, (void*) s);

	if(found) printf("Found '%s'\n", s);
	else printf("'%s' isnt in the list!\n", s);

	free(s);
}

void printData(LinkedList l)
{
	int i;
	char** arData = (char**) LL_getData(l);
	for(i = 0; i < LL_size(l); i++)
	{
		printf("%s\n", arData[i]);
		free(arData[i]);
	}
	free(arData);
}
