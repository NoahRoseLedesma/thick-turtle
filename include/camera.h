/*
 * Camera
 * Modify the world view based on player input
 */
#pragma once

#include <SFML/Window/Event.hpp>

namespace sf {
  class RenderWindow;
}

class Camera {
 public:
  Camera(sf::RenderWindow* window);

  /*
   * Process some player input event and adjust the camera
   */
  void Think( sf::Event& event );
  
  /*
   * Attempt to adjust the zoom factor of the world view
   */
  void OnZoomEvent( sf::Event::MouseWheelScrollEvent& event );

  /*
   * Reapply camera adjustments after the world view has been reset by an
   * external event. E.g. the display was resized
   */
  void OnViewReset();

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
  float currentZoom = 1.;

  /*
   * Methods
   */
};
