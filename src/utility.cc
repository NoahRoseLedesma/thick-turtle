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

size_t HexNumbers( const size_t n ) {
    return 3*n*(n+1)+1;
}
