#ifndef GOLD_HPP
#define GOLD_HPP

#include "event.hpp"

// Gold interface
class gold : public event {
public:

	/*
	 * Function: Constructor
	 * Description: Constructs gold object
	 */
	gold();

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
