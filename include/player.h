/*
 * Declarations of a player object that can interact with the game
 *
 * Created by stott on 7/29/19.
 */


#pragma once

#include <string>
#include <map>
#include <vector>

#include "piece.h"
#include "tile.h"

class PlayerInput;

class Piece;

class Tile;

class Player {
 public:
  virtual void HandleUserInput(const PlayerInput &p_input) = 0;

  void AddPieces(const Piece *p_new_piece,
                 const Tile *p_target_tile);

  int GetNumTilesOccupied();

 private:
  std::string m_name;
  std::map<const Tile *, const Piece *> m_pieces;
  std::vector<const Tile *> m_controlled_tiles;
};


