#include <stdlib.h>
#include <stdbool.h>

#include "queue.h"
#include "dynarray.h"

/*
 * This is the structure of the queue
 */
struct queue {
  struct dynarray* array;
};

/*
 * Helper function
 * Checks if queue is null
 * returns true if queue is null, false otherwise
 */
bool queue_is_null(struct queue* q) {
    return q == NULL;
}

/*
 * Helper function
 * Checks if dynarray is null
 * returns true if dynarray is null, false otherwise
 */
bool da_is_null(struct dynarray* da) {
    return da == NULL;
}

/*
 * This function allocates and initializes a new, empty queue and return
 * a pointer to it.
 */
struct queue* queue_create() {
	struct queue* q = malloc(sizeof(struct queue));
	if (queue_is_null(q)) {
		return NULL; // unable to allocate
	}

	q->array = dynarray_create();
	if (da_is_null(q->array)) {
		free(q);
		return NULL; // unable to allocate
	}

	return q;
}

/*
 * This function frees the memory associated with a queue.  Does not free any 
 * memory associated with any objects stored within.
 * Params:
 *   queue - the queue to be destroyed.  May not be NULL.
 */
void queue_free(struct queue* queue) {
	dynarray_free(queue->array);
	free(queue);
  	return;
}

/*
 * This function indicates whether a given queue is currently empty.
 * Specifically, it returns 1 if the specified queue is empty (i.e.
 * contains no elements) and 0 otherwise.
 *
 * Params:
 *   queue - the queue whose emptiness is being questioned.  May not be NULL.
 */
int queue_isempty(struct queue* queue) {
	if (queue_is_null(queue) || da_is_null(queue->array) 
		|| dynarray_size(queue->array) == 0) {
		return 1;
	}
	return 0;
}

/*
 * This function enqueues a new value into a given queue.  The value to
 * be enqueued is specified as a void pointer. 
 *
 * Params:
 *   queue - the queue into which a value is to be enqueued.  May not be NULL.
 *   val - the value to be enqueued.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void queue_enqueue(struct queue* queue, void* val) {
	if (queue_is_null(queue) || da_is_null(queue->array)) {
		return;
	}
	dynarray_insert(queue->array, val);
	return;
}

/*
 * This function returns the value stored at the front of a given queue
 * *without* removing that value. 
 *
 * Params:
 *   queue - the queue from which to query the front value.  May not be NULL.
 */
void* queue_front(struct queue* queue) {
	if (queue_is_null(queue) || da_is_null(queue->array)) {
		return NULL;
	}

	if (dynarray_size(queue->array) == 0) {
		return NULL; // queue is empty
	}

	return dynarray_get(queue->array, 0);
}

/*
 * This function dequeues a value from a given queue and return the
 * dequeued value. 
 *
 * Params:
 *   queue - the queue from which a value is to be dequeued.  May not be NULL.
 *
 * Return:
 *   The value that was dequeued.
 */
void* queue_dequeue(struct queue* queue) {
	if (queue_is_null(queue) || da_is_null(queue->array)) {
		return NULL;
	}

	if (dynarray_size(queue->array) == 0) {
		return NULL; // queue is empty
	}

	void* val = queue_front(queue);
	dynarray_remove(queue->array, 0);
	return val;
}

/*
 * This function returns the length of the queue.
 *
 * Params:
 *   queue - the queue from to get length.  May not be NULL.
 *
 * Return:
 *   The length of the queue.
 */
int queue_length(struct queue* queue) {
	if (queue_is_null(queue) || da_is_null(queue->array)) {
		return 0;
	}
	return dynarray_length(queue->array);
}
