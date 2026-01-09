#ifndef QUEEN_H_
#define QUEEN_H_

#include "Arduino.h"
#include "piece.h"

class queen : public piece {
  public :
    queen(bool wh, uint8_t px, uint8_t py);
    ~queen();

    // Is move legal w/ regards to pieces
    bool canMoveTo(uint8_t nx, uint8_t ny) override;
    
};
#endif