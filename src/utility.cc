//
// Created by stott on 7/31/19.
//
#include "utility.h"

#include <cmath>

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
void generateHex(sf::ConvexShape *hex, double x, double y, double r) {
    hex->setPointCount(6);
    for ( size_t i = 0; i < 6; i++ ) {
      const float angle = 3.14 * i / 3;
      hex->setPoint(i, sf::Vector2f(x + r * std::cos(angle),
                                    y + r * std::sin(angle)));
    }
    hex->setOutlineColor(sf::Color::Red);
    hex->setOutlineThickness(5);
}

/*
 * Rounds floating point Axial Coordinate Values to
 * the appropiate int values
 */
AxialCoordinate RoundAxialCoordinate(float q, float r) {
    // Algorhthm can be found at
    // https://www.redblobgames.com/grids/hexagons/#rounding

    /*First convert to cubic coordinates
     * var x = hex.q
     * var z = hex.r
     * var y = -x-z
     */
    double l_x = q, l_z = r, l_y = -l_x - l_z;

    // Round each value to nearest integer
    int rx = round(l_x);
    int ry = round(l_y);
    int rz = round(l_z);

    // Find the differences
    int dif_x = abs(rx - l_x);
    int dif_y = abs(ry - l_y);
    int dif_z = abs(rz - l_z);

    if (dif_x > dif_y && dif_x > dif_z) {
        rx = -ry-rz;
    }
    else if (dif_y > dif_z) {
        ry = -rx-rz;
    }
    else {
        rz = -rx-ry;
    }
    return AxialCoordinate(rx, rz);
}
