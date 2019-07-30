/*
 * Heagonal Game Tile
 * Created by Noah Rose Ledesma
 *
 * Tiles are what the game map is made up of. A tile may be occupied by a game piece.
 */
#pragma once
#include "Map.h"

class Map;

class Tile {
public:
  Tile( const Map* const map, const AxialCoordinate&& position );
  Tile( const Map* const map, const AxialCorrdiante& position );

private:
  // The position of this tile in the map.
  const AxialCoordinate position;
  // The map of which this tile belongs to
  const Map* const map;
};
