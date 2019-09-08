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

    // Returns false if game is over;
    bool Think();

    void ToggleFlagged() { is_flagged = !is_flagged; }
    void FindNumNearbyMines();
    // Return false if the tile is mined
    bool GetIsMine() { return is_mine; }
    unsigned int GetNumNearbyTiles() { return num_nearby_mines; }

 private:
    bool is_covered = true;
    bool is_flagged = false;
    bool is_mine;
    unsigned int num_nearby_mines = 0;
};


#endif //THICK_TURTLE_MINESWEEPERTILE_H
