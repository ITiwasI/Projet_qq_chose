#include "pawn.h"
#include "Arduino.h"

pawn::pawn(bool wh, uint8_t px, uint8_t py) : piece(1, wh, px, py) {}
pawn::~pawn() {}

bool pawn::canMoveTo(uint8_t nx, uint8_t ny) {
  if (nx < 1 || nx > 8 || ny < 1 || ny > 8)   return false;     // Can't be out of the board
  else if (_posX != nx)                       return false;     // Can't be different column
  else if ( _white && (_posY == 2) && (ny==3 || ny==4) ) return true;        // Test for first white move
  else if ( _white && (_posY >  2) && (ny==_posY+1) )    return true;        // test for 2nd or later move
  else if (!_white && (_posY == 7) && (ny==6 || ny==5) ) return true;        // Test for first black move
  else if (!_white && (_posY <  7) && (ny==_posY-1) )    return true;        // test for 2nd or later move
  return false;
}