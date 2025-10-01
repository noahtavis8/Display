#include "bat_swarm.hpp"

bat_swarm::bat_swarm() : event('B') {}

event* bat_swarm::clone() const {
    return new bat_swarm(*this);
}

void bat_swarm::precept() {
    std::cout << "You hear screeching." << std::endl;
}

bool bat_swarm::encounter(player& p) {
    std::cout << std::endl << "Bats swarm you!" << std::endl;
    std::cout << "You can't see where you're looking.";
    p.confuse();
    return false;
}
