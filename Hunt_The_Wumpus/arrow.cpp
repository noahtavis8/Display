#include "arrow.hpp"

arrow::arrow() : event('A') {}

event* arrow::clone() const {
    return new arrow(*this);
}

void arrow::precept() {}

bool arrow::encounter(player& p) {
    std::cout << std::endl << "You found an arrow!";
    p.add_arrow();
    return true;
}

