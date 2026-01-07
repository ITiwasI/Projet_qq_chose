#ifndef PAWN_H_
#define PAWN_H_

#include "Arduino.h"
#include "piece.h"

class pawn : public piece {
  public :
    pawn(bool wh, uint8_t px, uint8_t py);
    ~pawn();

    // Is move legal w/ regards to pieces
    bool canMoveTo(uint8_t nx, uint8_t ny) override;
    
};
#endif