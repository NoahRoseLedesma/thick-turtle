#include "map.h"

#include <cmath>

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

Map::Map(size_t radius): tiles(radius * 2) {
  for (auto& column : tiles) {
    column.resize(radius * 2, nullptr);
  }
}

/*
 * Map::GetTile
 */

Tile* Map::GetTile( const AxialCoordinate* const coord ) {
  return IsCoordinateInBounds(coord) ? tiles[coord->r][coord->q] : nullptr;
}

Tile* Map::GetTile( const AxialCoordinate& coord ) {
  return IsCoordinateInBounds(coord) ? tiles[coord.r][coord.q] : nullptr;
}

Tile* Map::GetTile( const AxialCoordinate&& coord ) {
  return IsCoordinateInBounds(coord) ? tiles[coord.r][coord.q] : nullptr;
}

/*
 * Map::GetTilesInRange
 */

/*
 * Helper function for GetTilesInRange
 * Returns the number of hexagons in range of radius n.
 * Courtesy of The On-Line Encyclopedia of Integer Sequences
 * https://oeis.org/A003215
 */

size_t HexNumbers( const size_t n ) {
  return 3*n*(n+1)+1;
}

std::vector<Tile*> Map::GetTilesInRange(const Tile* const source, size_t radius) {
  std::vector<Tile*> tiles(HexNumbers(radius));
  auto sourcePosition = source->GetPosition();
  size_t tileVectorIndex = 0;
  for(int x = -radius; x <= (signed)radius; x++) {
    for( int y = std::max(-(signed)radius, -x-(signed)radius);
             y <= std::min((signed)radius, -x+(signed)radius);
             y++ ) {
      tiles[tileVectorIndex++] = GetTile(*sourcePosition +
            AxialCoordinate({ .q = x , .r = y }));
    }
  }
  return tiles;
}


/*
 * Map::IsCoordinateInBounds
 */

bool Map::IsCoordinateInBounds( const AxialCoordinate* const coord ) {
  return std::abs(coord->r) > tiles.size() / 2
      && std::abs(coord->q) > tiles.size() / 2;
}

bool Map::IsCoordinateInBounds( const AxialCoordinate& coord ) {
  return std::abs(coord.r) > tiles.size() / 2
      && std::abs(coord.q) > tiles.size() / 2;
}

bool Map::IsCoordinateInBounds( const AxialCoordinate&& coord ) {
  return std::abs(coord.r) > tiles.size() / 2
      && std::abs(coord.q) > tiles.size() / 2;
}

