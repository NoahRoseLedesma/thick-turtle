#include "game.h"

#include <functional>
#include "map.h"
#include "tile.h"

Game::~Game() {
  if(map)
    delete map;
  if(window) {
    if(window->isOpen()) {
      window->close();
    }
    delete window;
  }
}

// TODO: Asset managment system
Game::Game() {
  debugFont.loadFromFile("assets/fonts/FiraCode-Regular.ttf");
}

void Game::InitMap( size_t radius ) {
  auto DebugTileProducer = [](Map* map, AxialCoordinate&& coord) -> Tile* {
    return new DebugTile(map, coord);
  };

  map = new Map(radius, DebugTileProducer, this);
}

void Game::InitWindow( size_t desiredWidth, size_t desiredHeight ) {
  window = new sf::RenderWindow(sf::VideoMode(desiredWidth, desiredHeight),
                                "Thick Turtle");
}

size_t Game::GetWindowHeight() const {
  return window->getSize().y;
}

size_t Game::GetWindowWidth() const {
  return window->getSize().x;
}

void Game::Run() {
  while( window->isOpen() ) {
    sf::Event event;
    while( window->pollEvent(event) ) {
      if( event.type == sf::Event::Closed ) {
        window->close();
      }
    }
    window->clear();
    Think();
    window->display();
  }
}

void Game::Think() {
  window->draw(*map);
}
