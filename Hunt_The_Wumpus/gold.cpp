#include "gold.hpp"

// TODO Gold implementation (define gold member functions below)

gold::gold() : event('G') {}

event* gold::clone() const {
    return new gold(*this);
}

void gold::precept() {
    std::cout << "You stub your toe on something heavy." << std::endl;
}

bool gold::encounter(player& p) {
    std::cout << std::endl << "You found the Wumpus's gold!";
    p.found_gold();
    return true;
}
