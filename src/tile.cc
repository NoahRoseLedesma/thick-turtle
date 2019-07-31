#include "tile.h"

/*
 * Tile
 */

Tile::Tile( const Map* const map, const AxialCoordinate&& position ):
    map(map), position(new AxialCoordinate(position)) {}

Tile::Tile( const Map* const map, const AxialCoordinate& position ):
    map(map), position(new AxialCoordinate(position)) {}

/*
 * ~Tile
 */

Tile::~Tile() {
  delete position;
}

/*
 * DebugTile
 */
DebugTile::DebugTile( const Map* const map, const AxialCoordinate&& position ):
  Tile(map, position) {}
DebugTile::DebugTile( const Map* const map, const AxialCoordinate& position ):
  Tile(map, position) {}


