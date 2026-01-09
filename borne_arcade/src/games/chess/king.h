#ifndef KING_H_
#define KING_H_

#include "Arduino.h"
#include "piece.h"

class king : public piece {
  public :
    king(bool wh, uint8_t px, uint8_t py);
    ~king();

    // Is move legal w/ regards to pieces
    bool canMoveTo(uint8_t nx, uint8_t ny) override;
    
};
#endif