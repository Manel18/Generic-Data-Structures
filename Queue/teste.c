#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Queue.h"

#define MAX_BUF_SIZ 286

void* clone(const void* data);
void freeStrP(void* data);

void menu();
int choose();
void createQueue(Queue* q);
void enqueueStr(Queue q);
void dequeueStr(Queue q);
void queueUsed(Queue q);
void printData(Queue q);

int main(int argc, char** argv)
{
	Queue q = NULL;
	int op;
	
	menu();
	
	while((op = choose()))
	{
		switch(op){
			case 1: createQueue(&q); break;
			case 2: enqueueStr(q); break;
			case 3: dequeueStr(q); break;
			case 4: queueUsed(q); break;
			case 5: printData(q); break;
			default: printf("Invalid option!");
		}
		menu();
	}

	Q_free(q);

	return 0;
}

void menu()
{
	char op1[10] = "1: Create";
	char op2[10] = "2: Insert";
	char op3[10] = "3: Remove";
	char op4[10] = "4: Used";
	char op5[10] = "5: Print";

	printf("\n- MENU -\n");
	printf("%s\n", op1);
	printf("%s\n", op2);
	printf("%s\n", op3);
	printf("%s\n", op4);
	printf("%s\n", op5);
}

int choose()
{
	int i;
	printf("> ");
	scanf("%d", &i);
	return i;
}

void createQueue(Queue* q)
{
	int i;
	printf("\nInitial size: ");
	scanf("%d", &i);
	printf("Creating queue...");
	*q = Q_create(i, clone, free);
	printf("done\n");
}

void enqueueStr(Queue q)
{
	char* s = malloc(sizeof(char)*MAX_BUF_SIZ);
	printf("\nString: ");
	scanf("%s", s);
	printf("Enqueued: \"%s\"\n", s);
	Q_enqueue(q, (void*) s);
	free(s);
}

void dequeueStr(Queue q)
{
	char* s = (char*) Q_dequeue(q);
	printf("%s\n",s);
	free(s);
}

void queueUsed(Queue q)
{
	int s = Q_getUsed(q);
	printf("\nQueue size: %d\n", s);
}

void printData(Queue q)
{
	/* I'll have to make a func that returns a copy of the queue, but for now this...*/
	Q_print(q);
}

void* clone(const void* data)
{
	return (void*) strdup((char*) data);
}

void freeStrP(void* data)
{
	free((char*) data);
}
