/*
 * Hexagonal Game Map
 * Created by Noah Rose Ledesma
 *
 * The game map is composed of hexagonal tiles. A tiles position within
 * the map is defined by two coordinate systems.
 *
 * Cubic Coordinate System: Every hexagon on the map lies at the intersection
 * of three lines. These lines can be denoted by three values: x, y, and z.
 * The sum of the x, y, and z components when denoting a hexagon on the map
 * will always be zero.
 *
 * Axial Coordinate System: This coordinate system is built by taking two of
 * the three values used to represent a point in the cubic coordinate system
 * and dropping the third. The third value is always implicitly known by the
 * relationship x + y + z = 0. The choice for which two axes to use is
 * arbitrary. 
 * This map will be using columns `q` as the X axis and rows `r` as the Z axis.
 */
#pragma once
#include <cstdint>
#include <vector>
#include <functional>
#include "utility.h"
#include "tile.h"
#include "game.h"

class Game;
class Tile;

// Coordinate types and associated utilities
typedef int32_t CoordComponentType;

class AxialCoordinate {
 public:
  AxialCoordinate(CoordComponentType q, CoordComponentType r);
  AxialCoordinate(const AxialCoordinate&& copy);

    AxialCoordinate(float pixel_x, float pixel_y, Game *game);

    AxialCoordinate(const AxialCoordinate& copy);

  AxialCoordinate operator+(const AxialCoordinate&& rhs) const;
  AxialCoordinate operator+(const AxialCoordinate& rhs) const;
  AxialCoordinate operator+(const AxialCoordinate* rhs) const;

  CoordComponentType q, r;
 private:
};

class CubicCoordinate;

class Map : public sf::Drawable {
 public:
  /*
   * Create a map in the shape of a hexagon with the specified radius.
   */
  explicit Map(size_t radius,
               std::function<Tile*(Map*,AxialCoordinate&&)> initilizer,
               Game* gameObject);
  ~Map();

  /*
   * Get a tile in the map from a coordinate.
   * If there is no tile at the specified coordinate, this returns nullptr.
   * If the specified coordinate is invalid, this returns nullptr.
   * Otherwise, a pointer to the tile is returned.
   */
   Tile* GetTile(const AxialCoordinate* const coord) const;
   Tile* GetTile(const AxialCoordinate& coord) const;
   Tile* GetTile(const AxialCoordinate&& coord) const;
   Tile* GetTile(const AxialCoordinate* const coord);
   Tile* GetTile(const AxialCoordinate& coord);
   Tile* GetTile(const AxialCoordinate&& coord);
  /*
   * Get an unordered list of the tiles within a radius of a given tile.
   */
   std::vector<Tile*> GetTilesInRange(const Tile* source, size_t radius) const;
  /*
   * Returns true if the specified coordinate is within the bounds of the map
   */
   bool IsCoordinateInBounds(const AxialCoordinate* const coord) const;
   bool IsCoordinateInBounds(const AxialCoordinate& coord) const;
   bool IsCoordinateInBounds(const AxialCoordinate&& coord) const;


  /*
   * Get the game object
   */
  const Game* GetGameObject() const { return game; }

  /*
   * Draw the map to the specified render target by drawing all of it's tiles
   */
  virtual void draw( sf::RenderTarget& target, sf::RenderStates states)
                      const;

  /*
   * Invoked when the display changes size
   */
  void OnDisplayResize();

  /*
   * Set the center of the map
   */
  void ShiftCenter(int32_t x, int32_t y);

  /*
   * Get the center of the map
   */
  sf::Vector2f GetCenter();
 private:
  // Represent the map using a 2D matrix
  // This approach is simple to implement but will have space overhead
  // especially in the case of maps with distant 'islands' and empty space
  // between them. In this scenerio it may be better to use a hash table.
  // This vector is indexed by AxialCoordinates
  std::vector<std::vector<Tile*>> tiles;

  // The game which this map belongs to
  Game* game;

  // The x-y pixel location of the center of the map
  sf::Vector2f center_coordinate;
};
