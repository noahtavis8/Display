#ifndef __STACK_H
#define __STACK_H

/*
 * Structure used to represent a stack.
 */
struct stack;

/*
 * Stack interface function prototypes.  Refer to stack.c for documentation
 * about each of these functions.
 */
struct stack* stack_create();
void stack_free(struct stack* stack);
int stack_isempty(struct stack* stack);
void stack_push(struct stack* stack, void* val);
void* stack_top(struct stack* stack);
void* stack_pop(struct stack* stack);
int stack_length(struct stack* stack);

#endif
