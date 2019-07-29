//
// Created by stott on 7/29/19.
// Copyright 2019 Stephen Ott

#include "player.h"

void Player::MovePieces(const Tile &p_target_tile) {
}

void Player::AddPieces(const Tile &p_target_tile, const Piece &p_new_piece) {
    this->m_pieces[p_target_tile] = p_new_piece;
}
