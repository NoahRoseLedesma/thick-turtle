//
// Created by stott on 7/29/19.
// Copyright 2019 Stephen Ott


#pragma once

#include "player.h"

class Piece {
 public:
    virtual void Move(const Tile& p_target_tile) = 0;
    virtual void TakeDamage(const int& damage);


 private:
    Tile m_tile;
    int m_hp;
};
