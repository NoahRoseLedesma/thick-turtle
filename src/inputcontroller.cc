//
// Created by stott on 8/17/19.
//

#include "inputcontroller.h"

InputController::InputController(Game *p_game, Player *p_player)
    : m_current_game(p_game), m_current_player(p_player){

}

InputController::~InputController() {

}

AxialCoordinate InputController::GetTileClickedOn(sf::Event::MouseButtonEvent &event) {
    return m_current_game->PixelToAxial(event.x, event.y);
}
