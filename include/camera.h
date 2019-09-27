/*
 * Camera
 * Modify the world view based on player input
 */
#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "map.h"

class Map;

namespace sf {
  class RenderWindow;
}

class Camera : public sf::Drawable {
 public:
  Camera(sf::RenderWindow *window, Map *map);

  /*
   * Process some player input event and adjust the camera
   */
  void Think( sf::Event& event );

  /*
   * Reapply camera adjustments after the world view has been reset by an
   * external event. E.g. the display was resized
   */
  void OnViewReset();

  /*
   * Draws camera related components
   */
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states)
                    const override;

  /*
   * Returns the current zoom
   */
  float GetCurrentZoom() const;

 private:
  /*
   * Configuration constants
   */
  static constexpr float MAX_ZOOM = 2.;
  static constexpr float MIN_ZOOM = 1.;

  /*
   * Data members
   */
  sf::RenderWindow* window;
  // The current zoom factor relative to the zoom factor when the camera was
  // initilized. This should be relative to the native zoom of the view.
  float currentZoom;

  // Enabled when the view is panning
  bool currentlyPanning = false;

  // The map of the game
  Map* map;

  // The last position of the mouse
  sf::Vector2i lastMousePosition;

  /*
   * Methods
   */
  
  /*
   * Attempt to adjust the zoom factor of the world view
   */
  void OnZoomEvent( sf::Event::MouseWheelScrollEvent& event );

  /*
   * Enable/Disable panning
   */
  void StartPanning(sf::Event::MouseButtonEvent& event);
  void StopPanning() { currentlyPanning = false; }

  /*
   * Process a mouse movement event to pan the view if panning is enabled
   */
  void OnPanEvent(sf::Event::MouseMoveEvent& event);
};
