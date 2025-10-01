#include <iostream>
#include <cstdlib>

#include "game.hpp"
#include "gold.hpp"
#include "bat_swarm.hpp"
#include "bottomless_pit.hpp"
#include "wumpus.hpp"
#include "escape_rope.hpp"
#include "arrow.hpp" 
#include "hidden_passage.hpp"
#include "lucky_ring.hpp"

// game implementation

std::vector<std::vector<room>> game::create_room_vector(int width, int height) {
	std::vector<std::vector<room>> rooms;

	// For every row of rooms, 
	for (int i = 0; i < height; i++) {

		// Make a vector for them
		std::vector<room> row(width, room()); 

		// Add the row to the rooms vector
		rooms.push_back(row);
	}

	// Return 2D vector of empty rooms
	return rooms;

}

std::vector<event*> game::create_events() {
	// Create pointers to heap-allocated event objects
	event* w = new wumpus;
	event* g = new gold;
	event* r = new escape_rope;
	event* a1 = new arrow;
	event* a2 = new arrow;
	event* p1 = new bottomless_pit;
	event* p2 = new bottomless_pit;
	event* b1 = new bat_swarm;
	event* b2 = new bat_swarm;
	event* h1 = new hidden_passage;
	event* h2 = new hidden_passage;
	event* l = new lucky_ring;

	// Populate an events vector with the pointers to the events
	std::vector<event*> events = {w, g, r, a1, a2, p1, p2, b1, b2, h1, h2, l};

	return events;
}

void game::populate_rooms_with_events(int width, int height) {

	// Create vector of necessary events
	std::vector<event*> events = this->create_events();

	// Ints for random row and column numbers
	int x = 0;
	int y = 0;

	// For every event to be placed, 
	for (int i = 0; i < events.size(); ++i) {
		// Generate a random row / column index
		x = rand() % height;
		y = rand() % width;

		// If that room does not have an event, populate it with the next event
		// to be placed
		if (this->rooms.at(x).at(y).get_event() == nullptr) {
			rooms.at(x).at(y).set_event(events[i]);

			// If the event being assigned is an escape rope, make a player
			// object with those coordinates and store it in the player 
			// member var
			if (events.at(i)->get_debug_symbol() == 'R') {
				this->p = player(x, y);

			// If its a Wumpus, store its coordinates for arrow mechanics
			} else if (events.at(i)->get_debug_symbol() == 'W') {
				this->wumpus_row = x;
				this->wumpus_col = y;

			// If its a hidden passage, send the coordinates to the appropriate
			// player member variables
			} else if (events.at(i)->get_debug_symbol() == 'H') {
				if (!this->p.has_hidden_passage_1()) {
					this->p.set_hidden_passage_1(x, y);
				} else {
					this->p.set_hidden_passage_2(x, y);
				}	
			}

		// Otherwise, we need to try again, so de-increment
		} else {
			i--;
		}
	}
}

game::game(int width, int height, bool debug, bool wumpus_move) :
		width(width),
		height(height),
		debug(debug),
		wumpus_can_find_player(wumpus_move) {

	// Create 2D vector of rooms
	this->rooms = this->create_room_vector(width, height);

	// Populate it with the necessary events
	this->populate_rooms_with_events(width, height);
}

void game::display_game() const {
	std::cout << std::endl << std::endl;
	std::cout << "Arrows remaining: " << this->p.get_num_arrows() << std::endl;

	std::string row_border = "+";
	for (int i = 0; i < this->width; ++i) {
		row_border += "--+";
	}

	std::cout << row_border << std::endl;
	for (int i = 0; i < this->height; ++i) { // For each row
		std::cout << "|";
		for (int j = 0; j < this->width; ++j) { // For each column
			// The first char indicates whether the player is in
			// the room at row index i, column index j. 
			
			// If the player is in the given room, print an *
			if (p.is_here(i, j)) {
				std::cout << "*";
			// Otherwise, print a space
			} else {
				std::cout << " ";
			}

			// The next char indicates the event in the room.
			
			// If we are in debug mode, print debug symbols
			if (this->debug) {
				rooms[i][j].print_debug_symbol();
			// Otherwise print spaces
			} else {
				std::cout << " ";
			}

			std::cout << "|";
		}
		std::cout << std::endl;
		std::cout << row_border << std::endl;
	}

	//example output (when finished): 
	// +--+--+--+--+
	// | P| G| P|  |
	// +--+--+--+--+
	// |  | W|  | B|
	// +--+--+--+--+
	// | A|  |  |  |
	// +--+--+--+--+
	// |*R| B| A|  |
	// +--+--+--+--+
}

