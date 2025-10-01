#ifndef HIDDEN_PASSAGE_HPP
#define HIDDEN_PASSAGE_HPP

#include "event.hpp"

// hidden_passage interface
class hidden_passage : public event {
public:

	/*
	 * Function: Constructor
	 * Description: Constructs hidden_passage object
	 */
	hidden_passage();

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