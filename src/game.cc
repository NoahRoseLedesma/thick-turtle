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
  LoadATexture("SmileyFace.png", this->win);
  LoadATexture("SadFace.png", this->loss);
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

  auto MinesweeperTileProducer = [&](Map* p_map, AxialCoordinate&& coord) -> Tile* {
      return new MinesweeperTile(p_map, coord, false);
  };

  mapRadius = radius;
  number_of_mines = radius * radius;
  map = new Map(mapRadius, MinesweeperTileProducer, this);

  auto l_game_tiles = map->GetTilesInRange(map->GetTile(AxialCoordinate(0, 0)), mapRadius);

  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<> dist(0, l_game_tiles.size() - 1);


  auto l_num_mines_copy = number_of_mines;
  while (l_num_mines_copy > 0) {
      auto num = dist(rng);
      auto l_tile = dynamic_cast<MinesweeperTile *>(l_game_tiles[num]);
      if (l_tile->IsMine()) {
          continue;
      }
      else {
          l_tile->SetToMined();
          l_num_mines_copy--;
      }
  }

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
    //unsigned int number_of_non_mines = HexNumbers(mapRadius) - number_of_mines;

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
            case sf::Event::MouseButtonPressed: {
                InputController controller(this);
                AxialCoordinate l_tile_clicked =
                        controller.GetTileClickedOn(event.mouseButton);

                if (!map->IsCoordinateInBounds(l_tile_clicked)) break;

                auto l_minesweeper_tile = dynamic_cast<MinesweeperTile *>(this->map->GetTile(l_tile_clicked));

                if (event.mouseButton.button == sf::Mouse::Left &&
                    l_minesweeper_tile->IsCovered() &&
                    !l_minesweeper_tile->IsFlagged()) {

                    l_minesweeper_tile->Think();

                    if(l_minesweeper_tile->IsMine()) {
                        SetAllTiles(Loss);
                    }
                    else {
                        if (map->GetNumNonMinedTiles() <= 0) {
                            SetAllTiles(Win);
                        }
                    }

                } else if (event.mouseButton.button == sf::Mouse::Right &&
                    l_minesweeper_tile->IsCovered()) {
                    l_minesweeper_tile->ToggleFlagged();
                }
                std::cout << map->GetNumNonMinedTiles() << std::endl;
                break;
            }
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
        case Win:
            return &this->win;
        case Loss:
            return &this->loss;
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
        case Error:
        default:
            return &this->error;
    }
}

/*
 * This method happens in a snap
 * Pass in true for a win and false for a loss
 */
void Game::Endgame(bool p_is_win) {
    p_is_win ? this->SetAllTiles(Win) : this->SetAllTiles(Loss);
    window->clear();
    Think();
    window->display();
}


const float Game::GetZoom() {
    return this->camera->GetCurrentZoom();
}

/*
 * Sets all tiles on the board to the desired texture
 * Used when the game is won or lost
 */
void Game::SetAllTiles(TextureType desired_texture) {
    auto l_tiles = this->map->GetTilesInRange(this->map->GetTile({0,0}), this->mapRadius);
    for (auto tile : l_tiles) {
        dynamic_cast<MinesweeperTile*>(tile)->setTexture(this->GetTexture(desired_texture));
    }
}
