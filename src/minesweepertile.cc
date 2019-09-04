//
// Created by stott on 9/4/19.
//

#include "minesweepertile.h"

MinesweeperTile::MinesweeperTile(const Map *const map, const AxialCoordinate &&position, bool is_mine)
    :Tile(map, position), is_mine(is_mine) {

}

MinesweeperTile::MinesweeperTile(const Map *const map, const AxialCoordinate &position, bool is_mine)
    :Tile(map, position), is_mine(is_mine) {

}

