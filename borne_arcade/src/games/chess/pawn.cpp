#include "pawn.h"

pawn::pawn() : piece(0, false, 0, 0) {}
pawn::pawn(bool wh, uint8_t px, uint8_t py) : piece(1, wh, px, py) {}
pawn::~pawn() {}

bool pawn::canMoveTo(uint8_t nx, uint8_t ny, piece *(&b)[9][9]) {
  // Check for :
  // - Inside the board
  // - First move : can go 2 ranks up/down, if not blocked by a piece
  // - Attack on direct diagonals if not same color

  // (2*_white-1) is -1 for black pieces so points to piece 1 under, +1 for white so piece 1 over 
  uint8_t next1rank = _posY+(2*_white-1);
  uint8_t next2rank = _posY+(4*_white-2);

  // - Can't be out of the board
  if (!isInBounds(nx, ny))   return false;

  // - Attack left for both black and white
  // Checks if it's the case, if the tile is a piece, and a differently colored one (now that sounds racist)
  else if (nx==_posX-1 && ny==next1rank && b[next1rank][_posX-1]!=nullptr) {
    if (b[next1rank][_posX-1]->isWhite() != this->_white)   return true;
  }

  // - Attack right for both black and white
  // Same but X+1
  else if (nx==_posX+1 && ny==next1rank && b[next1rank][_posX+1]!=nullptr) {
    if (b[next1rank][_posX+1]->isWhite() != this->_white)   return true;
  }

  // - Move from any pawn rank
  // Checks if same file,
  //   and empty next and next selected
  //   or  empty next and empty 2nd next and 2nd next selected, and piece in its first rank
  // Same trick to determine first pawn rank
  else if (_posX==nx) {
    if      (b[next1rank][_posX]==nullptr && ny==next1rank) {
      return true;
    }
    else if (b[next1rank][_posX]==nullptr && _posY==(7-5*_white) &&
             b[next2rank][_posX]==nullptr && ny==next2rank) {
      return true;
    }
  }

  return false;
}