#include <stdlib.h>

#include "pq.h"
#include "dynarray.h"


/*
 * This struct represents a pq node.
 */
struct pq_node {
	void* value;
	int priority;
};

/*
 * This is the structure that represents a priority queue.
 */
struct pq {
	struct dynarray* heap;
};


/*
 * This function allocates and initializes an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
	struct pq* pq = malloc(sizeof(struct pq));
	if (pq == NULL) {
		return NULL; // unable to allocate
	}

	pq->heap = dynarray_create();
	if (pq->heap == NULL) {
		free(pq);
		return NULL;
	}

	return pq;
}


/*
 * This function frees the memory allocated to a given priority queue. It does not free
 * any memory associated with the objects stored.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
	dynarray_free(pq->heap);
	free(pq);
	return;
}


/*
 * This function returns 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
	if (pq == NULL || pq->heap == NULL || dynarray_size(pq->heap) == 0) {
		return 1;
	}
	return 0;
}


/*
 * This function inserts a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value will be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.
 */
void pq_insert(struct pq* pq, void* value, int priority) {
	if (pq == NULL || pq->heap == NULL) {
		return;
	}

	// Create node and insert into heap
	struct pq_node* node = malloc(sizeof(struct pq_node));
	node->value = value;
	node->priority = priority;
	dynarray_insert(pq->heap, node);

	// Get pos of insertion and parent pos
	int pos = dynarray_size(pq->heap) - 1;
	int pidx = (pos - 1) / 2;

	// While insert position isnt root
	while (pos > 0) {
		struct pq_node* parent = dynarray_get(pq->heap, pidx);

		// If node has higher priority than its parent,
		if (node->priority < parent->priority) {
			// Move parent, update new insertion pos and get new pidx
			dynarray_set(pq->heap, pos, parent);
			pos = pidx;
			pidx = (pos - 1) / 2;
		}
		// Otherwise, break
		else {
			break;
		}
	}

	// Insert new value at the correct index
	dynarray_set(pq->heap, pos, node);
	return;
}


/*
 * This function returns the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   The value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
	if (pq_isempty(pq)) {
		return NULL;
	}

	struct pq_node* node = dynarray_get(pq->heap, 0);
	return node->value;
}


/*
 * This function returns the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   The priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
	if (pq_isempty(pq)) {
		return 0;
	}

	struct pq_node* node = dynarray_get(pq->heap, 0);
	return node->priority;
}

/* 
 * Helper function
 * Swaps two elements based on two indexes
 */
void _swap(struct pq* pq, int i, int j) {
	if (pq == NULL || pq->heap == NULL) {
		return;
	}

	// Get two nodes to swap
	struct pq_node* i_node = dynarray_get(pq->heap, i);
	struct pq_node* j_node = dynarray_get(pq->heap, j);

	// Insert them at other index
	dynarray_set(pq->heap, i, j_node);
	dynarray_set(pq->heap, j, i_node);
}

/* 
 * Helper function
 * Recursively adjusts heap to maintain min heap quality
 */
void _adjust_heap(struct pq* pq, int max_idx, int pos) {
	if (pq == NULL || pq->heap == NULL) {
		return;
	}

	int left_idx = pos * 2 + 1; // Left child index
	int right_idx = pos * 2 + 2; // Right child index
	int smallest = pos;

	// Check both the right and the left children if they exist for the lowest
	// priority index

	// Check left child against current priority
	if (left_idx <= max_idx) {

		struct pq_node* left_node = dynarray_get(pq->heap, left_idx);
		struct pq_node* curr = dynarray_get(pq->heap, smallest);

		// If left priority is less than current, recors its priority
		if (left_node->priority < curr->priority) {
			smallest = left_idx;
		}
	}

	 // Check right against smallest of left and current
	if (right_idx <= max_idx) {

		struct pq_node* right_node = dynarray_get(pq->heap, right_idx);
		struct pq_node* smallest_node = dynarray_get(pq->heap, smallest);

		// If the right child has higher priority,
		if (right_node->priority < smallest_node->priority) {
			smallest = right_idx;
		}
	}

	// If the position of the smallest priority isnt that of the inserted element, 
	// swap element with its parent and recurse
	if (smallest != pos) {
		_swap(pq, pos, smallest);
		_adjust_heap(pq, max_idx, smallest);
	}
}

/*
 * This function returns the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   The value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
	if (pq == NULL || pq->heap == NULL) {
		return NULL;
	}

	// Get node to remove and its value
	struct pq_node* root = dynarray_get(pq->heap, 0);
	void* to_return = root->value;

	// Get the position of the last element
	int last = dynarray_size(pq->heap) - 1;

	// Copy last element to first place
	if (last > 0) {
		struct pq_node* last_node = dynarray_get(pq->heap, last);
		dynarray_set(pq->heap, 0, last_node);
	}

    // Remove last from array
    dynarray_remove(pq->heap, last);

    // Fix heap if needed
    if (last > 0) {
        _adjust_heap(pq, last - 1, 0);
    }

	// Free the removed node and return its value
    free(root); 
    return to_return;
}
