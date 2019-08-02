#include "tile.h"

/*
 * Tile
 */
Tile::Tile(const Map* const map, const AxialCoordinate&& position):
    map(map), position(new AxialCoordinate(position)) {}

Tile::Tile(const Map* const map, const AxialCoordinate& position):
    map(map), position(new AxialCoordinate(position)) {}

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
  Tile(map, position) {}
DebugTile::DebugTile(const Map* const map, const AxialCoordinate& position):
  Tile(map, position) {}


