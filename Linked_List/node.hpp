#ifndef NODE_HPP
#define NODE_HPP

struct node {
public:
	int val;	// the value that this node stores
	node* next;	// a pointer to the next node in the list
public:
	// Default constructor
	node() = default;

	// Constructor
	// Parameters: val (int) - value to store
	node(int val) : val(val), next(nullptr) {}
};

#endif
