//
// Created by stott on 8/17/19.
//

#include <iostream>
#include "inputcontroller.h"

InputController::InputController(Game *p_game)
    : m_current_game(p_game) {
}

InputController::~InputController() {
}

AxialCoordinate InputController::GetTileClickedOn(
        const sf::Event::MouseButtonEvent &event) {
    return AxialCoordinate(event.x, event.y, this->m_current_game);
}

void InputController::DebugEventClick(
        const sf::Event::MouseButtonEvent &event) {
    std::cout << "x: " << event.x << ", y: " << event.y << std::endl;
}
