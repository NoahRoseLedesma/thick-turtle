#include "camera.h"

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

Camera::Camera(sf::RenderWindow *window, Map *map) : window(window), map(map) {
  this->currentZoom = map->GetRadius() / 6.5;
}

void Camera::Think(sf::Event &event) {
  // Disable zooming for the time being. This will be done in a
  // seperate branch at a later time
  /*if(event.type == sf::Event::EventType::MouseWheelScrolled) {
    OnZoomEvent(event.mouseWheelScroll);
  }*/
  if (event.type == sf::Event::EventType::MouseMoved) {
    OnPanEvent(event.mouseMove);
  } else if (event.type == sf::Event::EventType::MouseButtonPressed) {
    // Middle mouse button enables panning
    if (event.mouseButton.button == sf::Mouse::Button::Middle) {
      StartPanning(event.mouseButton);
    }
  } else if (event.type == sf::Event::EventType::MouseButtonReleased) {
    // Middle mouse buton click disables panning
    if (event.mouseButton.button == sf::Mouse::Button::Middle) {
      StopPanning();
    }
  }
}

void Camera::OnZoomEvent(sf::Event::MouseWheelScrollEvent &event) {
  float relativeZoomFactor = (-event.delta * 0.1) / currentZoom + 1;

  // If the zoom would push out of our limits, zoom to the limit.
  if (relativeZoomFactor * currentZoom > MAX_ZOOM) {
    relativeZoomFactor = MAX_ZOOM / currentZoom;
  } else if (relativeZoomFactor * currentZoom < MIN_ZOOM) {
    relativeZoomFactor = MIN_ZOOM / currentZoom;
  }

  // It is standard to copy a view object, make adjustments, then assign the
  // view object back to the window.
  sf::View view = window->getView();
  view.zoom(relativeZoomFactor);
  window->setView(view);

  auto l_mouse_event = sf::Event::MouseMoveEvent();
  l_mouse_event.x = event.x;
  l_mouse_event.y = event.y;

  this->currentlyPanning = true;
  this->OnPanEvent(l_mouse_event);
  this->currentlyPanning = false;

  currentZoom *= relativeZoomFactor;
}

// Called when the view is reset by the display being resized.
// Zoom should be restored
void Camera::OnViewReset() {
  sf::View view = window->getView();
  view.zoom(currentZoom);
  window->setView(view);
}

void Camera::OnPanEvent(sf::Event::MouseMoveEvent &event) {
  if (!currentlyPanning)
    return;

  // Calculate the change in mouse position
  sf::Vector2i deltaMousePosition(event.x, event.y);
  deltaMousePosition -= lastMousePosition;

  // Shift the view using the delta
  sf::View view = window->getView();
  view.move((float) -deltaMousePosition.x * currentZoom, (float) -deltaMousePosition.y * currentZoom);
  window->setView(view);

  // Shift the center coordinate
  this->map->ShiftCenter(deltaMousePosition.x, deltaMousePosition.y);

  // Set the last mouse position to be the mouse position in this frame
  lastMousePosition = {event.x, event.y};
}

void Camera::StartPanning(sf::Event::MouseButtonEvent &event) {
  currentlyPanning = true;
  lastMousePosition = {event.x, event.y};
}

// Currently unused. May be helpful in the future
void Camera::draw(sf::RenderTarget &, sf::RenderStates) const {}

float Camera::GetCurrentZoom() const {
  return this->currentZoom;
}
