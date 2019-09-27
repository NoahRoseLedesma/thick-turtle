//
// Created by stott on 7/29/19.
//

#include "player.h"

void Player::AddPieces(const Piece *p_new_piece, const Tile *p_target_tile) {
  this->m_pieces[p_target_tile] = p_new_piece;
}

int Player::GetNumTilesOccupied() {
  return this->m_pieces.size();
}
