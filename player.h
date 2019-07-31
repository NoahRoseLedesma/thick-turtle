/*
 * Declarations of a player object that can interact with the game
 *
 * Created by stott on 7/29/19.
 */


#pragma once

#include <string>
#include <map>

#include "piece.h"

class PlayerInput;
class Tile;

class Player {
 public:
    virtual void HandleUserInput(const PlayerInput &p_input) = 0;
    void MovePieces(const Piece &p_target_piece, const Tile &p_target_tile);
    void AddPieces(const Piece &p_new_piece, const Tile &p_target_tile);
    int GetNumTilesOccupied();

 private:
    std::string m_name;
    std::map<Tile, Piece> m_pieces;
};


