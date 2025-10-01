#include <iostream>
#include "room.hpp"

room::room() : room_event(nullptr) {}

room::room(const room& other) {
    // If the other room's event exists, clone it
    if (other.room_event) {
        this->room_event = other.room_event->clone();
    } else {
    // Otherwise, set this one to null
        this->room_event = nullptr;
    }
}

room& room::operator=(const room& other) {
    // If the rooms are the same, return
    if (this == &other) {
        return *this;
    }

    // Otherwise, delete current event
    delete this->room_event;

    // And check if the other room's event exists and act accordingly
    if (other.room_event) {
        this->room_event = other.room_event->clone();
    } else {
        this->room_event = nullptr;
    }

    return *this;
}

room::~room() {
    delete this->room_event;
}

void room::set_event(event* e) {
    // If the event to be assigned is already there, return
    if (this->room_event == e) {
        return;
    }

    // If there is already an event, delete it
    if (this->room_event) {
        delete this->room_event;
    }
    this->room_event = e;
}

event* room::get_event() const {
    return this->room_event;
}

void room::print_debug_symbol() const {
    if (this->room_event) {
        this->room_event->print_debug_symbol();
    } else {
        std::cout << " ";
    }
}
