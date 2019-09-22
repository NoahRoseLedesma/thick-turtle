//
// Created by stott on 9/4/19.
//

#include "minesweepertile.h"

MinesweeperTile::MinesweeperTile(Map* map, const AxialCoordinate &&position, bool is_mine)
    :Tile(map, position), is_mine(is_mine), map(map) {
    this->setTexture(map->GetGameObject()->GetTexture(Covered));
}

MinesweeperTile::MinesweeperTile(Map * map, const AxialCoordinate &position, bool is_mine)
    :Tile(map, position), is_mine(is_mine), map(map) {
    this->setTexture(map->GetGameObject()->GetTexture(Covered));
}

void MinesweeperTile::FindNumNearbyMines() {
    auto immediate_tiles = this->map->GetTilesInRange(this, 1);
    for (const auto& tile : immediate_tiles) {
        if(tile == nullptr) continue;
        if (dynamic_cast<MinesweeperTile*>(tile)->is_mine){
            dynamic_cast<MinesweeperTile*>(tile)->setFillColor(sf::Color::Yellow);
            num_nearby_mines++;
        }
    }
}

void MinesweeperTile::Think() {
    if (this->is_mine) {
        is_covered = false;
        SetTileTexture(Mined);
    }
    else if (!map->IsCoordinateInBounds(this->position)) {
        return;
    } else {
        map->DecrementNumNonMinedTiles();
        has_been_visited = true;
        is_covered = false;
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

        if (iter_tile == nullptr || l_tile->has_been_visited || this == l_tile) continue;

        l_tile->has_been_visited = true;
        l_tile->setFillColor(sf::Color::Red);

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

void MinesweeperTile::ToggleFlagged() {
    is_flagged = !is_flagged;
    is_flagged ? SetTileTexture(Flagged) : SetTileTexture(Covered);
}

