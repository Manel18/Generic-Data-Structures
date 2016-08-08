#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"

#define MAX_BUF_SIZ 256

void* cloner(const void*);

void menu();
int choose();
void stackCreate(Stack*);
void stackPush(Stack);
void stackPop(Stack);
void stackSize(Stack);
void stackPrint(Stack);

int main(int argc, char* argv[])
{
	Stack s = NULL;
	int op;
	
	menu();
	while((op = choose()))
	{
		switch(op){
			case 1: stackCreate(&s); break;
			case 2: stackPush(s); break;
			case 3: stackPop(s); break;
			case 4: stackSize(s); break;
			case 5: stackPrint(s); break;
			default: printf("Invalid option! (press 0 to leave)\n");
		}
		menu();
	}
	
	S_free(s);
	
	return 0;
}

void menu()
{
	char op1[10] = "1: Create";
	char op2[10] = "2: Push";
	char op3[10] = "3: Pop";
	char op4[10] = "4: Size";
	char op5[10] = "5: Print";

	printf("\n- Menu -\n");
	printf("%s\n %s\n %s\n %s\n %s\n", op1, op2, op3, op4, op5);
}

int choose()
{
	int i;
	printf("> ");
	scanf("%d", &i);
	return i;
}

void stackCreate(Stack* s)
{
	int size;
	printf("Stack's size: ");
	scanf("%d", &size);
	printf("Creating Stack...");
	*s = S_create(size, cloner, free);
	printf("done\n");
}

void stackPush(Stack s)
{
	char* str = malloc(sizeof(char)*MAX_BUF_SIZ);
	printf("String: ");
	scanf("%s", str);
	printf("Pushing \"%s\"...", str);
	S_push(s, str);
	printf("done\n");
	free(str);
}

void stackPop(Stack s)
{
	if(!S_isEmpty(s))
	{
		char* str = NULL;
		printf("Popping from stack...");
		str = S_pop(s);
		printf("done -> \"%s\"\n", str);
		free(str);
	}
}

void stackSize(Stack s)
{
	printf("Stack size: %d\n", S_getSize(s));
}

void stackPrint(Stack s)
{
	printf("TODO\n");
}

void* cloner(const void* data)
{
	return (void*) strdup((char*) data);
}



