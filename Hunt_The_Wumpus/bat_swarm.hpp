#ifndef BAT_SWARM_HPP
#define BAT_SWARM_HPP

#include "event.hpp"

// Bat swarm interface
class bat_swarm : public event {
public:

	/*
	 * Function: Constructor
	 * Description: Constructs bat_swarm object
	 */
	bat_swarm();

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
