#include "camera.h"

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

Camera::Camera(sf::RenderWindow* window): window(window) {}

void Camera::Think( sf::Event& event ) {
  if(event.type == sf::Event::EventType::MouseWheelScrolled) {
    OnZoomEvent(event.mouseWheelScroll);
  }
}

void Camera::OnZoomEvent( sf::Event::MouseWheelScrollEvent& event ) {
  float relativeZoomFactor = (-event.delta * 0.1) / currentZoom + 1;
  
  // If the zoom would push out of our limits, zoom to the limit.
  if( relativeZoomFactor * currentZoom > MAX_ZOOM ) {
    relativeZoomFactor = MAX_ZOOM / currentZoom;
  } else if ( relativeZoomFactor * currentZoom < MIN_ZOOM ) {
    relativeZoomFactor = MIN_ZOOM / currentZoom;
  }
  
  // It is standard to copy a view object, make adjustments, then assign the
  // view object back to the window.
  sf::View view = window->getView();
  view.zoom(relativeZoomFactor);
  window->setView(view);

  currentZoom *= relativeZoomFactor;
}

// Called when the view is reset by the display being resized.
// Zoom should be restored
void Camera::OnViewReset() {
  sf::View view = window->getView();
  view.zoom(currentZoom);
  window->setView(view);
}
