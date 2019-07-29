//
// Created by stott on 7/29/19.
// Copyright 2019 Stephen Ott


#ifndef PROGRAMMING_THICK_TURTLE_PLAYER_H_
#define PROGRAMMING_THICK_TURTLE_PLAYER_H_

#include <string>
#include <map>

#include "piece.h"

class PlayerInput;
class Tile;

class Player {
 public:
    virtual void HandleUserInput(const PlayerInput &p_input) = 0;
    void MovePieces(const Tile &p_target_tile);
    void AddPieces(const Tile &p_target_tile, const Piece& p_new_piece);

 private:
    std::string m_name;
    std::map<Tile, Piece> m_pieces;
};


#endif  // PROGRAMMING_THICK_TURTLE_PLAYER_H_

