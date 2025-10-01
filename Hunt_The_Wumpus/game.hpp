#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include "room.hpp"
#include "player.hpp"

// game interface
class game {
private:

	int width;				// width of the game grid
	int height;				// height of the game grid
	bool debug;				// debug mode or not
	bool wumpus_can_find_player;		// wumpus can find player or not

	std::vector<std::vector<room>> rooms;	// 2D room vector
	player p;								// player object

	// Wumpus location
	int wumpus_row;
	int wumpus_col;

public:
	
	/*
	 * Function: create_room_vector
	 * Description: Creates a 2D vector of rooms
	 * Parameters:
	 * 		width (int): Width of the grid
	 * 		height (int): Height of the grid
	 * Returns: A 2D vector of default rooms
	 */
	std::vector<std::vector<room>> create_room_vector(int width, int height);

	/*
	 * Function: create_events
	 * Description: Creates a vector of pointers to each necessary event 
	 * 		subclass object and returns it
	 * Returns: A vector of events objects to give to the rooms vector
	 */
	std::vector<event*> create_events();

	/*
	 * Function: populate_rooms_with_events
	 * Description: Populates the rooms vector with the necessary events in a 
	 * 		random manner
	 */
	void populate_rooms_with_events(int width, int height);

	/*
	 * Function: Constructor
	 * Description: Constructs game object with a grid matching the given
	 * 		width and height
	 * Parameters:
	 * 		width (int): Width of the grid
	 * 		height (int): Height of the grid
	 * 		debug (bool): Whether or not debug mode should be enabled
	 * 		wumpus_move(bool): Whether the wumpus can find the player when it moves
	 */
	game(int width, int height, bool debug, bool wumpus_move);

	/*
	 * Function: display_precepts
	 * Description: Displays the precepts for each adjacent room
	 */
	void display_precepts();

	/*
	 * Function: display_game
	 * Description: Displays the game grid in the terminal
	 */
	void display_game() const;

	/*
	 * Function: check_win
	 * Description: Determines whether the player has won the game
	 * Returns (bool): True if the player has won, false otherwise
	 */
	bool check_win() const;

	/*
	 * Function: check_lose
	 * Description: Determines whether the player has lost the game
	 * Returns (bool): True if the player has lost, false otherwise
	 */
	bool check_lose() const;

	/*
	 * Function: is_direction
	 * Description: Returns true if the given character is a valid direction
	 * 		character (w/a/s/d) and false otherwise
	 * Parameters:
	 * 		c (char): The character to check
	 * Returns (bool): Boolean indicating whether the character is a valid
	 * 		direction character (w/a/s/d)
	 */
	bool is_direction(char c);

	/*
	 * Function: to_lower
	 * Description: Converts a given character to lowercase. Used to standardize
	 * 		a user's character input.
	 * Parameters:
	 * 		direction (char): Character to convert to lowercase
	 * Returns (char): Character converted to lowercase
	 */
	char to_lower(char direction);

	/*
	 * Function: can_move_in_direction
	 * Description: Determines whether the player can move in the given
	 * 		direction, based on their current location and the size of the
	 * 		grid.
	 * Parameters:
	 * 		direction (char): Direction the player wishes to move in
	 * Returns (bool): True if the player can move in the given direction
	 * 		without moving off the grid. False otherwise.
	 */
	bool can_move_in_direction(char direction);

	/*
	 * Function: is_valid_action
	 * Description: Determines whether the given action is valid.
	 * Parameters:
	 * 		action (char): Action the player wishes to perform.
	 * Returns (bool): True if the requested action is valid. False otherwise.
	 */
	bool is_valid_action(char action);

	/*
	 * Function: print_action_error
	 * Description: Prints a clear error message associated with the user's
	 * 		provided invalid action
	 * Parameters:
	 * 		action (char): Invalid action that the user requested
	 */
	void print_action_error(char action);

	/*
	 * Function: get_player_action
	 * Description: Prompts the player for their action for the turn and
	 * 		returns it as a char (w, a, s, d, or f). If the player enters
	 * 		an invalid action, this function reprompts until a valid one is
	 * 		provided.
	 * Returns (char): The valid action provided by the player.
	 */
	char get_player_action();

