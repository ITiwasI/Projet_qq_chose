#include "king.h"

king::king(bool wh, uint8_t px, uint8_t py) : piece(6, wh, px, py) {}
king::~king() {}

bool king::canMoveTo(uint8_t nx, uint8_t ny) {
  if (nx < 1 || nx > 8 || ny < 1 || ny > 8)   return false;     // Can't be out of the board
  else if (_posX==nx && _posY==ny)            return false;     // Can't be same place
  else if (true) return true;
  return false;
}