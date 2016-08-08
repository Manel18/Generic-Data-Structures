#include "LinkedList.h"
#include <stdlib.h>

typedef struct node
{
	void* data; /* data held by the node */
	struct node* next; /* pointer to the next node */
} NODE;

typedef struct linkedlist
{
	unsigned int size; /* size of the list*/
	Comparator compare; /* pointer to compare function*/
	Cloner clone; /* pointer to clone function */
	Freer free; /* pointer to free function */
	NODE* fst; /*head of the list*/
} LList;

static NODE* LL_newNode(LList* list, void* data);

static void LL_freeNode(LList* list, NODE* node);

LList* LL_create(Comparator compare, Cloner clone, Freer free)
{
	LList* new_ll = malloc(sizeof(struct linkedlist));

	new_ll->size = 0;
	new_ll->compare = compare;
	new_ll->clone = clone;
	new_ll->free = free;
	new_ll->fst = NULL;

	return new_ll;
}

void LL_insert(LList* list, void* data)
{
	NODE* new_node = LL_newNode(list, data);
	
	new_node->next = list->fst;
	
	list->fst = new_node;
	list->size += 1;
}

void LL_remove(LList* list, void* data) 
{
	NODE* temp = list->fst;
	int found = 0;
	list->size -= 1;

	if(list->compare(data, temp->data) == 0)
	{
		NODE* temp1 = temp->next;
		LL_freeNode(list, temp);
		list->fst = temp1;
	}
	else
	{
		while(temp->next)
		{
			if(!(list->compare(data, temp->next->data)))
			{
				found = 1;
				break;
			}
			temp = temp->next;
		}

		if(found)
		{
			NODE* temp2 = temp->next;
			temp->next = temp2->next;
			LL_freeNode(list, temp2);
		}
	}
}

void LL_removePos(LList* list, int i)
{
	int j;
	NODE* temp = list->fst;
	list->size -= 1;

	if(i == 0)
	{
		NODE* temp1 = temp->next;
		list->free(list->fst);
		list->fst = temp1;
	}

	for(j = 1, temp = temp->next; j < i-1 && temp->next != NULL; j++, temp = temp->next);

	NODE* temp2 = temp->next;
	temp->next = temp2->next;
	list->free(temp2);
}

int LL_lookUp(LList* list, void* data)
{
	int found = 0;
	NODE* temp = list->fst;
	while(!found && temp != NULL)
	{
		if(!(list->compare(data, temp->data))) found = 1;
		temp = temp->next;
	}
	return found;
}

void* LL_peek(LList* list)
{
	return list->fst->data;
}

int LL_size(LList* list)
{
	return list->size;
}

void LL_free(LList* list)
{
	NODE* temp;
	while(list->fst != NULL)
	{
		temp = list->fst->next;
		LL_freeNode(list, list->fst);
		list->fst = temp;
	}

	free(list);
}

void** LL_getData(LList* l)
{
	int i;
	NODE* temp;
	void** arData = malloc(sizeof(void*) * l->size);
	for(i = 0, temp = l->fst; i < l->size && temp != NULL; i++, temp = temp->next)
		arData[i] = l->clone(temp->data);
	
	return arData;
}

static NODE* LL_newNode(LList* list, void* data)
{
	NODE* new_node = malloc(sizeof(struct node));
	
	new_node->data = list->clone(data);
	new_node->next = NULL;

	return new_node;
}

static void LL_freeNode(LList* list, NODE* node)
{
	list->free(node->data);
	free(node);
}
