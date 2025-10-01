#include "bottomless_pit.hpp"
#include <cstdlib>

bottomless_pit::bottomless_pit() : event('P') {}

event* bottomless_pit::clone() const {
    return new bottomless_pit(*this);
}

void bottomless_pit::precept() {
    std::cout << "You feel a breeze." << std::endl;
}

bool bottomless_pit::encounter(player& p) {

    std::cout << std::endl << std::endl 
        << "You encountered a bottomless pit!" << std::endl;

    // If a random 1-100 number is <= 75 (it should be 75% of the time)
    if ((rand() % 100) + 1 <= 75) {
        // The player lived
        std::cout << "You narrowly missed falling in.";
    
    // Otherwise they died
    } else {
        std::cout << "You misstepped and fell to your death." << std::endl;
        p.kill();
    }
    return false;
}