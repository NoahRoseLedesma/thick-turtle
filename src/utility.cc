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
