//
// Created by stott on 9/4/19.
//

#ifndef THICK_TURTLE_MINESWEEPERTILE_H
#define THICK_TURTLE_MINESWEEPERTILE_H


#include "map.h"

class MinesweeperTile : public Tile {

 public:
    MinesweeperTile(Map* map, const AxialCoordinate&& position, bool is_mine);
    MinesweeperTile(Map* map, const AxialCoordinate& position, bool is_mine);

    void Think();

    void ToggleFlagged();
    void FindNumNearbyMines();
    void RevealTilesIfBlank();

    inline bool IsMine() { return is_mine; }
    inline bool IsEmpty() { return num_nearby_mines == 0; }
    inline bool IsFlagged() { return is_flagged; }
    inline bool IsCovered() { return is_covered; }
    inline bool HasBeenVisited() { return has_been_visited; }
    inline unsigned int GetNumNearbyTiles() { return num_nearby_mines; }

 protected:
    void SetTileTexture(TextureType type);

 private:
    bool is_covered = true;
    bool is_flagged = false;
    bool is_mine;
    bool has_been_visited = false;
    unsigned int num_nearby_mines = 0;
    Map* map;
};


#endif //THICK_TURTLE_MINESWEEPERTILE_H
