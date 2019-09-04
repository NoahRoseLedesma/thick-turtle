//
// Created by stott on 9/4/19.
//

#ifndef THICK_TURTLE_MINESWEEPERTILE_H
#define THICK_TURTLE_MINESWEEPERTILE_H


#include "map.h"

class MinesweeperTile : public Tile {

 public:
    MinesweeperTile(const Map* const map, const AxialCoordinate&& position, bool is_mine);
    MinesweeperTile(const Map* const map, const AxialCoordinate& position, bool is_mine);

    void ToggleFlagged() { is_flagged = !is_flagged; }

 private:
    bool is_covered = true;
    bool is_flagged = false;
    bool is_mine;
};


#endif //THICK_TURTLE_MINESWEEPERTILE_H
