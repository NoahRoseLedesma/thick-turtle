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
 * Constructor in the case where q and r are calculated
 * and floats from the calculation are present
 */
AxialCoordinate::AxialCoordinate(float pixel_x, float pixel_y, Game *game) {
    /*
    * var q = ( 2./3 * point.x                        ) / size
    * var r = (-1./3 * point.x  +  sqrt(3)/3 * point.y) / size
    */
    float l_x = pixel_x - game->GetWindowWidth()/2.;
    float l_y = pixel_y - game->GetWindowHeight()/2.;

    float l_q = (2./3. * l_x) / game->GetTileRadius();
    float l_r = ((-1./3. * l_x)  +  (Game::ROOT3/3. * l_y)) / game->GetTileRadius();
    /*
     * Convert to cubic coordinates bearing in mind
     * that x+y+z = 0 and letting x=q and z=r
     */
    l_x = l_q;
    float l_z = l_r;
    l_y = -l_x - l_z;

    // Round each value to nearest integer
    int rx = round(l_x);
    int ry = round(l_y);
    int rz = round(l_z);

    // Find the differences between rounded and actual value
    int dif_x = abs(rx - l_x);
    int dif_y = abs(ry - l_y);
    int dif_z = abs(rz - l_z);

    if (dif_x > dif_y && dif_x > dif_z) {
        rx = -ry-rz;
    }
    else if (dif_y > dif_z) {
        ry = -rx-rz;
    }
    else {
        rz = -rx-ry;
    }

    this->q = rx;
    this->r = rz;
}

/*
 * Map
 */

Map::Map(size_t radius,
         std::function<Tile*(Map*, AxialCoordinate&&)> initilizer,
         Game* game):
         tiles(radius * 2 + 1), game(game) {
  for ( auto& column : tiles ) {
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
void Map::draw(sf::RenderTarget& target, sf::RenderStates) const {
  size_t radius = tiles.size() / 2;
  for ( auto* tile : GetTilesInRange(GetTile({0, 0}), radius ) ) {
    target.draw(*tile);
  }
}

/*
 * Map::OnDisplayResize
 */

void Map::OnDisplayResize() {
  // Notify every tile of the display resize
  size_t radius = tiles.size() / 2;
  for ( Tile* tile : GetTilesInRange(GetTile({0, 0}), radius) ) {
    tile->OnDisplayResize();
  }
}
