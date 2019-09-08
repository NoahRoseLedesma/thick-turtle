/*
 * Game object. Handles overarching game logic and otherwise global data.
 */
#pragma once

#include <cmath>
#include <functional>
// only for debugging purposes
#include <iostream>
#include <chrono>

#include <SFML/Graphics.hpp>

#include "inputcontroller.h"
#include "map.h"
#include "tile.h"
#include "camera.h"

class Map;
class AxialCoordinate;
class Camera;

enum TextureType {
    Covered,
    Uncovered,
    Flagged,
    Mined
};

class Game {
 public:
  Game();
  ~Game();

  /*
   * Construct a map with the given radius and make this the active game map.
   */
  void InitMap(size_t radius);
  void InitWindow(size_t desiredWidth, size_t desiredHeight);
  void InitCamera();

  size_t GetWindowHeight() const;
  size_t GetWindowWidth() const;

  sf::Vector2f GetMapCenter() const;

  /*
   * Trap the main thread into running the game loop
   */
  void Run();

  /*
   * Methods for converting between hex coordinates to world coordinates (pixel)
   */
  sf::Vector2f AxialToPixel(const AxialCoordinate& coordinate) const;
  sf::Vector2f AxialToPixel(const AxialCoordinate&& coordinate) const;

  /*
   * Gets the world size of each tile based on the current dimentions
   * of the display
   */
  size_t GetTileRadius() const;

  /*
   * Handle the resizing of the main window
   */
  void OnDisplayResize();

  /*
   * Mathematical constants
   */
  static constexpr float ROOT3 = 1.73205081;

  // Debug resources
  const sf::Font& GetDebugFont() const { return debugFont; }

  const sf::Texture * GetTexture(TextureType desired_texture) const;

 private:
  /*
   * The primary game loop. Draw to the screen and perform game logic
   */
  void Think();
  /*
   * Game map object
   */
  Map* map = nullptr;
  size_t mapRadius;

  /*
   * We use a pointer to a window because RenderWindows follows RAII.
   * Meaning that if we were to use an instance, a window could appear
   * before initilization has completed.
   */
  sf::RenderWindow* window = nullptr;

  /*
   * The camera controlling the world view
   */
  Camera* camera = nullptr;

  /*
   * A font resource which can be used for debugging purposes.
   */
  sf::Font debugFont;

  /*
   * Textures that describe the state of a tile
   */
  sf::Texture covered, uncovered, flagged, mined;
};
