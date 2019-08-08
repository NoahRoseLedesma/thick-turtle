//
// Created by stott on 7/31/19.
//

#pragma once

#include <algorithm>
#include <vector>
#include <SFML/Graphics/ConvexShape.hpp>
#include "map.h"

// Just a couple of mathematical constants
#define SIN60 0.8660254038
#define ROOT3 1.732050808

size_t HexNumbers(const size_t n);

template <typename T>
bool VectorContains(const std::vector<T> &p_search_target, const T &element);

void generateHex(sf::ConvexShape *hex, double x, double y, double r);