bool game::check_win() const{
	if (this->p.has_won()) {
		std::cout << std::endl << "You won!!" << std::endl << std::endl;
		return true;
	}

	return false;
}

bool game::check_lose() const{
	// If the player is not alive, they lost
	if (!this->p.is_alive()) {
		std::cout << std::endl << "You lost." << std::endl << std::endl;
		return true;
	}

	return false;
}

bool game::is_direction(char c) {
	return c == 'w' ||
		c == 'a' ||
		c == 's' ||
		c == 'd';
}

char game::to_lower(char direction) {
	if (direction >= 'A' && direction <= 'Z') {
		return direction + ('a' - 'A');
	}
	return direction;
}

bool game::can_move_in_direction(char direction) {
	return this->p.can_move(direction, this->width, this->height);
}

bool game::is_valid_action(char action) {
	if (this->is_direction(action)) {
		char direction = action;
		return this->can_move_in_direction(direction);
	} else if (action == 'f') {
		return this->p.get_num_arrows() > 0;
	}
	return false;
}

void game::print_action_error(char action) {
	if (this->is_direction(action)) {
		std::cout << std::endl << "You can't move in that direction!" <<
			std::endl;
	} else if (action == 'f') {
		std::cout << std::endl << "You're out of arrows!" << std::endl;
	} else {
		std::cout << std::endl << "That's an invalid input!" << std::endl;
	}
}

char game::get_player_action() {
	char action;
	bool first = true;
	do {
		if (!first) {
			char previous_action = action;
			this->print_action_error(previous_action);
		}
		first = false;

		std::cout << std::endl << std::endl << "What would you like to do?" <<
			std::endl << std::endl;
		std::cout << "w: move up" << std::endl;
		std::cout << "a: move left" << std::endl;
		std::cout << "s: move down" << std::endl;
		std::cout << "d: move right" << std::endl;
		std::cout << "f: fire an arrow" << std::endl;

		std::cin >> action;
		action = this->to_lower(action);
	} while (!this->is_valid_action(action));

	return action;
}

char game::get_arrow_fire_direction() {
	char direction;
	bool first = true;
	do {
		if (!first) {
			std::cout << std::endl << "That's an invalid input!" <<
				std::endl << std::endl;
		}
		first = false;

		std::cout << std::endl << std::endl <<
			"What direction would you like to fire the arrow?" << std::endl <<
			std::endl;
		std::cout << "w: up" << std::endl;
		std::cout << "a: left" << std::endl;
		std::cout << "s: down" << std::endl;
		std::cout << "d: right" << std::endl;

		std::cin >> direction;
		direction = this->to_lower(direction);
	} while (!this->is_direction(direction));

	return direction;
}

void game::random_move() {
	bool loop = true;

	// While the random direction is not one that the player can move in, 
	while (loop) {
		// Choose a random [0-3] number / direction
		int choice = rand() % 4;

		if (choice == 0) {
			// Check if they can move in that direction
			if (this->can_move_in_direction('w')) {
				// If they can, move there and break the loop
				this->p.move_up();
				loop = false;
			}
		} else if (choice == 1) {
			if (this->can_move_in_direction('a')) {
				this->p.move_left();
				loop = false;
			}
		} else if (choice == 2) {
			if (this->can_move_in_direction('s')) {
				this->p.move_down();
				loop = false;
			}
		} else if (choice == 3) {
			if (this->can_move_in_direction('d')) {
					this->p.move_right();
					loop = false;
			}
		}

	} // end while
}


void game::move(char direction) {
	// If the player is confused,
	if (this->p.is_confused()) {
		// move them randomly
		this->random_move();

	// Otherwise, 

	// Move up
	} else if (direction == 'w') {
		this->p.move_up();

	// Move left
	} else if (direction == 'a') {
		this->p.move_left();

	// Move down
	} else if (direction == 's') {
		this->p.move_down();

	// Move right
	} else {
		this->p.move_right();
	}

	// Unconfuse the player after movement
	this->p.unconfuse();
}

bool game::wumpus_check_bounds(char direction) {
	if (direction == 'w' && (this->wumpus_row - 1) >= 0) {
        return true;
    } else if (direction == 'a' && (this->wumpus_col - 1) >= 0) {
        return true;
    } else if (direction == 's' && (this->wumpus_row + 1) <= (this->height - 1)) {
		return true; 
	} else if (direction == 'd' && (this->wumpus_col + 1) <= (this->width - 1)) {
		return true;
	}
	
    return false;
}

