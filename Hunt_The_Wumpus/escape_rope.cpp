#include "escape_rope.hpp"

escape_rope::escape_rope() : event('R') {}

event* escape_rope::clone() const {
    return new escape_rope(*this);
}

void escape_rope::precept() {}

bool escape_rope::encounter(player& p) {
    if (p.has_found_gold()) {
        std::cout << std::endl 
            << "You made it back to your rope safely with the gold!" 
            << std::endl;
        p.player_won();
    }
    return false;
}