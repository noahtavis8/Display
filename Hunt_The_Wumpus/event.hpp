#ifndef EVENT_HPP
#define EVENT_HPP

#include <iostream>
#include "player.hpp"

// Event interface
class event {
private:
	char debug_symbol;
public:

	/*
	 * Function: Constructor
	 * Description: Constructs event object with a debug symbol
	 */
	event(char s);

	/*
	 * Function: clone
	 * Description: Pure virtual copy constructor
	 */
	virtual event* clone() const = 0;

	/*
	 * Function: Destructor
	 * Description: Deconstructs event object
	 */
	virtual ~event() = default;

	/*
	 * Function: print_debug_symbol
	 * Description: Prints this events debug symbol
	 */
	void print_debug_symbol() const;

	/*
	 * Function: get_debug_symbol
	 * Description: Getter for debug symbol
	 * Returns: Debug symbol for this event
	 */
	char get_debug_symbol();

	/*
	 * Function: precept
	 * Description: Pure virtual display precept function
	 */
	virtual void precept() = 0;

	/*
	 * Function: encounter
	 * Description: Pure virtual encounter function
	 * Parameters: Reference to the player object
	 * Returns: Boolean dictating whether the event needs to be removed or not
	 */
	virtual bool encounter(player& p) = 0;
};

#endif
