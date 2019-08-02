/*
 * Hexagonal Game Tile
 * Created by Noah Rose Ledesma
 *
 * Tiles are what the game map is made up of. A tile may be occupied by a game piece.
 */
#pragma once
#include "map.h"

class Map;
class AxialCoordinate;

class Tile {
 public:
  Tile( const Map* const map, const AxialCoordinate&& position );
  Tile( const Map* const map, const AxialCoordinate& position );
  virtual ~Tile();

  /*
   * Gets the position of the tile within the map
   */
  const AxialCoordinate* GetPosition() const { return position; };
  const AxialCoordinate* GetPosition() { return position; };
  /*
   * Gets the pointer to the map
   */
  const Map* GetMap() const { return this->map; };
  const Map* GetMap() { return this->map; };
  /*
   * Returns the number of movement points this tile de/buffs from the piece
   * which occupies it.
   */
  virtual int GetMovementModifier() = 0;
 protected:
  // The map of which this tile belongs to
  const Map* const map;
  // The position of this tile in the map.
  const AxialCoordinate* position;
};

class DebugTile : public Tile {
 public:
  DebugTile( const Map* const map, const AxialCoordinate&& position );
  DebugTile( const Map* const map, const AxialCoordinate& position );

  int GetMovementModifier() override { return movementBonus; }

protected:
  const static int movementBonus = 4;
};
