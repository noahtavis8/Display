#ifndef PLAYER_HPP
#define PLAYER_HPP

// Player interface
class player {
private:	
    int row_pos;
    int col_pos;
    int num_arrows = 0; 
    bool confused = false;
    bool alive = true;
    bool has_gold = false;
    bool win = false;

	// Hidden passage locations
	int hidden_passage_1[2] = {-1, -1};
	int hidden_passage_2[2] = {-1, -1};

	// Number of uses for the lucky ring
	int lucky_rings = 0;


protected:

public:

	/*
	 * Function: Default constructor
	 * Description: Constructs a default player object
	 */
	player() = default;

    /*
	 * Function: Constructor
	 * Description: Constructs player object with given position
     * Paremeters: Integer row and column positions
	 */
    player(int row_pos, int col_pos);

    /*
	 * Function: get_num_arrows
	 * Description: Getter for number of arrows
     * Returns: The number of arrows left
	 */
    int get_num_arrows() const;

     /*
	 * Function: get_row_pos
	 * Description: Getter for player's row position
     * Returns: The row position for the player
	 */
    int get_row_pos() const;

    /*
	 * Function: get_col_pos
	 * Description: Getter for player's column position
     * Returns: The column position for the player
	 */
    int get_col_pos() const;

    /*
	 * Function: subtract_arrow
	 * Description: Subtracts one from the player's arrow count
	 */
    void subtract_arrow();

    /*
	 * Function: add_arrow
	 * Description: Adds one from the player's arrow count
	 */
    void add_arrow();

    /*
	 * Function: is_here
	 * Description: Determines whether the player is at a given position
     * Paremeters: Integer row and column positions
     * Returns: True if the player is at the position, false otherwise
	 */
    bool is_here(int row_pos, int col_pos) const;

    /*
	 * Function: is_confused
	 * Description: Determines whether the player is confused
     * Returns: True if the player is confused, false otherwise
	 */
    bool is_confused();

    /*
	 * Function: confuse
	 * Description: Confuses the player
	 */
    void confuse();

    /*
	 * Function: unconfuse
	 * Description: Un-confuses the player
	 */
    void unconfuse();

    /*
	 * Function: is_alive
	 * Description: Determines whether the player is alive
     * Returns: True if the player is alive, false otherwise
	 */
    bool is_alive() const;

    /*
	 * Function: has_won
	 * Description: Determines whether the player has won
     * Returns: True if the player won, false otherwise
	 */
    bool has_won() const;

    /*
	 * Function: player_won
	 * Description: Sets win to true
	 */
    void player_won();
    
    /*
	 * Function: has_found_gold
	 * Description: Determines whether the player has found the gold
     * Returns: True if the player has the gold, false otherwise
	 */
    bool has_found_gold();

    /*
	 * Function: cam_move
	 * Description: Determines whether the player can move in a given direction
     * Paremeters: 
     *      direction (char): direction to move in
     *      width (int): width of board
     *      height (int): height of board
     * Returns: True if the player can move in the given direction, false if not
	 */
    bool can_move(char direction, int width, int height);

    /*
	 * Function: move_up
	 * Description: Moves the player up one grid space
	 * Pre-condition: Player is capable of moving in this direction (without
	 * 		hitting the edge of the board)
	 * Post-condition: Player is moved accordingly.
	 */
	void move_up();

	/*
	 * Function: move_down
	 * Description: Moves the player down one grid space
	 * Pre-condition: Player is capable of moving in this direction (without
	 * 		hitting the edge of the board)
	 * Post-condition: Player is moved accordingly.
	 */
	void move_down();

	/*
	 * Function: move_left
	 * Description: Moves the player left one grid space
	 * Pre-condition: Player is capable of moving in this direction (without
	 * 		hitting the edge of the board)
	 * Post-condition: Player is moved accordingly.
	 */
	void move_left();

	/*
	 * Function: move_right
	 * Description: Moves the player right one grid space
	 * Pre-condition: Player is capable of moving in this direction (without
	 * 		hitting the edge of the board)
	 * Post-condition: Player is moved accordingly.
	 */
	void move_right();

	/*
	 * Function: found_gold
	 * Description: Updates the has_gold boolean to true
	 */ 
    void found_gold();

    /*
	 * Function: kill
	 * Description: Kills the player
	 */
    void kill();

    /*
	 * Function: set_hidden_passage_1
	 * Description: Sets the coordinates for this hidden passage, so the player
	 * 		can warp when they encounter each hidden passage
	 */
	void set_hidden_passage_1(int row, int col);

	/*
	 * Function: set_hidden_passage_2
	 * Description: Sets the coordinates for this hidden passage, so the player
	 * 		can warp when they encounter each hidden passage
	 */
	void set_hidden_passage_2(int row, int col);

	/*
	 * Function: has_hidden_passage_1
	 * Description: Checks whether the first hidden passage coordinates have
	 * 		been set
	 * Returns: True if they have, false if not
	 */
	bool has_hidden_passage_1();

	/*
	 * Function: is_at_hidden_passage_1
	 * Description: Checks whether the players position matches the first hidden 
	 * 		passage's coordinates
	 * Returns: True if they do, false if not
	 */
	bool is_at_hidden_passage_1();

	/*
	 * Function: warp_to_hidden_passage_1
	 * Description: Changes the position of the player to the location of the 
	 * 		first hidden passage
	 */
	void warp_to_hidden_passage_1();

	/*
	 * Function: warp_to_hidden_passage_2
	 * Description: Changes the position of the player to the location of the 
	 * 		second hidden passage
	 */
	void warp_to_hidden_passage_2();

	/*
	 * Function: found_lucky_ring
	 * Description: Sets the number of lucky ring uses the player has to 2
	 */
	void found_lucky_ring();

};


#endif
