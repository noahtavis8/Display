/*
 * Author: Noah Tavis
 * Program description: Linked list class implimentation 
 */

#include "linked_list.hpp"
#include <iostream>

linked_list::linked_list(const linked_list& other) : length(other.length) {
	// If there are no nodes to copy, return
	if (other.length == 0) {
		return;
	}

	// Create a head for this linked list and initialize it to a new node
	// with the other head's value
	this->head = new node(other.head->val);

	// Iterators
	node* this_itr = this->head;
	node* other_itr = other.head->next;

	// While there are more nodes to copy, 
	while (other_itr != nullptr) {
		// Create new node with the next value
		this_itr->next = new node(other_itr->val);

		// Increment iterators
		this_itr = this_itr->next;
        other_itr = other_itr->next;
	}
}

void linked_list::operator=(const linked_list& other) {
    // If the lists are the same, return
    if (this == &other) {
        return;
    }

	// Delete this list
	node* current = head;
	while (current != nullptr) {
		node* next = current->next;
		delete current;
		current = next;
	}

	// Make a new one
	if (other.length == 0) {
		return;
	}

	// Similar logic to the copy constructor here
	head = new node(other.head->val);
    node* this_itr = head;
    node* other_itr = other.head->next;

    while (other_itr != nullptr) {
        this_itr->next = new node(other_itr->val);
        this_itr = this_itr->next;
        other_itr = other_itr->next;
    }

    length = other.length;
}

linked_list::~linked_list() {
	// Delete this list
	node* current = head;
	while (current != nullptr) {
		node* next = current->next;
		delete current;
		current = next;
	}
}

int linked_list::get_length() {
	return this->length;
}

void linked_list::print() {
	node* current = this->head;
	while (current != nullptr) {
		std::cout << current->val << " ";
		current = current->next;
	}
	std::cout << std::endl;
}

void linked_list::clear() {
	// Delete this list
	node* current = head;
	while (current != nullptr) {
		node* next = current->next;
		delete current;
		current = next;
	}

	this->head = nullptr;
	this->length = 0;
}

void linked_list::push_front(int value) {
	node* old_head = this->head;
	this->head = new node(value);
	this->head->next = old_head;
	this->length++;
}

void linked_list::push_back(int value) {
	if (this->head == nullptr) {
		this->head = new node(value);
		this->length++;
		return;
	}

	node* current = this->head;
	// While the next value in the list exists, icrement iterator
	while (current->next != nullptr) {
		current = current->next;
	}
	// Then add the new node
	current->next = new node(value);
	this->length++;
}

void linked_list::insert(int value, int index) {
	// If the index is out of bounds, return
	if (index < 0 || index > this->length) {
		return;
	}

	if (index == 0) {
		push_front(value);
		return;
	} else if (index == this->length) {
		push_back(value);
		return;
	}

	// Increment to the index just before the one we're inserting at
	node* current = this->head;
	for (int i = 0; i < index - 1; i++) {
		current = current->next;
	}

	// Create new node
	node* new_node = new node(value);

	// Assign the new node to point to the next one in the list
	new_node->next = current->next;
	// Add the new node to the list
	current->next = new_node;
	this->length++;
}

void linked_list::pop_front() {
	if (this->head == nullptr) {
		return;
	}

	// Store the next node, delete the head, re-assign head
	node* next = this->head->next;
	delete this->head;
	this->head = next;
	this->length--;
}

void linked_list::pop_back() {
	if (this->head == nullptr) {
		return;
	}

	// If the list is only 1 node long, delete it and return
	if (this->length == 1) {
		delete this->head;
		this->head = nullptr;
		this->length--;
		return;
	}

	// Otherwise, increment to the second to last node
	node* current = this->head;
	while (current->next->next != nullptr) {
		current = current->next;
	}

	// Delete the last one and assign this one to be the last
	delete current->next;
	current->next = nullptr;
	
	this->length--;
}

void linked_list::remove(int index) {
	// If the index is out of bounds, return
	if (index < 0 || index > this->length - 1) {
		return;
	}

	if (index == 0) {
		pop_front();
		return;
	} if (index == this->length - 1) {
		pop_back();
		return;
	}

	// Increment to the index just before the one we're deleting
	node* current = this->head;
	for (int i = 0; i < index - 1; i++) {
		current = current->next;
	}

	// Placeholder for next node
	node* next = current->next->next;

	// Delete the node at the specified index
	delete current->next;

	// Re-assing next pointer
	current->next = next;
	this->length--;
}

void linked_list::split_list(node* source, node** front, node** back) {
	// Slow and fast iterators
	node* slow = source;
	node* fast = source->next;

	// Iterate over the list such that when the fast iterator reaches
	// the end of the list, the slow iterator will reach the middle
	
	// That is, iterate fast twice as much as slow until it reaches the end
	while (fast != nullptr) {
		fast = fast->next;
		if (fast != nullptr) {
			slow = slow->next;
			fast = fast->next;
		}
	}

	// Front, or the first list gets the beginning node of the bigger list
	*front = source;

	// Back, or the second list gets the middle node of the bigger list
	*back = slow->next;

	// Seperate lists
	slow->next = nullptr;
}

node* linked_list::merge_sorted_lists(node* a, node* b, bool ascending) {
	// Base case - If we are at the end of either list, return the other node
	if (a == nullptr) {
		return b;
	} else if (b == nullptr) {
		return a;
	}

	// Resulting list
	node* result = nullptr;

	// If we are sorting for ascending values, 
	if (ascending) {
		// And the value of a is less than that of b, 
		if (a->val <= b->val) {
			// a becomes the first node in the resulting list
			result = a;
			// Then recurse one further down the line on a list
			result->next = this->merge_sorted_lists(a->next, b, ascending);

		// Otherwise, the value at b needs to come first
		} else {
			result = b;
			result->next = this->merge_sorted_lists(a, b->next, ascending);
		}

	// If we are sorting for descending values, opposite logic, same process
	} else {
		if (a->val >= b->val) {
			result = a;
			result->next = this->merge_sorted_lists(a->next, b, ascending);
		} else {
			result = b;
			result->next = this->merge_sorted_lists(a, b->next, ascending);
		}
	}

	// Return the node to store
	return result;
}

void linked_list::merge_sort(node** head_ref, bool ascending) {
	node* head = *head_ref;
	// Base cases - the list is of length 0 or 1 (already sorted)
	if (head == nullptr || head->next == nullptr) {
		return;
	}

	// New lists to split into 
	node* a;
	node* b;

	// Split the main list into smaller ones
	this->split_list(head, &a, &b);

	// Recurse on new halves of list
	this->merge_sort(&a, ascending);
	this->merge_sort(&b, ascending);

	// Update original list
	*head_ref = merge_sorted_lists(a, b, ascending);
}

void linked_list::sort_ascending() {
	bool ascending = true;
	merge_sort(&this->head, ascending);
}

void linked_list::sort_descending() {
	bool ascending = false;
	merge_sort(&this->head, ascending);
}
