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
