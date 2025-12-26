#include "knight.h"

knight::knight(bool wh, uint8_t px, uint8_t py) : piece(2, wh, px, py) {}
knight::~knight() {}

bool knight::canMoveTo(uint8_t nx, uint8_t ny) {
  if (nx < 1 || nx > 8 || ny < 1 || ny > 8)   return false;     // Can't be out of the board
  else if ((nx-_posX)*(nx-_posX)+(ny-_posY)*(ny-_posY) == 5) return true; // Math condition for knight move
  return false;
}