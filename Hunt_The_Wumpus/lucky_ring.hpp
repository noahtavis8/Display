#ifndef LUCKY_RING_HPP
#define LUCKY_RING_HPP

#include "event.hpp"

// lucky_ring interface
class lucky_ring : public event {
public:

	/*
	 * Function: Constructor
	 * Description: Constructs lucky_ring object
	 */
	lucky_ring();

	/*
	 * Function: clone
	 * Description: Pure virtual copy constructor
	 */
    event* clone() const;

	/*
	 * Function: precept
	 * Description: Prints this events precept
	 */
	void precept();

	/*
	 * Function: encounter
	 * Description: Preforms the actions necessary when encountering this event
	 * Parameters: Reference to the player object
	 * Returns: Boolean dictating whether the event needs to be removed or not
	 */
	bool encounter(player& p);
};


#endif