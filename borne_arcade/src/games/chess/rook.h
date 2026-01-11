#ifndef ROOK_H_
#define ROOK_H_

#include "Arduino.h"
#include "piece.h"

class rook : public piece {
  public :
	rook();
    rook(bool wh, uint8_t px, uint8_t py);
    ~rook();

    // Is move legal w/ regards to pieces
    bool canMoveTo(uint8_t nx, uint8_t ny, piece *(&board)[9][9]) override;
    
};
#endif