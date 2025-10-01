#ifndef ROOM_HPP
#define ROOM_HPP

#include "event.hpp"

// Room interface
class room {
private: 
	event* room_event;		// Pointer to an event object
public:
	/*
	 * Function: Default Constructor
	 * Description: Constructs room object with default values
	 */
	room();

	/*
	 * Function: Copy Constructor
	 * Description: Constructs room object based on one to copy
	 * Parameters:
	 * 		other (Room&): room to copy
	 */
	room(const room& other);

	/*
	 * Function: AOO
	 * Description: Copies one room object from another
	 * Parameters:
	 * 		other (Room&): room to copy
	 */
	room& operator=(const room& other);

	/*
	 * Function: Destructor
	 * Description: Deconstructs room object
	 */
	~room();

	/*
	 * Function: set_event
	 * Description: Assigns the room an event
	 * Parameters:
	 * 		e (event*): event to be assigned
	 */
	void set_event(event* e);

	/*
	 * Function: get_event
	 * Description: Returns a pointer to the rooms event
	 */
	event* get_event() const;

	/*
	 * Function: print_debug_symbol
	 * Description: Prints this rooms debug symbol or a space if there isnt an
	 * 		event there
	 */
	void print_debug_symbol() const;
};

#endif
