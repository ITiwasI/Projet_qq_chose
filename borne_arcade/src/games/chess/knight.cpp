#include "knight.h"

knight::knight() : piece(0, false, 0, 0) {}
knight::knight(bool wh, uint8_t px, uint8_t py) : piece(2, wh, px, py) {}
knight::~knight() {}

bool knight::canMoveTo(uint8_t nx, uint8_t ny, piece *(&b)[9][9]) {
  // Check for :
  // - Inside the board
  // - L move
  // - Empty or oponent

  // - Can't be out of the board
  if (!isInBounds(nx, ny))   return false;

  // If night move
  if (!((nx-_posX)*(nx-_posX)+(ny-_posY)*(ny-_posY)==5)) return false; // Math condition for knight move

  // - Empty or opponent
  if (b[ny][nx]==nullptr)                      return true;
  else if (b[ny][nx]->isWhite()!=this->_white) return true;
  
  return false;
}