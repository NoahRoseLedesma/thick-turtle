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

  // a tile can be moved to if the coordinate is in bounds,
  // is not occupied, and can be moved to
  bool l_is_in_bounds = p_target_tile->GetMap()
          ->IsCoordinateInBounds(p_target_tile->GetPosition());
  if ( l_is_in_bounds && p_target_tile->CanBeMovedTo() ) {
      return;
  }

  m_tile = p_target_tile;
}

void Piece::TakeDamage(size_t damage) {
  if ( IsDead() ) {
    // TODO: If this unit is dead and we apply damage to it,
    // we should log this as a non-critical error.
    return;
  }

  if ( damage >= m_hp ) {
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

std::vector<Tile *> Piece::GetAvailableMoves(const Tile *p_target_tile) {
    std::vector<Tile*> l_available_moves = p_target_tile->GetMap()
            ->GetTilesInRange(p_target_tile,
                    this->m_movement_range);

    // lambda which checks if a tile is valid to move to
    auto filter = [&] (Tile* cur_tile) -> bool {
        return !(cur_tile->CanBeMovedTo() &&
            cur_tile->GetMap()->IsCoordinateInBounds(cur_tile->GetPosition()));
    };
    // removes all values that satisfy the lambda

    std::remove_if(l_available_moves.begin(), l_available_moves.end(), filter);
    return l_available_moves;
}

