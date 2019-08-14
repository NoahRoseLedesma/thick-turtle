/*
 * Game object. Handles overarching game logic and otherwise global data.
 */
#pragma once

#include <SFML/Graphics.hpp>

class Map;
class AxialCoordinate;

class Game {
 public:
  Game();
  ~Game();

  /*
   * Construct a map with the given radius and make this the active game map.
   */
  void InitMap( size_t radius );
  void InitWindow( size_t desiredWidth, size_t desiredHeight );

  size_t GetWindowHeight() const;
  size_t GetWindowWidth() const;

  /*
   * Trap the main thread into running the game loop
   */
  void Run();

  /*
   * Methods for converting between hex coordinates to world coordinates (pixel)
   */
  sf::Vector2f AxialToPixel(const AxialCoordinate& coordinate) const;
  sf::Vector2f AxialToPixel(const AxialCoordinate&& coordinate) const;
  AxialCoordinate PixelToAxial(size_t x, size_t y) const;

  /*
   * Gets the world size of each tile based on the current dimentions
   * of the display
   */
  size_t GetTileRadius() const;

  /*
   * Handle the resizing of the main window
   */
  void OnDisplayResize();

  // Debug resources
  const sf::Font& GetDebugFont() const { return debugFont; }
  void InitRenderTexture();
  sf::RenderTexture& GetRenderTexture() const { return renderTexture; }

 private:
  /*
   * The primary game loop. Draw to the screen and perform game logic
   */
  void Think();
  
  /*
   * Game map object
   */
  Map* map;
  size_t mapRadius;

  /*
   * We use a pointer to a window because RenderWindows follows RAII.
   * Meaning that if we were to use an instance, a window could appear
   * before initilization has completed.
   */
  sf::RenderWindow* window;

  /*
   * Mathematical constants
   */
  static constexpr float ROOT3 = 1.73205081;

  /*
   * A font resource which can be used for debugging purposes.
   */
  sf::Font debugFont;

  /*
   * A shared render texture resource used for debugging purposes.
   */
  mutable sf::RenderTexture renderTexture;
};