bool game::wumpus_check_events(char direction) {
	// Get wumpus position
	int row = this->wumpus_row;
	int col = this->wumpus_col;

	// Increment index according to direction
	if (direction == 'w') {
		row--;
    } else if (direction == 'a') {
		col--;
    } else if (direction == 's') {
		row++;
	} else if (direction == 'd') {
		col++;
	}

	// Return false if the room has an event and the wumpus cannot move
	// in that direction
	return !rooms.at(row).at(col).get_event();
}

bool game::wumpus_check_player(char direction) {
	// Gather wumpus pos
	int row = this->wumpus_row;
	int col = this->wumpus_col;

	// Gather player pos
	int player_row = this->p.get_row_pos();
	int player_col = this->p.get_col_pos();

	// For every direction, increment the wumpus's position accordingly
	if (direction == 'w') {
        row--;
    } else if (direction == 'a') {
        col--;
    } else if (direction == 's') {
		row++; 
	} else if (direction == 'd') {
		col++;
	}

	// If the wumpus's new direction is the same as the players, return false
	if (row == player_row && col == player_col) {
		return false;
	}

	// Otherwise, the player is not preventing the wumpus from moving, so
	return true;
}

void game::wumpus_move(char direction) {
	// Gather wumpus's coordinates
	int row = this->wumpus_row;
	int col = this->wumpus_col;

	// Make a new wumpus
	event* w = new wumpus;

	// Remove wumpus from current room
	rooms.at(row).at(col).set_event(nullptr);

	// Update position based on direction
	if (direction == 'w') {
		row--;
    } else if (direction == 'a') {
		col--;
    } else if (direction == 's') {
		row++;
	} else if (direction == 'd') {
		col++;
	}

	// Place wumpus in the new room
	rooms.at(row).at(col).set_event(w);

	// Update wumpus position
	this->wumpus_row = row;
	this->wumpus_col = col;

}

void game::move_wumpus_1() {
	bool tried_w = false;
	bool tried_a = false;
	bool tried_s = false;
	bool tried_d = false;

	// While the every direction has not been tried, 
	while (!tried_w || !tried_a || !tried_s || !tried_d) {
		// Generate random [0-3] number / direction
		int choice = rand() % 4;

		// Check if the wumpus can move there, and if they can move the wumpus
		if (choice == 0) {

			// Up
			if (this->wumpus_check_bounds('w') && this->wumpus_check_events('w')
				&& this->wumpus_check_player('w')) {
				this->wumpus_move('w');
				break;
			}
			tried_w = true;

			// Left
		} else if (choice == 1) {
			if (this->wumpus_check_bounds('a') && this->wumpus_check_events('a')
				&& this->wumpus_check_player('a')) {
				this->wumpus_move('a');
				break;
			}
			tried_a = true;

			// Down 
		} else if (choice == 2) {
			if (this->wumpus_check_bounds('s') && this->wumpus_check_events('s')
				&& this->wumpus_check_player('s')) {
				this->wumpus_move('s');
				break;
			}
			tried_s = true;

			// Right
		} else if (choice == 3) {
			if (this->wumpus_check_bounds('d') && this->wumpus_check_events('d')
				&& this->wumpus_check_player('d')) {
				this->wumpus_move('d');
				break;
			}
			tried_d = true;
		}
	}
}

void game::wumpus_found_player() {
    std::cout << std::endl << "The Wumpus found you! It kills you." << std::endl;
    this->p.kill();
}

void game::move_wumpus_2() {
	bool tried_w = false;
	bool tried_a = false;
	bool tried_s = false;
	bool tried_d = false;

	// While the every direction has not been tried, 
	while (!tried_w || !tried_a || !tried_s || !tried_d) {
		// Generate random [0-3] number / direction
		int choice = rand() % 4;

		// Check if the wumpus can move there, and if they can move the wumpus
		if (choice == 0) {

			// Up
			if (this->wumpus_check_bounds('w') && this->wumpus_check_events('w')) {
				this->wumpus_move('w');
				break;
			}
			tried_w = true;

			// Left
		} else if (choice == 1) {
			if (this->wumpus_check_bounds('a') && this->wumpus_check_events('a')) {
				this->wumpus_move('a');
				break;
			}
			tried_a = true;

			// Down 
		} else if (choice == 2) {
			if (this->wumpus_check_bounds('s') && this->wumpus_check_events('s')) {
				this->wumpus_move('s');
				break;
			}
			tried_s = true;

			// Right
		} else if (choice == 3) {
			if (this->wumpus_check_bounds('d') && this->wumpus_check_events('d')) {
				this->wumpus_move('d');
				break;
			}
			tried_d = true;
		}
	}

	// If the wumpus's new coordinates match the players, it found the player
	if (this->wumpus_row == this->p.get_row_pos() 
		&& this->wumpus_col == this->p.get_col_pos()) {
		this->wumpus_found_player();
	}
}

