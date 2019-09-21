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
        if (dynamic_cast<MinesweeperTile*>(tile)->is_mine){
            num_nearby_mines++;
        }
    }
}

void MinesweeperTile::Think() {

    if (this->is_mine) {
        SetTileTexture(Mined);
    }
    else if (!map->IsCoordinateInBounds(this->position)) {
        return;
    } else {

        switch (num_nearby_mines) {
            case 0:
                SetTileTexture(Uncovered);
                this->RevealTilesIfBlank();
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

    }
}

void MinesweeperTile::RevealTilesIfBlank() {
    MinesweeperTile* l_tile;
    auto tiles = this->map->GetTilesInRange(map->GetTile(this->position), 1);
    for (auto iter_tile : tiles) {
        l_tile = dynamic_cast<MinesweeperTile*>(iter_tile);

        if (iter_tile == nullptr || l_tile->has_been_visited) continue;

        l_tile->has_been_visited = true;

        if (l_tile->num_nearby_mines == 0) {
            this->SetTileTexture(Uncovered);
            l_tile->RevealTilesIfBlank();
        }
        l_tile->Think();

    }
}

void MinesweeperTile::SetTileTexture(TextureType type) {
    this->setTexture(this->map->GetGameObject()->GetTexture(type));
}

