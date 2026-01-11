#include "king.h"

king::king() : piece(0, false, 0, 0) {}
king::king(bool wh, uint8_t px, uint8_t py) : piece(6, wh, px, py) {}
king::~king() {}

bool king::canMoveTo(uint8_t nx, uint8_t ny, piece *(&b)[9][9]) {
  // Check for :
  // - If nx ny in bounds,
  // - If nx ny is surrounding king
  // - If nx ny is empty or oponent

  // - If nx, ny in bounds
  if (!isInBounds(nx, ny))   return false;

  // - If nx ny is surrounding king, no need for else because of return
  if (_posX==nx && _posY==ny)          return false;     // Can't be same place
  if (nx < _posX-1 || nx > _posX+1)    return false;     // Can't be too far
  if (ny < _posY-1 || ny > _posY+1)    return false;     // Can't be too far
  
  // - Empty or opponent
  if (b[ny][nx]==nullptr)                      return true;
  else if (b[ny][nx]->isWhite()!=this->_white) return true;
  // Could have returned the condition but don't want to make my code too cryptic, just a lil

  return false; // All other cases
}