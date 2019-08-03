//
// Created by stott on 7/29/19.
//


#pragma once

#include "player.h"
#include "tile.h"
#include "utility.h"



class Piece {
 public:
    /*
     * Construct a piece and place it on the specified tile
     */
    explicit Piece(const Tile* position);
    /*
     * Change which tile this piece is occuping
     * TODO: What is the behavior of this method if the tile is invalid
     * or the tile is already occupied?
     */
    virtual void Move(const Tile* p_target_tile);
    /*
     * Apply damage to the piece, killing it if HP drops below zero.
     */
    virtual void TakeDamage(size_t damage);
    /*
     * Gets the HP this unit should have when constructed
     */
    virtual size_t GetStartingHP() const;
    /*
     * Kill this unit and remove it from the game. It is the player's
     * reponsibility to remove the dead unit (deallocate it, etc).
     */
    virtual void Kill();
    /*
     * Returns true if this unit has been killed.
     */
    bool IsDead() const { return m_hp == 0; }
    /*
     *  Returns a vector of pointers to tiles the piece could move to
     */
    virtual std::vector<Tile *> GetAvailableMoves(const Tile *p_target_tile);
    /*
     *  Performs an attack on a piece wherein a calculation must be performed
     */
    virtual void Attack(Piece* p_target_piece) = 0;
    /*
     *  TODO: Need to implement defend function, but am unsure of what args it takes
     */
    virtual void Defend();

 protected:
    const Tile* m_tile;
    size_t m_hp;
    size_t m_movement_range;
};
