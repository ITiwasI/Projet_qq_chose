#include "rook.h"

rook::rook() : piece(0, false, 0, 0) {}
rook::rook(bool wh, uint8_t px, uint8_t py) : piece(4, wh, px, py) {}
rook::~rook() {}

bool rook::canMoveTo(uint8_t nx, uint8_t ny, piece *(&b)[9][9]) {
  // Check for :
  // - Inside the board
  // - 1 loop to check all 4 directions, inside out, stop independtly at piece or bounds

  if (!isInBounds(nx, ny))   return false;

  // Following booleans enables exploring in respective directions
  bool up    = true;
  bool down  = true;
  bool left  = true;
  bool right = true;
  for (int delta=1;delta<7;delta++) {
    // For each direction :
    // - If shifted position out of the board, don't explore more
    // - If still exploring and wanted tile is matching, and empty, return true
    //                                                 , and non empty, and opponent piece, return true
    //                                                                  don't explore more for next iteration

    // Up 0+
    if (!isInBounds(_posX, _posY+delta)) up = false;
    if (up) {
      if (b[_posY+delta][_posX]==nullptr) {
        if (nx==_posX && ny==_posY+delta) return true;
      } else {
        up = false;
        if (nx==_posX && ny==_posY+delta && b[ny][nx]->isWhite()!=this->_white) return true;
      }
    }
    
    // Down 0-
    if (!isInBounds(_posX, _posY-delta)) down = false;
    if (down) {
      if (b[_posY-delta][_posX]==nullptr) {
        if (nx==_posX && ny==_posY-delta) return true;
      } else {
        down = false;
        if (nx==_posX && ny==_posY-delta && b[ny][nx]->isWhite()!=this->_white) return true;
      }
    }

    // Left -0
    if (!isInBounds(_posX-delta, _posY)) left = false;
    if (left) {
      if (b[_posY][_posX-delta]==nullptr) {
        if (nx==_posX-delta && ny==_posY) return true;
      } else {
        left = false;
        if (nx==_posX-delta && ny==_posY && b[ny][nx]->isWhite()!=this->_white) return true;
      }
    }

    // Right +0
    if (!isInBounds(_posX+delta, _posY)) right = false;
    if (right) {
      if (b[_posY][_posX+delta]==nullptr) {
        if (nx==_posX+delta && ny==_posY) return true;
      } else {
        right = false;
        if (nx==_posX+delta && ny==_posY && b[ny][nx]->isWhite()!=this->_white) return true;
      }
    }
  }

  return false;
}