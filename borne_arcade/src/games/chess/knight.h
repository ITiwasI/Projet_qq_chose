#ifndef KNIGHT_H_
#define KNIGHT_H_

#include "Arduino.h"
#include "piece.h"

class knight : public piece {
  public :
	knight();
    knight(bool wh, uint8_t px, uint8_t py);
    ~knight();

    // Is move legal w/ regards to pieces
    bool canMoveTo(uint8_t nx, uint8_t ny, piece *(&board)[9][9]) override;
    
};
#endif