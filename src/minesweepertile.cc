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

void MinesweeperTile::Think() {

    if (this->is_mine) {
        SetTileTexture(Mined);

    } else {
        switch (num_nearby_mines) {
            case 0:
                SetTileTexture(Uncovered);
                break;
            case 1:
                SetTileTexture(One);
                break;
            case 2:
                SetTileTexture(Two);
                break;
            case 3:
                SetTileTexture(Three);
                break;
            case 4:
                SetTileTexture(Four);
                break;
            case 5:
                SetTileTexture(Five);
                break;
            case 6:
                SetTileTexture(Six);
                break;
            default:
                SetTileTexture(Error);
                break;
        }
        this->RevealTilesIfBlank();
    }
}

void MinesweeperTile::RevealTilesIfBlank() {

    if (!this->map->IsCoordinateInBounds(this->position) || this->is_mine) {
        return;
    }
    auto tiles = this->map->GetTilesInRange(map->GetTile(this->position), 1);
    for (auto iter_tile : tiles) {
        if (iter_tile == nullptr) continue;

        auto l_mine_tile = dynamic_cast<MinesweeperTile*>(iter_tile);

        if (l_mine_tile->IsEmpty() && !l_mine_tile->is_mine) {
            l_mine_tile->SetTileTexture(Uncovered);
        }

        l_mine_tile->RevealTilesIfBlank();
    }
}

void MinesweeperTile::SetTileTexture(TextureType type) {
    this->setTexture(this->map->GetGameObject()->GetTexture(type));
}

