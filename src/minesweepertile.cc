//
// Created by stott on 9/4/19.
//

#include "minesweepertile.h"

MinesweeperTile::MinesweeperTile(const Map *const map, const AxialCoordinate &&position, bool is_mine)
    :Tile(map, position), is_mine(is_mine) {
    this->setTexture(map->GetGameObject()->GetTexture(Covered));
}

MinesweeperTile::MinesweeperTile(const Map *const map, const AxialCoordinate &position, bool is_mine)
    :Tile(map, position), is_mine(is_mine) {
    this->setTexture(map->GetGameObject()->GetTexture(Covered));
}

void MinesweeperTile::FindNumNearbyMines() {
    auto immediate_tiles = this->map->GetTilesInRange(this, 1);
    for (const auto& tile : immediate_tiles) {
        if(tile == nullptr) continue;
        auto temp = dynamic_cast<MinesweeperTile*>(tile);
        if (temp->is_mine) num_nearby_mines++;
    }
}

bool MinesweeperTile::Think() {

    // Lambda to make my life easier changing textures
    auto SetTileTexture = [this] (TextureType type) -> void {
        this->setTexture(this->map->GetGameObject()->GetTexture(type));
    };

    if (this->is_mine) {
        SetTileTexture(Mined);
        return false;
    } else {
        SetTileTexture(Uncovered);
        return true;
    }

}

