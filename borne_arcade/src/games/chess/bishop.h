#ifndef BISHOP_H_
#define BISHOP_H_

#include "Arduino.h"
#include "piece.h"

class bishop : public piece {
  public :
	bishop();
    bishop(bool wh, uint8_t px, uint8_t py);
    ~bishop();

    // Is move legal w/ regards to pieces
    bool canMoveTo(uint8_t nx, uint8_t ny, piece *(&board)[9][9]) override;
    
};
#endif