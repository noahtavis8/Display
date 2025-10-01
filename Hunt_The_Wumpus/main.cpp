/*
 * Author: Noah Tavis
 * Program description: Simulates a game of Hunt the Wumpus
 * Date: May 27, 2025
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "game.hpp"

/*
 * Function: get_width
 * Description: Prompts the user for the game board width (# of columns)
 * Returns (int): Valid width supplied by user
 */
int get_width() {
	int width;
	bool first = true;
	do {
		if (!first) {
			std::cout << std::endl << "Invalid width!" << std::endl <<
				std::endl;
		}
		first = false;
		std::cout << "Enter the game board width between 4 and 30: ";
		std::cin >> width;
	} while(width < 4 || width > 30);
	return width;
}

/*
 * Function: get_height
 * Description: Prompts the user for the game board height (# of columns)
 * Returns (int): Valid height supplied by user
 */
int get_height() {
	int height;
	bool first = true;
	do {
		if (!first) {
			std::cout << std::endl << "Invalid height!" << std::endl <<
				std::endl;
		}
		first = false;
		std::cout << "Enter the game board height between 4 and 30: ";
		std::cin >> height;
	} while(height < 4 || height > 30);
	return height;
}

/*
 * Function: get_debug
 * Description: Prompts the user whether they want to play in debug mode
 * Returns (bool): True if the user wants to play in debug mode. False
 * 		otherwise.
 */
bool get_debug() {
	int debug_input;
	bool first = true;
	do {
		if (!first) {
			std::cout << std::endl << "Invalid input!" << std::endl <<
				std::endl;
		}
		first = false;
		std::cout << "Would you like to play in debug mode? (1-yes, 0-no): ";
		std::cin >> debug_input;
	} while(debug_input != 0 && debug_input != 1);
	return debug_input == 1;
}

/*
 * Function: get_wumpus_can_find_player
 * Description: Prompts the user whether they want the wumpus to be able to move
 * 		into the player's square or not
 * Returns (bool): True if the user wants wants the wumpus to be able to move in
 * 		the player's square, false otherwise
 */
bool get_wumpus_can_find_player() {
	std::cout << std::endl;
	int wumpus_input;
	bool first = true;
	do {
		if (!first) {
			std::cout << std::endl << "Invalid input!" << std::endl <<
				std::endl;
		}
		first = false;
		std::cout << "Would you like the wumpus to be able to move" << std::endl;
		std::cout << "into the player's square? (1-yes, 0-no): ";
		std::cin >> wumpus_input;
	} while(wumpus_input != 0 && wumpus_input != 1);
	return wumpus_input == 1;
}

/*
 * Function: main
 * Description: Prompts user for gameboard dimensions and for debug mode,
 * 		constructs a game object with given parameters, and plays the game
 */
int main()
{
	std::cout << std::endl;

	// Set the random seed
	srand(time(nullptr));
	
	// Ask user for width and height of game board
	int width = get_width();
	int height = get_height();

	// Ask user whether they want debug mode
	bool debug = get_debug();

	// Ask user whether they want the wumpus to be able to move into the
	// player's square
	bool wumpus_move = get_wumpus_can_find_player();

	// Construct game object
	game g(width, height, debug, wumpus_move);

	//Play game
	g.play_game();

	return 0;
}
