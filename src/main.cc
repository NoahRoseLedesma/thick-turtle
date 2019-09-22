//
// Created by stott on 8/2/19.
//
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

#include "game.h"

int main() {
  Game game;
  game.InitWindow(800, 600);
  game.InitMap(10);
  game.InitCamera();
  game.Run();
  return 0;
}
