//
// Created by stott on 8/17/19.
//

#pragma once

#include "game.h"
#include "player.h"
#include <SFML/Window/Event.hpp>

class InputController {
 public:
    InputController(Game* p_game, Player* p_player);
    ~InputController();
    AxialCoordinate GetTileClickedOn(sf::Event::MouseButtonEvent& event);
 private:
    Game* m_current_game;
    Player* m_current_player;
};

