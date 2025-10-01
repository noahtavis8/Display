#include "wumpus.hpp"

wumpus::wumpus() : event('W') {}

event* wumpus::clone() const {
    return new wumpus(*this);
}

void wumpus::precept() {
    std::cout << "The hairs stand up on the back of your neck." << std::endl;
}

bool wumpus::encounter(player& p) {
    std::cout << std::endl << "You found the Wumpus! It kills you." << std::endl;
    p.kill();
    return false;
}
