/*
 * Game object. Handles overarching game logic and otherwise global data.
 */
#pragma once

#include <SFML/Graphics.hpp>

class Map;

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

  // We use a pointer to a window because RenderWindows follows RAII.
  // Meaning that if we were to use an instance, a window could appear
  // before initilization has completed.
  sf::RenderWindow* window;

  /*
   * A font resource which can be used for debugging purposes.
   */
  sf::Font debugFont;
  /*
   * A shared render texture resource used for debugging purposes.
   */
  mutable sf::RenderTexture renderTexture;
};
