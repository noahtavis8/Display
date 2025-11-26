#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "list.h"

/*
 * This structure is used to represent a single node in a singly-linked list.
 */
struct node {
    void* val;
    struct node* next;
};

/*
 * Helper function
 * Checks if list is null
 * returns true if list is null, false otherwise
 */
bool list_is_null(struct list* list) {
    return list == NULL;
}

/*
 * Helper function
 * Checks if node is null
 * returns true if node is null, false otherwise
 */
bool node_is_null(struct node* node) {
    return node == NULL;
}

/*
 * This structure is used to represent a singly-linked list.
 */
struct list {
    struct node* head;
};

/*
 * This function allocates and initializes a new, empty linked list and
 * return a pointer to it.
 */
struct list* list_create()
{
    struct list* list = malloc(sizeof(struct list));
    if (list_is_null(list)) {
        return NULL;
    }

    list->head = NULL;
    
    return list;
}

/*
 * This function frees the memory associated with a linked list.  It does not free
 * the memory associated with each object stored in the list.
 *
 * Params:
 * list - the linked list to be destroyed.  May not be NULL.
 */

void list_free(struct list* list)
{
    if (list_is_null(list)) {
        return;
    }

    struct node* current = list->head;
    struct node* next =  NULL;

    // Traverse list and free each node
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    // Free list itself
    free(list);

    return;
}

/*
 * This function inserts a new value at the beginning a given linked list.
 *
 * Params:
 * list - the linked list into which to insert an element. May not be NULL.
 * val - the value to be inserted. Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */

void list_insert(struct list* list, void* val)
{
    if (list_is_null(list)) {
        return;
    }

    // Allocate new node
    struct node* new = malloc(sizeof(struct node));
    if (node_is_null(new)) {
        return; // mallocation failed
    }

    // Insert value and adjust pointers
    new->val = val;
    new->next = list->head;
    list->head = new;

    return;
}

/*
 * This function inserts a new value at the end of a given linked list.
 *
 * Params:
 * list - the linked list into which to insert an element.  May not be NULL.
 * val - the value to be inserted. Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */

void list_insert_end(struct list* list, void* val)
{
    if (list_is_null(list)) {
        return;
    }

    // Allocate new node and assign value
    struct node* new = malloc(sizeof(struct node));
    if (node_is_null(new)) {
        return; // mallocation failed
    }
    new->val = val;
    new->next = NULL;

    // If the list is empty, insert at beginning
    if (node_is_null(list->head)) {
        list->head = new;
        return;
    }

    // Traverse to end of list
    struct node* current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }

    // Insert new node
    current->next = new;

    return;
}

/*
 * This function removes an element with a specified value from a given
 * linked list. If the specified value appears multiple times in
 * the list, the function only removes the *first* instance of that
 * value (i.e. the one nearest to the head of the list).
 *
 * Params:
 * list - the linked list from which to remove an element.  May not be NULL.
 * val - the value to be removed. 
 * cmp - pointer to a function that can be passed two void* values from
 *     to compare them for equality, as described above.  If the two values
 *     passed are to be considered equal, this function should return 0.
 *     Otherwise, it should return a non-zero value.
 */
void list_remove(struct list* list, void* val, int (*cmp)(void* a, void* b))
{
    if (list_is_null(list) || node_is_null(list->head)) {
        return;
    }

    struct node* previous = NULL;
    struct node* current = list->head;

    // If the head is the node to remove
    if (cmp(val, current->val) == 0) {
        list->head = current->next;
        free(current);
        return;
    }

    // Advance pointers
    previous = current;
    current = current->next;

    // Traverse the list
    while (current != NULL) {

        if (cmp(val, current->val) == 0) {
            previous->next = current->next;
            free(current);
            return;
        }

        previous = current;
        current = current->next;
    }

    return;
}

/*
 * This function removes the last element from a given
 * linked list.

 * Params:
 * list - the linked list from which to remove an element.  May not be NULL.

 */
void list_remove_end(struct list* list)
{
    if (list_is_null(list) || node_is_null(list->head)) {
        return;
    }

    struct node* current = list->head;
    struct node* previous = NULL;

    // Traverse to end of list
    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }

    // If list had only one node
    if (previous == NULL) {
        list->head = NULL; // head is now NULL
    } else {
        previous->next = NULL; // detach last node
    }

    free(current);
    return;
}


/*
 * This function returns the position (i.e. the 0-based "index") of the
 * first instance of a specified value within a given linked list.
 *
 * Params:
 * list - the linked list to be searched from. May not be NULL.
 * val - the value to be located. Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 * cmp - pointer to a function that can be passed two void* values from
 *     to compare them for equality, as described above.  If the two values
 *     passed are to be considered equal, this function should return 0.
 *     Otherwise, it should return a non-zero value.
 *
 * Return:
 *   This function returns the 0-based position of the first instance of
 *   `val` within `list`, as determined by the function `cmp` (i.e. the closest
 *    such instance to the head of the list) or -1 if `list` does not contain
 *    the value `val`.
 */
int list_position(struct list* list, void* val, int (*cmp)(void* a, void* b))
{
    if (list_is_null(list) || node_is_null(list->head)) {
        return -1;
    }

    int pos = 0;
    struct node* current = list->head;

    // Compare and traverse
    while (current != NULL) {
        if (cmp(val, current->val) == 0) {
            return pos;
        }

        pos++;
        current = current->next;
    }

    return -1;
}

/*
 * This function reverses the order of the links in a given linked list in place.
 *
 * Params:
 * list - the linked list to be reversed.  May not be NULL.  When this
 *     function returns it will contain the reversed list.
 */
void list_reverse(struct list* list)
{
    if (list_is_null(list) || node_is_null(list->head)) {
        return;
    }

    struct node* previous = NULL;
    struct node* current = list->head;
    struct node* next = NULL;

    // Traverse list
    while (current != NULL) {
        next = current->next;       // store next node
        current->next = previous;   // swap pointer direction
        previous = current;         // move previous pointer
        current = next;             // mode current pointer
    }

    // Head now points to end of list
    list->head = previous;
    
    return;
}

// Checks whether the given list is empty
// Returns 1 if empty, 0 otherwise
int list_is_empty(struct list* list) {
  if (list == NULL || list->head == NULL) {
    return 1;
  }

  return 0;
}

// Returns the first value in the list
void* list_top(struct list* list) {
  assert(list);

  if (list->head == NULL) {
    return NULL;
  }

  return list->head->val;
}

// Returns the first value in the list 
// AND removes the node from the list
void* list_pop(struct list* list) {
  assert(list);

  if (list->head == NULL) {
    return NULL;
  }

  void* val = list->head->val;
  struct node* temp = list->head->next;
  free(list->head);
  list->head = temp;
  return val;
}

// Returns the length of the list
int list_length(struct list* list) {
  int len = 0;
  struct node* current = list->head;
  while (current != NULL) {
    current = current->next;
    len++;
  }
  return len;
}
