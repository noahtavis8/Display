#include "hidden_passage.hpp"

hidden_passage::hidden_passage() : event('H') {}

event* hidden_passage::clone() const {
    return new hidden_passage(*this);
}

void hidden_passage::precept() {
    std::cout << "You hear water dripping." << std::endl;
}

bool hidden_passage::encounter(player& p) {
    std::cout << std::endl << "You found a hidden passage!";

    // Warp the player appropriately
    if (p.is_at_hidden_passage_1()) {
        p.warp_to_hidden_passage_2();
    } else {
        p.warp_to_hidden_passage_1();
    }
    return false;
}
