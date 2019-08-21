#include "camera.h"

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

Camera::Camera(sf::RenderWindow* window): window(window) {}

void Camera::Think( sf::Event& event ) {
  if(event.type == sf::Event::EventType::MouseWheelScrolled) {
    OnZoomEvent(event.mouseWheelScroll);
  } else if(event.type == sf::Event::EventType::MouseMoved) {
    OnPanEvent(event.mouseMove);
  } else if(event.type == sf::Event::EventType::MouseButtonPressed) {
    // Right click enables panning
    if(event.mouseButton.button == sf::Mouse::Button::Right) {
      StartPanning(event.mouseButton);
    }
  } else if(event.type == sf::Event::EventType::MouseButtonReleased) {
    // Right click disables panning]
    if(event.mouseButton.button == sf::Mouse::Button::Right) {
      StopPanning();
    }
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

void Camera::OnPanEvent(sf::Event::MouseMoveEvent& event) {
  if( !currentlyPanning )
    return;

  // Calculate the change in mouse position
  sf::Vector2i deltaMousePosition(event.x, event.y);
  deltaMousePosition -= lastMousePosition;

  // Shift the view using the delta
  sf::View view = window->getView();
  view.move((float)-deltaMousePosition.x, (float)-deltaMousePosition.y);
  window->setView(view);

  // Set the last mouse position to be the mouse position in this frame
  lastMousePosition = {event.x, event.y};
}

void Camera::StartPanning(sf::Event::MouseButtonEvent& event) {
  currentlyPanning = true;
  lastMousePosition = {event.x, event.y};
}

// Currently unused. May be helpful in the future
void Camera::draw(sf::RenderTarget&, sf::RenderStates) const {}
