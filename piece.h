//
// Created by stott on 7/29/19.
// Copyright 2019 Stephen Ott


#ifndef PROGRAMMING_THICK_TURTLE_PIECE_H_
#define PROGRAMMING_THICK_TURTLE_PIECE_H_

#include "player.h"

class Piece {
 public:
    void Move(const Tile& p_target_tile);

 private:
    Tile m_tile;
};


#endif  // PROGRAMMING_THICK_TURTLE_PIECE_H_
