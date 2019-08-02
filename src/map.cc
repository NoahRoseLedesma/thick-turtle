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


std::vector<Tile*> Map::GetTilesInRange(const Tile* const source, size_t radius) const {
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

