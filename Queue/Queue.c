#include <stdlib.h>
#include <stdio.h>
#include "Queue.h"

static void Q_resize(Queue);

typedef struct queue
{
	int size;
	int used;
	int head;
	Cloner clone;
	Freer free;
	void** queue;
};

Queue Q_create(int size, Cloner clone, Freer free)
{
	struct queue* queue = malloc(sizeof(struct queue));
	queue->size = size;
	queue->used = 0;
	queue->head = 0;
	queue->clone = clone;
	queue->free = free;	
	queue->queue = malloc(sizeof(void*) * size);
	return queue; 
}

void Q_free(Queue q)
{
	if(q->used)
	{
		int i, j;
		for(i = q->head, j = 1; j <= q->used; j++, i = (i + 1) % q->size)
				q->free(q->queue[i]);
	}
	free(q->queue);
	free(q);
}

int Q_isEmpty(Queue q)
{
	return q->used;
}

void Q_enqueue(Queue q, void* data)
{
	if( q->used + 1 == q->size)
		Q_resize(q);
	
	q->queue[q->used++] = q->clone(data);
}

void* Q_dequeue(Queue q)
{
	if(q->used)
	{	
		q->used--;
		// should i return a clone? i mean, within the queue we'll never look at it, the pointer will be overwritten eventually
		void* d = q->clone(q->queue[q->head]);
		free(q->queue[q->head]);
		q->head = (q->head + 1) % q->size;
		return d;
	}
	else
		return NULL;
}

int Q_getUsed(Queue q)
{
	return q->used;
}

void Q_print(Queue q)
{
	int i, j = 1;
	for(i = q->head; j <= q->used; i = (i + 1) % q->size)
	{
		printf("%d - ", i);
		printf("%s\n",(char*) q->queue[i]);
	}
}

void Q_resize(Queue q)
{
	int i, j = 0;
	void** queue = malloc(sizeof(void*) * q->size * 2);
	for(i = q->head; j + 1 <= q->used; i = (i + 1) % q->size)
	{
		queue[j++] = q->queue[i];
	}
	q->queue = queue;
	q->size *= 2;
	q->head = 0;
}
