#include "event.hpp"

// Event implementation (define non-pure-virtual event member functions below,
// if relevant)

event::event(char s) : debug_symbol(s) {}

void event::print_debug_symbol() const {
    std::cout << this->debug_symbol;
}

char event::get_debug_symbol() {
    return this->debug_symbol;
}