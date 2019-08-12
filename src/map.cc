#include "map.h"

#include <cmath>
#include <SFML/Graphics/RenderTarget.hpp>
/*
 * Axial Coordinate
 */

AxialCoordinate::AxialCoordinate(CoordComponentType q, CoordComponentType r):
    q(q), r(r) {}

AxialCoordinate::AxialCoordinate(const AxialCoordinate&& copy):
    q(copy.q), r(copy.r) {}

AxialCoordinate::AxialCoordinate(const AxialCoordinate& copy):
    q(copy.q), r(copy.r) {}

/*
 * AxialCoordinate::operator+
 */

AxialCoordinate AxialCoordinate::operator+(const AxialCoordinate&& rhs) const {
  return {q + rhs.q, r + rhs.r};
}

AxialCoordinate AxialCoordinate::operator+(const AxialCoordinate& rhs) const {
  return {q + rhs.q, r + rhs.r};
}

AxialCoordinate AxialCoordinate::operator+(const AxialCoordinate* rhs) const {
  return {q + rhs->q, r + rhs->r};
}

/*
 * Map
 */

Map::Map(size_t radius,
         std::function<Tile*(Map*,AxialCoordinate&&)> initilizer,
         Game* game):
         tiles(radius * 2 + 1), game(game) {

  for( auto& column : tiles ) {
    column.resize(2 * radius + 1);
  }

  for (int x = -radius; x <= (signed)radius; x++) {
    for ( int y = std::max(-(signed)radius, -x-(signed)radius);
              y <= std::min((signed)radius, -x+(signed)radius);
              y++ ) {
      tiles[y + radius][x + radius] = initilizer(this, {x, y}); 
    }
  } 
}

/*
 * Map::GetTile
 */

Tile* Map::GetTile(const AxialCoordinate* const coord) const {
  return GetTile(*coord);
}

Tile* Map::GetTile(const AxialCoordinate& coord) const {
  size_t radius = tiles.size() / 2;
  return IsCoordinateInBounds(coord) ?
         tiles[coord.r + radius][coord.q + radius] : nullptr;
}

Tile* Map::GetTile(const AxialCoordinate&& coord) const {
  AxialCoordinate bind = coord;
  return GetTile(bind);
}

Tile* Map::GetTile(const AxialCoordinate* const coord)  {
  return GetTile(*coord);
}

Tile* Map::GetTile(const AxialCoordinate& coord) {
  size_t radius = tiles.size() / 2;
  return IsCoordinateInBounds(coord) ?
         tiles[coord.r + radius][coord.q + radius] : nullptr;
}

Tile* Map::GetTile(const AxialCoordinate&& coord) {
  AxialCoordinate bind = coord;
  return GetTile(bind);
}

/*
 * Map::GetTilesInRange
 */


std::vector<Tile*> Map::GetTilesInRange(const Tile* const source,
        size_t radius) const {
  std::vector<Tile*> l_tiles(HexNumbers(radius));
  auto sourcePosition = source->GetPosition();
  size_t tileVectorIndex = 0;

  for (int x = -radius; x <= (signed)radius; x++) {
    for ( int y = std::max(-(signed)radius, -x-(signed)radius);
             y <= std::min((signed)radius, -x+(signed)radius);
             y++ ) {
      l_tiles[tileVectorIndex++] = this->GetTile(*sourcePosition +
            AxialCoordinate({ .q = x , .r = y }));
    }
  }
  return l_tiles;
}


/*
 * Map::IsCoordinateInBounds
 */

bool Map::IsCoordinateInBounds(const AxialCoordinate* const coord) const {
  return IsCoordinateInBounds(*coord);
}

bool Map::IsCoordinateInBounds(const AxialCoordinate& coord) const {
  return std::abs(coord.r) <= (signed) tiles.size() / 2
      && std::abs(coord.q) <= (signed) tiles.size() / 2;
}

bool Map::IsCoordinateInBounds(const AxialCoordinate&& coord) const {
  AxialCoordinate bind = coord;
  return IsCoordinateInBounds(bind);
}

const std::vector<std::vector<Tile *>> &Map::getTiles() const {
    return tiles;
}

/*
 * Map::draw
 */
void Map::draw( sf::RenderTarget& target, sf::RenderStates ) const {
  size_t radius = tiles.size() / 2;
  for( auto* tile : GetTilesInRange( GetTile({0, 0}), radius ) ) {
    target.draw(*tile);
  }
}