void game::arrow_hit_wumpus() {
	std::cout << std::endl << "You hit and killed the Wumpus!" << std::endl;
	std::cout << "All of its gold is yours for the taking." << std::endl;
	this->p.player_won();
}

char game::get_random_direction() {
	// Choose random [0-3] number / direction
	int choice = rand() % 4;

	// Return it
	if (choice == 0) {
		return 'w';
	} else if (choice == 1) {	
		return 'a';
	} else if (choice == 2) {
		return 's';
	} else {	
		return 'd';
	}

	return 'w';
}

void game::fire_arrow(char direction) {
	bool hit = false;

	// If the player is confused,
	if (this->p.is_confused()) {
		// Ramdomize direction
		direction = this->get_random_direction();
	
	// Otherwise, 
	}

	// Gather startint position of arrow
	int row = this->p.get_row_pos();
	int col = this->p.get_col_pos();

	// For three spaces, 
	for (int i = 0; i < 3; i++) {

		// Adjust the arrow's coordinates

		// Fire up
		if (direction == 'w') {
			row--;
		// Fire left
		} else if (direction == 'a') {
			col--;
		// Fire down
		} else if (direction == 's') {
			row++;
		// Fire right
		} else {
			col++;	
		}

		// If the arrow's coordinates match the wumpus's, 
		if (this->wumpus_row == row && this->wumpus_col == col) {
			// The arrow hit the wumpus
			this->arrow_hit_wumpus();
			hit = true;
		}
	}

	// If the player did not hit the wumpus, print a missed message
	if (!hit) {		
		std::cout << std::endl << "Your arrow missed.";
	}

	// Remove an arrow and unconfuse the player
	this->p.subtract_arrow();
	this->p.unconfuse();
}

void game::display_precepts() {
	int row_pos = this->p.get_row_pos();
	int col_pos = this->p.get_col_pos();

	// For every precept, we first must see if there is a room in each direction.
	// That logic is already implimented in the player can_move function.

	// Then, we need to see if that room has an event. If it does, call its
	// specific precept. Otherwise, do nothing

	// Up precept
	if (this->p.can_move('w', this->width, this->height)) {
		if (this->rooms.at(row_pos - 1).at(col_pos).get_event()) {
			this->rooms.at(row_pos - 1).at(col_pos).get_event()->precept();
		}
	}

	// Left precept
	if (this->p.can_move('a', this->width, this->height)) {
		if (this->rooms.at(row_pos).at(col_pos - 1).get_event()) {
			this->rooms.at(row_pos).at(col_pos - 1).get_event()->precept();
		}
	}

	// Down precept
	if (this->p.can_move('s', this->width, this->height)) {
		if (this->rooms.at(row_pos + 1).at(col_pos).get_event()) {
			this->rooms.at(row_pos + 1).at(col_pos).get_event()->precept();
		}
	}

	// Right precept
	if (this->p.can_move('d', this->width, this->height)) {
		if (this->rooms.at(row_pos).at(col_pos + 1).get_event()) {
			this->rooms.at(row_pos).at(col_pos + 1).get_event()->precept();
		}
	}
}

void game::play_game(){
	int row;
	int col;
	bool fired_arrow = false;
	while (!this->check_win() && !this->check_lose()) {
		// Reset fired_arrow
		fired_arrow = false;

		// Print game board
		this->display_game();

		// Display precepts
		this->display_precepts();
		
		// Ask player for their action
		char action = this->get_player_action();

		// Process action
		if (this->is_direction(action)) {
			// W/A/S/D = move player
			char direction = action;
			this->move(direction);
		} else {
			// F = prompt for arrow fire direction and fire arrow
			char direction = this->get_arrow_fire_direction();
			this->fire_arrow(direction);
			fired_arrow = true;
		}

		// If the player did not choose to fire an arrow, meaning they moved
		// to a different room,
		if (!fired_arrow) {
			// Gather coordinates
			row = this->p.get_row_pos();
			col = this->p.get_col_pos();

			// If there is an event in the given room, encounter it
			if (rooms.at(row).at(col).get_event()) {
				// If the event needs to be removed, remove it
				if (rooms.at(row).at(col).get_event()->encounter(this->p)) {
					rooms.at(row).at(col).set_event(nullptr);
				}
			}
		}

		// If the wumpus cannot move into the player's square,
		if (!this->wumpus_can_find_player) {
			this->move_wumpus_1();

		// Otherwise it can,
		} else {
			this->move_wumpus_2();
		}
	}
}
