#include "game.h"

#include <functional>
#include "map.h"
#include "tile.h"

/*
 * Game Object
 */

/*
 * Game::~Game
 */
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

/*
 * Game::Game
 */
Game::Game() {
  // Create debug resources
  debugFont.loadFromFile("assets/fonts/FiraCode-Regular.ttf");
}

/*
 * Game::InitMap
 */
void Game::InitMap( size_t radius ) {
  auto DebugTileProducer = [](Map* map, AxialCoordinate&& coord) -> Tile* {
    return new DebugTile(map, coord);
  };

  mapRadius = radius;
  map = new Map(mapRadius, DebugTileProducer, this);
}

/*
 * Game::InitWindow
 */
void Game::InitWindow( size_t desiredWidth, size_t desiredHeight ) {
  window = new sf::RenderWindow(sf::VideoMode(desiredWidth, desiredHeight),
                                "Thick Turtle");
}

/*
 * Game::GetWindowHeight
 * Game::GetWindowWidth
 */
size_t Game::GetWindowHeight() const {
  return window->getSize().y;
}
size_t Game::GetWindowWidth() const {
  return window->getSize().x;
}

/*
 * Game::Run
 */
void Game::Run() {
  while( window->isOpen() ) {
    sf::Event event;
    while( window->pollEvent(event) ) {
      if( event.type == sf::Event::Closed ) {
        window->close();
      }
      if( event.type == sf::Event::Resized ) {
        // Invoke the handler for this event
        OnDisplayResize();
      }
    }
    window->clear();
    Think();
    window->display();
  }
}

/*
 * Game::Think
 */
void Game::Think() {
  window->draw(*map);
}

/*
 * Game::AxialToPixel
 */
sf::Vector2f Game::AxialToPixel(const AxialCoordinate& coordinate) const {
  // Determine the origin of the centroid hexagon
  // This should always be at the center of the display
  float xCenter = GetWindowWidth() / 2.; 
  float yCenter = GetWindowHeight() / 2.;
  // Determine the pixel offset from the centroid from the given position
  float deltaX = GetTileRadius() * (1.5 * coordinate.q);
  float deltaY = GetTileRadius() * (ROOT3/2. * coordinate.q
                                     + ROOT3 * coordinate.r);
  return {xCenter + deltaX, yCenter + deltaY};
}

sf::Vector2f Game::AxialToPixel(const AxialCoordinate&& coordinate) const {
  AxialCoordinate bind = coordinate;
  return AxialToPixel(bind);
}

AxialCoordinate Game::PixelToAxial(size_t x, size_t y) const {
  int q = (2/3) * (float)x / (float)GetTileRadius();
  int r = (-1/3) * (float)x + (float)ROOT3/3 *
                     (float)y / (float)GetTileRadius();
  return {q, r};
}

/*
 * Game::GetTileRadius
 */
size_t Game::GetTileRadius() const {
  // TODO: Determine this programatically
  return 50;
}

/*
 * Game::OnDisplayResize
 */
void Game::OnDisplayResize() {
  // Update the window's view as not to have SFML automatically stretch
  // the drawn graphics
  sf::FloatRect visibleArea = {0, 0,
                              (float)GetWindowWidth(),
                              (float)GetWindowHeight()};
  window->setView(sf::View(visibleArea));
  // Update the game map of this event
  map->OnDisplayResize();
}

/*
 * Game::InitRenderTexture
 */
void Game::InitRenderTexture() {
  renderTexture.create(50, 50);
}
