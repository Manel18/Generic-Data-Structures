#include <stdlib.h>
#include "Stack.h"

/*
 * Dynamic array or linked list? Maybe provide both implementations and leave it for the user to decide
 * TODO: Have a way to stop the stack from resizing when a certain limit is reached. This limit would
 *       be different for different types of data.
 */

 typedef struct stack{
	int size;
	int used;
	Cloner clone;
	Freer free;
	void** stack;
 }stack;

static void S_resize(Stack);

Stack S_create(int size, Cloner clone, Freer free)
{
	stack* s = malloc(sizeof(struct stack));
	s->size = size;
	s->used = 0;
	s->clone = clone;
	s->free = free;
	s->stack = malloc(sizeof(void*) * size);
	return s;
}

void S_push(Stack s, void* data)
{
	if(s->used + 1 == s->size)
		S_resize(s);
	
	s->stack[s->used++] = s->clone(data);
}

void* S_pop(Stack s)
{
	void *d = NULL;

	if(s->used--)
	{
		d = s->clone(s->stack[s->used]);
		s->free(s->stack[s->used]);
	}
	
	return d;
}

int S_isEmpty(Stack s)
{
	return s->used == 0;
}

int S_free(Stack s)
{
	int i;
	for(i = 0; i < s->used; i++)
		s->free(s->stack[i]);
	
	free(s->stack);
	free(s);
}

int S_getSize(Stack s)
{
	return s->size;
}

int S_numElems(Stack s)
{
	return s->used;
}

static void S_resize(Stack s)
{
	s->stack = realloc(s->stack, sizeof(void*) * s->size * 2);
	s->size *= 2;
}
