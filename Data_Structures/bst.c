#include <stdlib.h>
#include <stdbool.h>

#include "bst.h"

/*
 * This structure represents a single node in a BST.  In addition to containing
 * pointers to its two child nodes (i.e. `left` and `right`), it contains two
 * fields representing the data stored at this node.  The `key` field is an
 * integer value that should be used as an identifier for the data in this
 * node. 
 */
struct bst_node {
  int key;
  void* value;
  struct bst_node* left;
  struct bst_node* right;
};


/*
 * This structure represents an entire BST.  It specifically contains a
 * reference to the root node of the tree.
 */
struct bst {
  struct bst_node* root;
};

/*
 * Helper function
 * Checks if bst is null
 * returns true if bst is null, false otherwise
 */
bool bst_is_null(struct bst* bst) {
    return bst == NULL;
}

/*
 * Helper function
 * Checks if bst_node is null
 * returns true if bst_node is null, false otherwise
 */
bool bst_node_is_null(struct bst_node* bst_node) {
    return bst_node == NULL;
}

/*
 * This function allocates and initializes a new, empty, BST and return
 * a pointer to it.
 */
struct bst* bst_create() {
  struct bst* bst = malloc(sizeof(struct bst));
  if (bst_is_null(bst)) {
    return NULL;
  }

  bst->root = NULL;
  return bst;
}

/*
 * Helper function
 * Recursively frees every node in the tree
 */
void bst_free_nodes(struct bst_node* node) {
  if (bst_node_is_null(node)) {
    return;
  }

  bst_free_nodes(node->left);
  bst_free_nodes(node->right);
  free(node);
}

/*
 * This function frees the memory associated with a BST.  While this
 * function frees all memory used in the BST itself, it does not free
 * any memory allocated to the pointer values stored in the BST.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   bst - the BST to be destroyed.  May not be NULL.
 */
void bst_free(struct bst* bst) {
  if (bst_is_null(bst)) {
    return;
  }

  bst_free_nodes(bst->root);
  free(bst);
}

/*
 * Helper function
 * Recursively counts every node in the tree and returns the total number of nodes
 */
int bst_count_nodes(struct bst_node* node) {
  if (bst_node_is_null(node)) {
    return 0;
  }

  return 1 + bst_count_nodes(node->left) + bst_count_nodes(node->right);
}

/*
 * This function returns the total number of elements stored in a given
 * BST.
 *
 * Params:
 *   bst - the BST whose elements are to be counted.  May not be NULL.
 */
int bst_size(struct bst* bst) {
    if (bst_is_null(bst)) {
    return 0;
  }
  
  return bst_count_nodes(bst->root);
}

/*
 * This function inserts a new key/value pair into the BST.
 *
 * Params:
 *   bst - the BST into which a new key/value pair is to be inserted.  May not
 *     be NULL.
 *   key - an integer value that is used to order the key/value pair
 *     being inserted with respect to the other data in the BST.
 *   value - the value being inserted into the BST.  This will be stored in
 *     the BST alongside the key.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void bst_insert(struct bst* bst, int key, void* value) {
  if (bst_is_null(bst)) {
    return;
  }

  struct bst_node* p = NULL;
  struct bst_node* n = bst->root;

  // Navigate to correct leaf node
  while (!bst_node_is_null(n)) {
    p = n;
    if (key < n->key) {
      n = n->left;
    }
    else {
      n = n->right;
    }
  }

  // Create new node
  struct bst_node* to_add = malloc(sizeof(struct bst_node));
  if (bst_node_is_null(to_add)) {
    return;
  }
  to_add->value = value;
  to_add->key = key;
  to_add->left = NULL;
  to_add->right = NULL;

  // Insert appropriately
  if (bst_node_is_null(p)) {
    bst->root = to_add;
  } 
  else if (key < p->key) {
    p->left = to_add;
  } 
  else {
    p->right = to_add;
  }

  return;
}


/*
 * This function removes a key/value pair with a specified key from a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function removes the first one it encounters (i.e. the one closest to
 * the root of the tree).
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair to be removed from the BST.
 */
void bst_remove(struct bst* bst, int key) {
  if (bst_is_null(bst)) {
    return;
  }

  // Find node to remove n and its parent p
  struct bst_node* p = NULL;
  struct bst_node* n = bst->root;
  while (!bst_node_is_null(n)) {
    if (n->key == key) {
      break;
    }
    else if (key < n->key) {
      p = n;
      n = n->left;
    }
    else {
      p = n;
      n = n->right;
    }
  }

  // If no key was found
  if (n == NULL) {
    return;
  }

  // Update the appropriate parent pointer:

  // If n has no children, 
  if (bst_node_is_null(n->right) && bst_node_is_null(n->left)) {
      if (p == NULL) {
        bst->root = NULL;
      } else if (p->left == n) {
        p->left = NULL;
      } else {
        p->right = NULL;
      }
  }

  // If n has one child, 
  else if (bst_node_is_null(n->right)) {
      if (p == NULL) {
        bst->root = n->left;
      } else if (p->left == n) {
        p->left = n->left;
      } else {
        p->right = n->left;
      }
  }
  else if (bst_node_is_null(n->left)) {
      if (p == NULL) {
        bst->root = n->right;
      } else if (p->left == n) {
        p->left = n->right;
      } else {
        p->right = n->right;
      }
  }

  // If n has both children
  else {

    // Find the in order sucessor and its parent
    struct bst_node* s_p = n;
    struct bst_node* s = n->right;
    while (!bst_node_is_null(s->left)) {
      s_p = s;
      s = s->left;
    }

    // Copy successor's data into n
    n->key = s->key;
    n->value = s->value;

    // Remove successor node from its parent
    if (s_p->left == s) {
      s_p->left = s->right;
    } else {
      s_p->right = s->right;
    }

    free(s);
    return;
  }

  free(n);
  return;
}

