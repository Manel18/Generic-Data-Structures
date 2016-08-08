#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue* Queue;

typedef void* (*Cloner) (const void*);

typedef void (*Freer) (void*);

void Q_print(Queue);

int Q_getUsed(Queue);

/*Creates a Queue with a given size passed as an argument*/
Queue Q_create(int, Cloner, Freer);

/*Deletes a queue*/
void Q_free(Queue);

/*Checks if a Queue is empty. Returns 0 if False, 1 if True*/
int Q_isEmpty(Queue);

/*Puts data in the queue (Maybe change the return size to be possible to check if it really was put)*/
void Q_enqueue(Queue, void*);

/*Removes the data at the head of the list*/
void* Q_dequeue(Queue);
#endif
