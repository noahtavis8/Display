#ifndef ARROW_HPP
#define ARROW_HPP

#include "event.hpp"

// Arrow interface
class arrow : public event {
public:

	/*
	 * Function: Constructor
	 * Description: Constructs arrow object
	 */
	arrow();

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
