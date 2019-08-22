#include "game.h"


/*
 * Game Object
 */

/*
 * Game::~Game
 */
Game::~Game() {
  if (map)
    delete map;
  if (window) {
    if (window->isOpen()) {
      window->close();
    }
    delete window;
  }
  if(camera)
    delete camera;
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
void Game::InitMap(size_t radius ) {
  auto DebugTileProducer = [](Map* map, AxialCoordinate&& coord) -> Tile* {
    return new DebugTile(map, coord);
  };

  mapRadius = radius;
  map = new Map(mapRadius, DebugTileProducer, this);
}

/*
 * Game::InitWindow
 */
void Game::InitWindow(size_t desiredWidth, size_t desiredHeight ) {
  window = new sf::RenderWindow(sf::VideoMode(desiredWidth, desiredHeight),
                                "Thick Turtle");
  camera = new Camera(window);
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
  while ( window->isOpen() ) {
    sf::Event event;

    while( window->pollEvent(event) ) {
      // Pass the event to the camera
      camera->Think(event);

      if( event.type == sf::Event::Closed ) {
        window->close();
      } else if ( event.type == sf::Event::Resized ) {
        // Invoke the handler for this event
        OnDisplayResize();
      } else if (event.type == sf::Event::MouseButtonPressed) {
          InputController controller(this);
          AxialCoordinate l_tile_clicked =
                  controller.GetTileClickedOn(event.mouseButton);
          this->map->GetTile(l_tile_clicked)->setFillColor(sf::Color::Yellow);
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
  window->draw(*camera);
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

/*
 * Game::GetTileRadius
 */
size_t Game::GetTileRadius() const {
  // TODO(Noah): Determine this programatically
  return 50;
}

/*
 * Game::OnDisplayResize
 */
void Game::OnDisplayResize() {
  // Update the window's view as not to have SFML automatically stretch
  // the drawn graphics
  sf::FloatRect visibleArea = {0, 0,
                               static_cast<float>(GetWindowWidth()),
                               static_cast<float>(GetWindowHeight())};
  window->setView(sf::View(visibleArea));
  // Update the game map of this event
  map->OnDisplayResize();
  // Reapply camera adjustments
  camera->OnViewReset();
}

/*
 * Game::InitRenderTexture
 */
void Game::InitRenderTexture() {
  renderTexture.create(50, 50);
}
