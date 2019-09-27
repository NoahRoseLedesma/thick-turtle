//
// Created by stott on 8/17/19.
//

#pragma once

#include "game.h"
#include "player.h"
#include <SFML/Window/Event.hpp>

class Game;

class Player;

class InputController {
public:
  explicit InputController(Game *p_game);

  ~InputController();

  AxialCoordinate GetTileClickedOn(const sf::Event::MouseButtonEvent &event);

  void DebugEventClick(const sf::Event::MouseButtonEvent &event);

private:
  Game *m_current_game;
  // we may not actually need to have this, but I thought it may be useful
  Player *m_current_player;
};

