#include "king.h"

king::king(bool wh, uint8_t px, uint8_t py) : piece(6, wh, px, py) {}
king::~king() {}

bool king::canMoveTo(uint8_t nx, uint8_t ny) {
  if (nx < 1 || nx > 8 || ny < 1 || ny > 8)   return false;     // Can't be out of the board
  else if (_posX==nx && _posY==ny)            return false;     // Can't be same place
  else if (nx < _posX-1 || nx > _posX+1)    return false;     // Can't be too far
  else if (ny < _posY-1 || ny > _posY+1)    return false;     // Can't be too far
  return true;  // Should be good now
}