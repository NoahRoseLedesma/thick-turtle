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

Map::Map(size_t radius) {
    this->tiles.resize(std::floor(SCREEN_HEIGHT / (3 * radius)));
    for (double y = 0; y < SCREEN_HEIGHT + radius; y += (radius * ROOT3)) {
        double inverter = 1;
        double offset = 0;
        int n = (ROOT3/3 * y) / radius;
        this->tiles[n].resize(std::floor(SCREEN_WIDTH / (3 * radius)));
        for (double x = 0; x < SCREEN_WIDTH + radius; x += (1.5 * radius)) {
            Tile* l_new_tile = new Tile(this, PixelToAxial(x, y));
            l_new_tile->setFillColor(sf::Color::Red);
            l_new_tile->setOutlineColor(sf::Color::Cyan);
            l_new_tile->setOutlineThickness(4);

            auto coordinates = PixelToAxial(x, y);
            this->tiles[coordinates.q][coordinates.r] = l_new_tile;

            offset += (inverter * (radius * (ROOT3 / 2)));
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
    double y = HEX_RADIUS * (((ROOT3 / 2) * p_coordinate.q)
            + (ROOT3 * p_coordinate.r));
    return sf::Vector2f(x, y);
}
sf::Vector2f AxialToPixel(const AxialCoordinate&& p_coordinate) {
    double x = HEX_RADIUS * (1.5 * p_coordinate.q);
    double y = HEX_RADIUS * (((ROOT3 / 2) * p_coordinate.q)
            + (ROOT3 * p_coordinate.r));
    return sf::Vector2f(x, y);
}

AxialCoordinate PixelToAxial(size_t x, size_t y) {
    int q = static_cast<int>((2/3 * static_cast<double>(x)) / HEX_RADIUS);
    int r = static_cast<int>((-1/3 * static_cast<double>(x)
            + ROOT3/3 * static_cast<double>(y)) / HEX_RADIUS);
    return AxialCoordinate(q, r);
}


