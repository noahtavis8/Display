/*
 * This file is where you should implement your stack.  It already contains
 * skeletons of the functions you need to implement (along with documentation
 * for each function).  Feel free to implement any additional functions you
 * might need.  Also, don't forget to include your name and @oregonstate.edu
 * email address below.
 *
 * Name: Noah Tavis
 * Email: tavisn@oregonstate.edu
 */

#include <stdlib.h>

#include "stack.h"
#include "list.h"

// For boolean return type for helper functions
#include <stdbool.h>

/*
 * This is the structure that will be used to represent a stack.  This
 * structure specifically contains a single field representing a linked list
 * that should be used as the underlying data storage for the stack.
 *
 * You should not modify this structure.
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
 * This function should allocate and initialize a new, empty stack and return
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
 * This function should free the memory associated with a stack.  While this
 * function should up all memory used in the stack itself, it should not free
 * any memory allocated to the pointer values stored in the stack.  This is the
 * responsibility of the caller.
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
 * This function should indicate whether a given stack is currently empty.
 * Specifically, it should return 1 if the specified stack is empty (i.e.
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
 * This function should push a new value onto a given stack.  The value to be
 * pushed is specified as a void pointer.  This function must have O(1)
 * average runtime complexity.
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
 * This function should return the value stored at the top of a given stack
 * *without* removing that value.  This function must have O(1) average runtime
 * complexity.
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
 * This function should pop a value from a given stack and return the popped
 * value.  This function must have O(1) average runtime complexity.
 *
 * Params:
 *   stack - the stack from which a value is to be popped.  May not be NULL.
 *
 * Return:
 *   This function should return the value that was popped.
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