/*
 * This function returns the value associated with a specified key in a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function returns the first one it encounters (i.e. the one closest to
 * the root of the tree).  If the BST does not contain the specified key, this
 * function returns NULL.
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Returns the value associated with the key `key` in `bst` or NULL,
 *   if the key `key` was not found in `bst`.
 */
void* bst_get(struct bst* bst, int key) {
  if (bst_is_null(bst)) {
    return NULL;
  }

  // Find node to get and return its value
  struct bst_node* n = bst->root;
  while (!bst_node_is_null(n)) {
    if (n->key == key) {
      return n->value;
    }
    else if (key < n->key) {
      n = n->left;
    }
    else {
      n = n->right;
    }
  }

  return NULL;
}

/*****************************************************************************
 **
 ** BST puzzle functions
 **
 *****************************************************************************/

/*
 * Helper function
 * Finds the longest path from a node recursively
 */
int bst_longest_path(struct bst_node* node) {
  // If the node is null,
  if (bst_node_is_null(node)) {
    return -1;
  }

  // If it has no children,
  if (bst_node_is_null(node->right) && bst_node_is_null(node->left)) {
    return 0;
  }

  // If it has one child, return 1 and recurse
  if (bst_node_is_null(node->left)) {
    return bst_longest_path(node->right) + 1;
  }
  if (bst_node_is_null(node->right)) {
    return bst_longest_path(node->left) + 1;
  }
  
  // If it has both children,
  int left = bst_longest_path(node->left) + 1;
  int right = bst_longest_path(node->right) + 1;

  // Return the one with the longest path
  if (left > right) {
    return left;
  }

  return right;
}

/*
 * This function returns the height of a given BST, which is the maximum
 * depth of any node in the tree (i.e. the number of edges in the path from
 * the root to that node).  Note that the height of an empty tree is -1 by
 * convention.
 *
 * Params:
 *   bst - the BST whose height is to be computed
 *
 * Return:
 *   Returns the height of bst.
 */
int bst_height(struct bst* bst) {
  struct bst_node* root = bst->root;

  // If the tree is empty,
  if (bst_is_null(bst)) {
    return -1;
  }

  // If it isnt, return the longest path from its root
  return bst_longest_path(root);
}

/*
 * Helper function
 * Checks if a path sum reaches a target value from a given node
 */
int bst_node_path_sum(struct bst_node* node, int target) {
  // If the node is null, return 0
  if (bst_node_is_null(node)) {
      return 0;
  }

  // Subtract current node's key from target
  int remaining = target - node->key;

  // If this is a leaf node, check if the remaining sum is 0
  if (bst_node_is_null(node->left) && bst_node_is_null(node->right)) {
      if (remaining == 0) {
          return 1;  // Found a valid path sum
      } else {
          return 0;  // Not a valid path sum
      }
  }

  // Check left subtree
  int left_result = bst_node_path_sum(node->left, remaining);
  if (left_result == 1) {
      return 1;  // Found in left subtree
  }

  // Check right subtree
  int right_result = bst_node_path_sum(node->right, remaining);
  if (right_result == 1) {
      return 1;  // Found in right subtree
  }

  // Not found in either subtree
  return 0;
}

/*
 * This function determines whether a specified value is a valid path
 * sum within a given BST.  In other words, this function will check whether
 * the given BST contains any path from the root to a leaf in which the keys
 * sum to the specified value.
 *
 * Params:
 *   bst - the BST whose paths sums to search
 *   sum - the value to search for among the path sums of `bst`
 *
 * Return:
 *   Returns 1 if `bst` contains any path from the root to a leaf in
 *   which the keys add up to `sum`.  Returns 0 otherwise.
 */
int bst_path_sum(struct bst* bst, int sum) {
  if (bst_is_null(bst)) {
    return 0;
  }

  return bst_node_path_sum(bst->root, sum);
}

/*
 * Helper function
 * Recursively computes a range sum over a given node with given bounds
 */
int bst_node_range_sum(struct bst_node* node, int lower, int upper) {
  if (bst_node_is_null(node)) {
    return 0;
  }

  // If the node's ley is lower than lower bound, look right
  if (node->key < lower) {
    return bst_node_range_sum(node->right, lower, upper);
  }

  // Vice versa
  if (node->key > upper) {
    return bst_node_range_sum(node->left, lower, upper);
  }

  // Otherwise the node is in range, so check both sides
  return node->key 
    + bst_node_range_sum(node->left, lower, upper) 
    + bst_node_range_sum(node->right, lower, upper);
}

/*
 * This function computes a range sum in a given BST.  Specifically, it
 * computes the sum of all keys in the BST between a given lower bound
 * and a given upper bound. 
 *
 * Params:
 *   bst - the BST within which to compute a range sum
 *   lower - the lower bound of the range over which to compute a sum; this
 *     is be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound is included in the sum
 *   upper - the upper bound of the range over which to compute a sum; this
 *     is considered an *inclusive* bound; in other words a key that's
 *     equal to this bound is included in the sum
 *
 * Return:
 *   Returns the sum of all keys in `bst` between `lower` and `upper`.
 */
int bst_range_sum(struct bst* bst, int lower, int upper) {
  if (bst_is_null(bst)) {
    return 0;
  }

  return bst_node_range_sum(bst->root, lower, upper);
}