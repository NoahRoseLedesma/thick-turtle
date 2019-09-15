#include <random>
#include "game.h"
#include "minesweepertile.h"


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
  debugFont.loadFromFile("../bin/assets/fonts/FiraCode-Regular.ttf");

  // Yes, I am in fact this lazy
  auto LoadATexture = [] (const std::string& file_name, sf::Texture& texture) -> void {
      texture.create(200,200);
      texture.loadFromFile("../bin/assets/textures/" + file_name);
  };

  // Load in all of our textures
  LoadATexture("CoveredTile.png", this->covered);
  LoadATexture("UncoveredTile.png", this->uncovered);
  LoadATexture("FlaggedTile.png", this->flagged);
  LoadATexture("MinedTile.png", this->mined);
  LoadATexture("ErrorTexture.jpg", this->error);
  LoadATexture("One.png", this->one);
  LoadATexture("Two.png", this->two);
  LoadATexture("Three.png", this->three);
  LoadATexture("Four.png", this->four);
  LoadATexture("Five.png", this->five);
  LoadATexture("Six.png", this->six);


}

/*
 * Game::InitMap
 */
void Game::InitMap(size_t radius ) {
  /*auto DebugTileProducer = [](Map* p_map, AxialCoordinate&& coord) -> Tile* {
    return new DebugTile(p_map, coord);
  };*/

  auto MinesweeperTileProducer = [](Map* p_map, AxialCoordinate&& coord) -> Tile* {
      unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
      std::mt19937 rng(seed);
      auto tile = new MinesweeperTile(p_map, coord, rng() % 3 == 0);
      return tile;
  };

  mapRadius = radius;
  map = new Map(mapRadius, MinesweeperTileProducer, this);

  auto l_game_tiles = map->GetTilesInRange(map->GetTile(AxialCoordinate(0, 0)), radius);
  for (const auto& tile: l_game_tiles) {
      auto derived_tile = dynamic_cast<MinesweeperTile *>(tile);
      derived_tile->FindNumNearbyMines();
  }
}

/*
 * Game::InitWindow
 */
void Game::InitWindow(size_t desiredWidth, size_t desiredHeight ) {

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
    while ( window->isOpen() ) {
    sf::Event event;

    while( window->pollEvent(event) ) {
        // Pass the event to the camera
        camera->Think(event);

        switch (event.type){
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::Resized:
                // Invoke the handler for this event
                OnDisplayResize();
                break;
            case sf::Event::MouseButtonPressed:
                if(event.mouseButton.button == sf::Mouse::Left) {
                    InputController controller(this);
                    AxialCoordinate l_tile_clicked =
                          controller.GetTileClickedOn(event.mouseButton);

                    std::cout << l_tile_clicked.q << ", " << l_tile_clicked.r << " | Zoom: " << this->GetZoom() << std::endl;

                    // Only continue if the tile is in bounds
                    if (map->IsCoordinateInBounds(l_tile_clicked)) {
                        Tile* l_tile = this->map->GetTile(l_tile_clicked);
                        dynamic_cast<MinesweeperTile*>(l_tile)->Think();
                    }
                }
                break;
            default:
                break;
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
  float xCenter = GetWindowWidth() / 2.f;
  float yCenter = GetWindowHeight() / 2.f;
  // Determine the pixel offset from the centroid from the given position
  float deltaX = GetTileRadius() * (1.5 * coordinate.q);
  float deltaY = GetTileRadius() * (ROOT3/2.f * coordinate.q
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
    if (camera) return std::ceil(50.f / camera->GetCurrentZoom());
    else return 50;
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
  // Reset center
  this->map->ResetCenter();
}


void Game::InitCamera() {
    this->camera = new Camera(this->window, this->map);
}

sf::Vector2f Game::GetMapCenter() const {
    return this->map->GetCenter();
}

/*
 * Gets the texture based off a given desired texture type
 */
const sf::Texture * Game::GetTexture(TextureType desired_texture) const {
    switch (desired_texture) {
        case Covered:
            return &this->covered;
        case Uncovered:
            return &this->uncovered;
        case Flagged:
            return &this->flagged;
        case Mined:
            return &this->mined;
        case One:
            return &this->one;
        case Two:
            return &this->two;
        case Three:
            return &this->three;
        case Four:
            return &this->four;
        case Five:
            return &this->five;
        case Six:
            return &this->six;
        default:
            return &this->error;
    }
}

/*
 * This method happens in a snap
 */
void Game::Endgame() {

}

const float Game::GetZoom() {
    return this->camera->GetCurrentZoom();
}
