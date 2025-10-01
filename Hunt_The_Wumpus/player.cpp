#include "player.hpp"

#include <iostream>

player::player(int row_pos, int col_pos) : row_pos(row_pos), col_pos(col_pos) {}

int player::get_num_arrows() const {
    return this->num_arrows;
}

int player::get_row_pos() const {
    return this->row_pos;
}

int player::get_col_pos() const {
    return this->col_pos;
}

void player::subtract_arrow() {
    this->num_arrows--;
}

void player::add_arrow() {
    this->num_arrows++;
}

bool player::is_here(int row_pos, int col_pos) const {
    // If the position given matches the player's, return true
    if (this->row_pos == row_pos && this->col_pos == col_pos) {
        return true;
    }

    return false;
}

bool player::is_confused() {
    return this->confused;
}

void player::confuse() {
    this->confused = true;
}

void player::unconfuse() {
    this->confused = false;
}

bool player::is_alive() const {
    return this->alive;
}

bool player::has_won() const {
    return this->win;
}

void player::player_won() {
    this->win = true;
}

bool player::has_found_gold() {
    return this->has_gold;
}

bool player::can_move(char direction, int width, int height) {
 
    if (direction == 'w' && (this->row_pos - 1) >= 0) {
        return true;
    } else if (direction == 'a' && (this->col_pos - 1) >= 0) {
        return true;
    } else if (direction == 's' && (this->row_pos + 1) <= (height - 1)) {
		return true; 
	} else if (direction == 'd' && (this->col_pos + 1) <= (width - 1)) {
		return true;
	}

    return false;
}

void player::move_up() {
    this->row_pos--;
}

void player::move_down() {
    this->row_pos++;
}

void player::move_left() {
    this->col_pos--;
}

void player::move_right() {
    this->col_pos++;
}

void player::found_gold() {
    this->has_gold = true;
}

void player::kill() {
    // Kill the player
    this->alive = false;

    // Revive them if they have lucky ring uses
    if (this->lucky_rings != 0) {
        std::cout << std::endl << "But wait!" << std::endl;
        std::cout << "Your lucky ring saves you!" << std::endl;
        this->alive = true;
    }

    // Print appropriate ring message and deincrement number of uses left
    if (this->lucky_rings == 2) {
        std::cout << std::endl << "You feel it get weaker.";
        this->lucky_rings--;
    } else if  (this->lucky_rings == 1) {
        std::cout << std::endl << "It crumbles off of your finger.";
        this->lucky_rings--;
    }

}

void player::set_hidden_passage_1(int row, int col) {
    this->hidden_passage_1[0] = row;
    this->hidden_passage_1[1] = col;
}

void player::set_hidden_passage_2(int row, int col) {
    this->hidden_passage_2[0] = row;
    this->hidden_passage_2[1] = col;
}

bool player::has_hidden_passage_1() {
    if (this->hidden_passage_1[0] != -1) {
        return true;
    }

    return false;
}

bool player::is_at_hidden_passage_1() {
    // If the player's position matches the first hidden passage's position
    if (this->row_pos == this->hidden_passage_1[0]
        && this->col_pos == this->hidden_passage_1[1] ) {

        // Return true
        return true;
    }

    return false;
}

void player::warp_to_hidden_passage_1() {
    this->row_pos = this->hidden_passage_1[0];
    this->col_pos = this->hidden_passage_1[1];
}

void player::warp_to_hidden_passage_2() {
    this->row_pos = this->hidden_passage_2[0];
    this->col_pos = this->hidden_passage_2[1];
}

void player::found_lucky_ring() {
    this->lucky_rings = 2;
}