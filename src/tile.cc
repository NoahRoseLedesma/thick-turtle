#include "tile.h"

#include <sstream>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include "game.h"

/*
 * Tile
 */
Tile::Tile(const Map* const map, const AxialCoordinate&& position):
    map(map), position(new AxialCoordinate(position)) {
    sf::Vector2f l_coord = AxialToPixel(position);
    generateHex(this, l_coord.x, l_coord.y, HEX_RADIUS);
}

Tile::Tile(const Map* const map, const AxialCoordinate& position):
    map(map), position(new AxialCoordinate(position)) {
    sf::Vector2f l_coord = AxialToPixel(position);
    generateHex(this, l_coord.x, l_coord.y, HEX_RADIUS);
}
/*
 * ~Tile
 */
Tile::~Tile() {
  delete position;
}

/*
 * Returns true if a piece could be moved to this tile
 */
bool Tile::CanBeMovedTo() const {
    /* TODO
     * A tile can be moved to if it
     * 1) Is not already occupied
     * 2) Allows for piece placement (s.t. a water tile would fail here)
     */
    return true;
}

/*
 * DebugTile
 */

DebugTile::DebugTile(const Map* const map, const AxialCoordinate&& position):
                     DebugTile(map, position) {}
DebugTile::DebugTile(const Map* const map, const AxialCoordinate& position):
                     Tile(map, position) {
  // Determine the debug text for this tile
  std::stringstream ss;
  ss << "q=" << position.q << " r=" << position.r;
  // Create a drawable representation of this text
  sf::Text text( ss.str(), map->GetGameObject()->GetDebugFont(), 4 );
  text.setOrigin(25, 25);
  // Create a rendering target to draw this text to
  sf::RenderTexture renderTexture;
  renderTexture.create(50, 50);
  // Draw the text to the render target 
  renderTexture.draw(text); 
  // Create a texture from the render target and apply it to this tile
  texture = renderTexture.getTexture();
  setTexture(&texture);
}


