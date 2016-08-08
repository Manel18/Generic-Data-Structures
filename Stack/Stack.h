#ifndef STACK_H
#define STACK_H

typedef struct stack* Stack;

typedef void* (*Cloner)(const void*);

typedef void (*Freer)(void*);


/*
 * Necessary functions: 
 */

/* Create a stack with a given size */
Stack S_create(int, Cloner, Freer);

/* Push some data to the stack */
void S_push(Stack, void*);

/* Pop some data from the stack */
void* S_pop(Stack);

/* Check if the stack is empty, return 1 if true and 0 otherwise */
int S_isEmpty(Stack);

/* Free the stack and all the data inside */
int S_free(Stack);

/*
 * Not so necessary:
 */

 /* Get the size of the stack */
int S_getSize(Stack);

 /* Get number of elements inside the stack */
int S_numElems(Stack);

#endif
