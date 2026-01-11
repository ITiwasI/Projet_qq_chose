#include "bishop.h"

bishop::bishop() : piece(0, false, 0, 0) {}
bishop::bishop(bool wh, uint8_t px, uint8_t py) : piece(3, wh, px, py) {}
bishop::~bishop() {}

bool bishop::canMoveTo(uint8_t nx, uint8_t ny, piece *(&b)[9][9]) {
  // Check for :
  // - Inside the board
  // - 1 loop to check all 4 diagonals, inside out, stop independtly at piece or bounds

  // - Can't be out of the board
  if (!isInBounds(nx, ny))   return false;

  // Following booleans enables exploring in respective diagonals
  bool upLeft    = true;
  bool upRight   = true;
  bool downLeft  = true;
  bool downRight = true;
  for (int delta=1;delta<7;delta++) {
    // For each diagonal :
    // - If shifted position out of the board, don't explore more
    // - If still exploring and wanted tile is matching, and empty, return true
    //                                                 , and non empty, and opponent piece, return true
    //                                                                  don't explore more for next iteration

    // Up-Left diagonal -+
    if (!isInBounds(_posX-delta, _posY+delta)) upLeft = false;
    if (upLeft) {
      if (b[_posY+delta][_posX-delta]==nullptr) {
        if (nx==_posX-delta && ny==_posY+delta) return true;
      } else {
        upLeft = false;
        if (nx==_posX-delta && ny==_posY+delta && b[ny][nx]->isWhite()!=this->_white) return true;
      }
    }

    // Up-Right diagonal ++
    if (!isInBounds(_posX+delta, _posY+delta)) upRight = false;
    if (upRight) {
      if (b[_posY+delta][_posX+delta]==nullptr) {
        if (nx==_posX+delta && ny==_posY+delta) return true;
      } else {
        upRight = false;
        if (nx==_posX+delta && ny==_posY+delta && b[ny][nx]->isWhite()!=this->_white) return true;
      }
    }

    // Down-Left diagonal --
    if (!isInBounds(_posX-delta, _posY-delta)) downLeft = false;
    if (downLeft) {
      if (b[_posY-delta][_posX-delta]==nullptr) {
        if (nx==_posX-delta && ny==_posY-delta) return true;
      } else {
        downLeft = false;
        if (nx==_posX-delta && ny==_posY-delta && b[ny][nx]->isWhite()!=this->_white) return true;
      }
    }

    // Down-Right diagonal +-
    if (!isInBounds(_posX+delta, _posY-delta)) downRight = false;
    if (downRight) {
      if (b[_posY-delta][_posX+delta]==nullptr) {
        if (nx==_posX+delta && ny==_posY-delta) return true;
      } else {
        downRight = false;
        if (nx==_posX+delta && ny==_posY-delta && b[ny][nx]->isWhite()!=this->_white) return true;
      }
    }
  }

  return false;
}