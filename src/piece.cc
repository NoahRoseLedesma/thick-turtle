//
// Created by stott on 7/29/19.
//

#include "piece.h"

Piece::Piece(const Tile* position) {
  Move(position);
  m_hp = GetStartingHP();
}

void Piece::Move(const Tile* p_target_tile) {
  // TODO: Notify the tile we are currently on that we are leaving
  // and notify the tile we have landed on that we have arrived

  /* A tile is valid to move to if
   * 1) It is in bounds
   * 2) It is not occupied by another piece
   * 3) It is within the movement range of the piece
   * TODO: methods for the above three conditions
   * An invalid tile should produce a non-fatal error.
   * i.e if( !Valid() ) return;
   */


  m_tile = p_target_tile;
}

void Piece::TakeDamage(size_t damage) {
  if( IsDead() ) {
    // TODO: If this unit is dead and we apply damage to it, we should log this as
    // a non-critical error.
    return;
  }

  if( damage >= m_hp ) {
    Kill();
    return;
  }

  m_hp -= damage;
}

// Really should be purely virtual, however I want to use this in the default
// constructor for all pieces.
size_t Piece::GetStartingHP() const {
  return 0;
}

void Piece::Kill() {
  m_hp = 0;
}

std::vector<const Tile *> Piece::GetAvailableMoves(const Tile *p_tartget_tile) {
    auto l_available_moves = p_tartget_tile->GetMap()->GetTilesInRange(p_tartget_tile, this->m_movement_range);
}

