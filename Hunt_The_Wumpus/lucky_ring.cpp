#include "lucky_ring.hpp"

lucky_ring::lucky_ring() : event('L') {}

event* lucky_ring::clone() const {
    return new lucky_ring(*this);
}

void lucky_ring::precept() {
    std::cout << "You feel like luck is on your side today." << std::endl;
}

bool lucky_ring::encounter(player& p) {
    std::cout << std::endl << "You found an old looking ring!" << std::endl;
    std::cout << "You feel luckier.";
    p.found_lucky_ring();
    return true;
}