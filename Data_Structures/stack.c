#include <stdlib.h>
#include <stdbool.h>

#include "stack.h"
#include "list.h"

/*
 * This is the structure that represents a stack.
 */
struct stack {
  struct list* list;
};

/*
 * Helper function
 * Checks if stack is null
 * returns true if stack is null, false otherwise
 */
bool stack_is_null(struct stack* s) {
    return s == NULL;
}

/*
 * Helper function
 * Checks if list is null
 * returns true if list is null, false otherwise
 */
bool list_is_null(struct list* l) {
    return l == NULL;
}

/*
 * This function allocates and initializes a new, empty stack and return
 * a pointer to it.
 */
struct stack* stack_create() {
	struct stack* s = malloc(sizeof(struct stack));
    if (stack_is_null(s)) {
        return NULL; // unable to allocate
    }

	s->list = list_create();
    if (list_is_null(s->list)) {
        free(s);
        return NULL; // unable to allocate
    }

	return s;
}

/*
 * This function frees the memory associated with a stack.  It does not free 
 * any memory associated with any objects held within.
 *
 * Params:
 *   stack - the stack to be destroyed.  May not be NULL.
 */
void stack_free(struct stack* stack) {
	list_free(stack->list);
	free(stack);
	return;
}

/*
 * This function indicates whether a given stack is currently empty.
 * Specifically, it returns 1 if the specified stack is empty (i.e.
 * contains no elements) and 0 otherwise.
 *
 * Params:
 *   stack - the stack whose emptiness is being questioned.  May not be NULL.
 */
int stack_isempty(struct stack* stack) {
	if (stack_is_null(stack) || list_is_null(stack->list)) {
		return 1;
	}
	return list_is_empty(stack->list);
}

/*
 * This function pushes a new value onto a given stack.  The value to be
 * pushed is specified as a void pointer. 
 *
 * Params:
 *   stack - the stack onto which a value is to be pushed.  May not be NULL.
 *   val - the value to be pushed.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void stack_push(struct stack* stack, void* val) {
	if (stack_is_null(stack) || list_is_null(stack->list)) {
		return;
	}
	list_insert(stack->list, val);
	return;
}

/*
 * This function returns the value stored at the top of a given stack
 * *without* removing that value. 
 * 
 * Params:
 *   stack - the stack from which to query the top value.  May not be NULL.
 */
void* stack_top(struct stack* stack) {
	if (stack_is_null(stack) || list_is_null(stack->list)) {
		return NULL;
	}
	return list_top(stack->list);
}

/*
 * This function pops a value from a given stack and return the popped
 * value. 
 *
 * Params:
 *   stack - the stack from which a value is to be popped.  May not be NULL.
 *
 * Return:
 *   This function returns the value that was popped.
 */
void* stack_pop(struct stack* stack) {
	if (stack_is_null(stack) || list_is_null(stack->list)) {
		return NULL;
	}
	return list_pop(stack->list);
}

/*
 * This function returns the length of the stack.
 *
 * Params:
 *   stack - the stack from which to get length.  May not be NULL.
 *
 * Return:
 *   The length of the stack.
 */
int stack_length(struct stack* stack) {
	if (stack_is_null(stack) || list_is_null(stack->list)) {
		return 0;
	}
	return list_length(stack->list);
}
