#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "dynarray.h"



/*
 * Dynarray struct definition
 */
struct dynarray {
    void** data;
    int size;
    int capacity;
};

/*
 * Helper function
 * Checks if da is null
 * returns true if da is null, false otherwise
 */
bool da_is_null(struct dynarray* da) {
    return da == NULL;
}

/*
* Helper function
* Checks idk is out of bounds
* returns true if idx is greater than or equal to n or below 0,
* returns false otherwise
*/
bool idx_out_of_bounds(int idx, int n) {
    if ((idx >= n || idx < 0)) {
        return true;
    }
    return false;
}


/*
 * This function allocates and initializes a new, empty dynamic array and
 * return a pointer to it.  Has an initial capacity of 2.
 */
struct dynarray* dynarray_create(){

    struct dynarray* da = malloc(sizeof(struct dynarray));
    if (da_is_null(da)) {
        return NULL; // unable to allocate
    }

    da->capacity = 2;
    da->size = 0;

    da->data = malloc(da->capacity * sizeof(void*));
    if (da->data == NULL) {
        free(da);
        return NULL; // unable to allocate
    }

    return da;
}

/*
 * This function frees the memory associated with a dynamic array. Does not free any 
 * memory associated with the objects within.
 *
 * Params:
 * da - the dynamic array to be destroyed.  May not be NULL.
 */
void dynarray_free(struct dynarray* da){
    if (da_is_null(da)) {
        return;
    }

    free(da->data);
    free(da);
    return;
}

/*
 * This function returns the size of a given dynamic array (i.e. the
 * number of elements stored in it, not the capacity).
 */
int dynarray_size(struct dynarray* da){
    if (da_is_null(da)) {
        return 0;
    }
    return da->size;
}

/*
 * This function inserts a new value at the end of a given dynarray.
 *
 * Params:
 * da - the dynamic array into which to insert an element.  May not be NULL.
 * val - the value to be inserted.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void dynarray_insert(struct dynarray* da, void* val){

    if (da_is_null(da)) {
        return;
    }

    // If more size is needed
    if (da->size == da->capacity) {
        da->capacity = da->capacity * 2;

        // 1. Allocate new memory
        void** new_data = malloc(da->capacity * sizeof(void*));
        if (new_data == NULL) {
            return;
        }
        

        // 2. Copy elements over
        for (int i = 0; i < da->size; i++) {
            new_data[i] = da->data[i];
        }

        // 3. Delete old array
        free(da->data);

        // 4. Update array pointer
        da->data = new_data;
    }

    // 5. Insert new element
    da->data[da->size] = val;
    da->size++;

    return;
}

/*
 * This function removes an element at a specified index from a dynamic
 * array.  All existing elements following the specified index are moved
 * forward to fill in the gap left by the removed element.
 *
 * Params:
 * da - the dynamic array from which to remove an element.  May not be NULL.
 * idx - the index of the element to be removed.  The value of `idx` must be
 *     between 0 (inclusive) and n (exclusive), where n is the number of
 *     elements stored in the array.
 */
void dynarray_remove(struct dynarray* da, int idx){
    if (da_is_null(da) || idx_out_of_bounds(idx, da->size)) {
        return;
    }

    // Shift everything forward
    for (int i = idx; i < da->size - 1; i++) {
        da->data[i] = da->data[i + 1];
    }

    da->size--;

    return;
}

/*
 * This function returns the value of an existing element a dynamic
 * array. Note that this value will be returned as type void*.
 *
 * Params:
 * da - the dynamic array from which to get a value.  May not be NULL.
 * idx - the index of the element whose value should be returned.  The value
 *     of `idx` must be between 0 (inclusive) and n (exclusive), where n is the
 *     number of elements stored in the array.
 */
void* dynarray_get(struct dynarray* da, int idx){
    if (da_is_null(da) || idx_out_of_bounds(idx, da->size)) {
        return NULL;
    }
    return da->data[idx];
}

/*
 * This function updates (i.e. overwrite) the value of an existing
 * element in a dynamic array.
 *
 * Params:
 *   da - the dynamic array in which to set a value.  May not be NULL.
 *   idx - the index of the element whose value should be updated.  The value
 *     of `idx` must be between 0 (inclusive) and n (exclusive), where n is the
 *     number of elements stored in the array.
 *   val - the new value to be set.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void dynarray_set(struct dynarray* da, int idx, void* val){
    if (da_is_null(da) || idx_out_of_bounds(idx, da->size)) {
        return;
    }
    da->data[idx] = val;
    return; 
}

// This function returns the length of the array.
int dynarray_length(struct dynarray* da) {
  return da->size;
}