	/*
	 * Function: get_arrow_fire_direction
	 * Description: Prompts the player for the direction they want to fire an
	 * 		arrow (w, a, s, or d) and returns it as a char. If the player enters
	 * 		an invalid direction, this function reprompts until a valid one is
	 * 		provided.
	 * Returns (char): The valid direction provided by the player.
	 */
	char get_arrow_fire_direction();

	/*
	 * Function: random_move
	 * Description: Moves the player in a random direction
	 * Pre-condition: Player is confused
	 * Post-condition: Player is moved accordingly.
	 */
	void random_move();

	/*
	 * Function: move
	 * Description: Moves the player in the direction specified by the given
	 * 		character
	 * Parameters:
	 * 		direction (char): Direction in which to move the player (a for
	 * 			west, s for south, d for east, w for north).
	 * Pre-condition: Player is capable of moving in this direction (without
	 * 		hitting the edge of the board)
	 * Post-condition: Player is moved accordingly.
	 */
	void move(char direction);

	/*
	 * Function: wumpus_check_bounds
	 * Description: Checks if the wumpus cannot move in a given direction due to
	 * 		gameboard bounds
	 * Returns: True if there are no gameboard bounds preventing the wumpus from
	 * 		moving, false otherwise
	 */
	bool wumpus_check_bounds(char direction);

	/*
	 * Function: wumpus_check_events
	 * Description: Checks if the wumpus cannot move in a given direction due to
	 * 		events already being in the location
	 * Returns: True if there are no events preventing the wumpus from
	 * 		moving, false otherwise
	 */
	bool wumpus_check_events(char direction);

	/*
	 * Function: wumpus_check_player
	 * Description: Checks if the wumpus cannot move in a given direction due to
	 * 		the player already being in the location
	 * Returns: True if the player is not preventing the wumpus from
	 * 		moving, false otherwise
	 */
	bool wumpus_check_player(char direction);

	/*
	 * Function: wumpus_move
	 * Description: Moves wumpus in given direction
	 * Parameters: Char indicating direction to move wumpus
	 * Pre-condition: Direction given is one that the wumpus can move in
	 * Post-condition: Wumpus is moved accordingly
	 */
	void wumpus_move(char direction);

	/*
	 * Function: move_wumpus_1
	 * Description: Attempts to move the wumpus in a random direction when IT 
	 * 		CANNOT move into the player's square
	 * Pre-condition: Wumpus is capable of moving in random direction (without
	 * 		hitting the edge of the board or other events OR THE PLAYER)
	 * Post-condition: Wumpus is moved accordingly, or not if it is not capable
	 */
	void move_wumpus_1();

	/*
	 * Function: wumpus_found_player
	 * Description: Prints a message stating the wumpus found the player, and 
	 * 		kills the player
	 */
	void wumpus_found_player();

	/*
	 * Function: move_wumpus_2
	 * Description: Attempts to move the wumpus in a random direction when IT 
	 * 		CAN move into the player's square
	 * Pre-condition: Wumpus is capable of moving in random direction (without
	 * 		hitting the edge of the board or other events)
	 * Post-condition: Wumpus is moved accordingly, or not if it is not capable
	 */
	void move_wumpus_2();

	/*
	 * Function: arrow_hit_wumpus
	 * Description: Prints a message stating the player hit the wumpus with
	 * 		their arrow, and ends the game
	 * Side effects: The player wins and the game ends
	 */
	void arrow_hit_wumpus();

	/*
	 * Function: get_random_direction
	 * Description: Gathers a random direction for which to fire an arrow if
	 * 		the player if confused
	 */
	char get_random_direction();

	/*
	 * Function: fire_arrow
	 * Description: Fires an arrow in the direction specified by the given
	 * 		character
	 * Parameters:
	 * 		direction (char): Direction in which to fire arrow (a for
	 * 			west, s for south, d for east, w for north).
	 * Post-condition: Arrow is fired. Wumpus is killed if hit
	 */
	void fire_arrow(char direction);

	/*
	 * Function: play_game
	 * Description: Runs one full iteration of the game
	 */
	void play_game();
};
#endif
