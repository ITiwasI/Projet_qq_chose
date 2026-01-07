#include "bishop.h"

bishop::bishop(bool wh, uint8_t px, uint8_t py) : piece(3, wh, px, py) {}
bishop::~bishop() {}

bool bishop::canMoveTo(uint8_t nx, uint8_t ny) {
  if (nx < 1 || nx > 8 || ny < 1 || ny > 8)   return false;     // Can't be out of the board
  else if ( _posX==nx && _posY==ny )          return false;     // Can't be same place
  else if (  _posX+_posY ==   nx+ny)        return true;        // Good if in same first diagonal
  else if (7+_posX-_posY == 7+nx-ny)        return true;        // Good if in same second diagonal (+7 to only have positive values)
  return false;
}