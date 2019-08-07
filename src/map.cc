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

Map::Map() {

    for (double y = 0; y < SCREEN_HEIGHT + HEX_RADIUS; y += (HEX_RADIUS * ROOT3)) {
        double inverter = 1;
        double offset = 0;
        for (double x = 0; x < SCREEN_WIDTH + HEX_RADIUS; x += (1.5 * HEX_RADIUS)) {
            Tile* l_new_tile = new Tile(this, PixelToAxial(x, y));
            l_new_tile->setFillColor(sf::Color::Red);
            l_new_tile->setOutlineColor(sf::Color::Cyan);
            l_new_tile->setOutlineThickness(4);

            this->tiles[y][x] = l_new_tile;

            offset += (inverter * (HEX_RADIUS * (ROOT3 / 2)));
            inverter *= -1;
        }
    }
}

/*
 * Map::GetTile
 */

Tile* Map::GetTile(const AxialCoordinate* const coord) const {
  return IsCoordinateInBounds(coord) ? tiles[coord->r][coord->q] : nullptr;
}

Tile* Map::GetTile(const AxialCoordinate& coord) const {
  return IsCoordinateInBounds(coord) ? tiles[coord.r][coord.q] : nullptr;
}

Tile* Map::GetTile(const AxialCoordinate&& coord) const {
  return IsCoordinateInBounds(coord) ? tiles[coord.r][coord.q] : nullptr;
}

Tile* Map::GetTile(const AxialCoordinate* const coord)  {
    return IsCoordinateInBounds(coord) ? tiles[coord->r][coord->q] : nullptr;
}

Tile* Map::GetTile(const AxialCoordinate& coord) {
    return IsCoordinateInBounds(coord) ? tiles[coord.r][coord.q] : nullptr;
}

Tile* Map::GetTile(const AxialCoordinate&& coord) {
    return IsCoordinateInBounds(coord) ? tiles[coord.r][coord.q] : nullptr;
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
  return std::abs(coord->r) > (signed) tiles.size() / 2
      && std::abs(coord->q) > (signed) tiles.size() / 2;
}

bool Map::IsCoordinateInBounds(const AxialCoordinate& coord) const {
  return std::abs(coord.r) > (signed) tiles.size() / 2
      && std::abs(coord.q) > (signed) tiles.size() / 2;
}

bool Map::IsCoordinateInBounds(const AxialCoordinate&& coord) const {
  return std::abs(coord.r) > (signed) tiles.size() / 2
      && std::abs(coord.q) > (signed) tiles.size() / 2;
}

const std::vector<std::vector<Tile *>> &Map::getTiles() const {
    return tiles;
}

/* Set of utility functions for converting from the x-y pixel plane
 * to the q-r axial plane
 */
sf::Vector2f AxialToPixel(const AxialCoordinate& p_coordinate) {
    double x = HEX_RADIUS * (1.5 * p_coordinate.q);
    double y = HEX_RADIUS * (((ROOT3 / 2) * p_coordinate.q) + (ROOT3 * p_coordinate.r));
    return sf::Vector2f(x, y);
}
sf::Vector2f AxialToPixel(const AxialCoordinate&& p_coordinate) {
    double x = HEX_RADIUS * (1.5 * p_coordinate.q);
    double y = HEX_RADIUS * (((ROOT3 / 2) * p_coordinate.q) + (ROOT3 * p_coordinate.r));
    return sf::Vector2f(x, y);
}

AxialCoordinate PixelToAxial(size_t x, size_t y) {
    double q = (2/3 * double(x)) / HEX_RADIUS;
    double r = (-1/3 * double(x) + ROOT3/3 * double(y)) / HEX_RADIUS;
    return AxialCoordinate(q, r);
}


