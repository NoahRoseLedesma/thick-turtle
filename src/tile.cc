#include "tile.h"

/*
 * Tile
 */
Tile::Tile(const Map* const map, const AxialCoordinate&& position):
    map(map), position(new AxialCoordinate(position)) {
    double x = HEX_RADIUS * (1.5 * position.q);
    double y = HEX_RADIUS * (((ROOT3 / 2) * position.q) + (ROOT3 * position.r));
    this->setPointCount(6);
    this->setPoint(0, sf::Vector2f(x-HEX_RADIUS, y));
    this->setPoint(1, sf::Vector2f(x-(HEX_RADIUS/2), y+(HEX_RADIUS*SIN60)));
    this->setPoint(2, sf::Vector2f(x+(HEX_RADIUS/2), y+(HEX_RADIUS*SIN60)));
    this->setPoint(3, sf::Vector2f(x+HEX_RADIUS, y));
    this->setPoint(4, sf::Vector2f(x+(HEX_RADIUS/2), y-(HEX_RADIUS*SIN60)));
    this->setPoint(5, sf::Vector2f(x-(HEX_RADIUS/2), y-(HEX_RADIUS*SIN60)));
}

Tile::Tile(const Map* const map, const AxialCoordinate& position):
    map(map), position(new AxialCoordinate(position)) {
    double x = HEX_RADIUS * (1.5 * position.q);
    double y = HEX_RADIUS * (((ROOT3 / 2) * position.q) + (ROOT3 * position.r));
    this->setPointCount(6);
    this->setPoint(0, sf::Vector2f(x-HEX_RADIUS, y));
    this->setPoint(1, sf::Vector2f(x-(HEX_RADIUS/2), y+(HEX_RADIUS*SIN60)));
    this->setPoint(2, sf::Vector2f(x+(HEX_RADIUS/2), y+(HEX_RADIUS*SIN60)));
    this->setPoint(3, sf::Vector2f(x+HEX_RADIUS, y));
    this->setPoint(4, sf::Vector2f(x+(HEX_RADIUS/2), y-(HEX_RADIUS*SIN60)));
    this->setPoint(5, sf::Vector2f(x-(HEX_RADIUS/2), y-(HEX_RADIUS*SIN60)));
}

/*
 * ~Tile
 */
Tile::~Tile() {
  delete position;
}

/*
 * Returns true if a piece could be moved to this tile
 */
bool Tile::CanBeMovedTo() const {
    /* TODO
     * A tile can be moved to if it
     * 1) Is not already occupied
     * 2) Allows for piece placement (s.t. a water tile would fail here)
     */
    return true;
}

/*
 * DebugTile
 */
DebugTile::DebugTile(const Map* const map, const AxialCoordinate&& position):
  Tile(map, position) {}
DebugTile::DebugTile(const Map* const map, const AxialCoordinate& position):
  Tile(map, position) {}


