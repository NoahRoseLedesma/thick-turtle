//
// Created by stott on 7/31/19.
//
#include "utility.h"

/*
 * Helper function for GetTilesInRange
 * Returns the number of hexagons in range of radius n.
 * Courtesy of The On-Line Encyclopedia of Integer Sequences
 * https://oeis.org/A003215
 */
size_t HexNumbers(const size_t n) {
    return 3*n*(n+1)+1;
}
/*
 * Utility function to determine if a vector has a given element
 * Returns true if element is in container, else returns false
 */
template <typename T>
bool VectorContains(const std::vector<T> &p_search_target, const T &element) {
    auto result = std::find(p_search_target.begin(),
            p_search_target.end(),
            element);
    return result == p_search_target.end();
}
/*
 * Function that returns a drawable hexagon
 */
sf::ConvexShape generateHex(double x, double y, double r) {
    sf::ConvexShape hex;
    hex.setPointCount(6);
    hex.setPoint(0, sf::Vector2f(x-r, y));
    hex.setPoint(1, sf::Vector2f(x-(r/2), y+(r*SIN60)));
    hex.setPoint(2, sf::Vector2f(x+(r/2), y+(r*SIN60)));
    hex.setPoint(3, sf::Vector2f(x+r, y));
    hex.setPoint(4, sf::Vector2f(x+(r/2), y-(r*SIN60)));
    hex.setPoint(5, sf::Vector2f(x-(r/2), y-(r*SIN60)));

    return hex;
}
/*
 * Set of utility functions for converting from the x-y pixel plane
 * to the q-r axial plane
 */
sf::Vector2f AxialToPixel(const AxialCoordinate& p_coordinate) {
    double x = HEX_RADIUS * (1.5 * p_coordinate.q);
    double y = HEX_RADIUS * (((ROOT3 / 2) * p_coordinate.q) + (ROOT3 * p_coordinate.r));
    return sf::Vector2f(x, y);
}
sf::Vector2f AxialToPixel(const AxialCoordinate&& p_coordinate) {
    double x = HEX_RADIUS * (1.5 * p_coordinate.q);
    double y = HEX_RADIUS * (((ROOT3 / 2) * p_coordinate.q) + (ROOT3 * p_coordinate.r));
    return sf::Vector2f(x, y);
}

AxialCoordinate PixelToAxial(size_t x, size_t y) {
    double q = (2/3 * double(x)) / HEX_RADIUS;
    double r = (-1/3 * double(x) + ROOT3/3 * double(y)) / HEX_RADIUS;
    return AxialCoordinate(q, r);
}
