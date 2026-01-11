#include "piece.h"

uint8_t piece::_pieceCount = 0;
piece* piece::_pieceList[32] = { nullptr };

piece::piece() : _id(0), _white(0), _posX(0), _posY(0) {};

piece::piece(uint8_t id, bool wh, uint8_t px, uint8_t py) : _id(id), _white(wh), _posX(px), _posY(py) {
  if(_pieceCount < 32) _pieceList[_pieceCount] = this;  
  _pieceCount++;
}

piece::~piece() {
  _pieceCount--;
}

bool piece::isInBounds(uint8_t x, uint8_t y) {
  return !(x < 1 || x > 8 || y < 1 || y > 8);
}

uint8_t piece::getId() {
  return _id;
}

uint8_t piece::getPos() {
  // Bijective transform (x,y) <=> (z) : file, rank => 10f+r
  return 10*_posX + _posY;
}

bool piece::isWhite() {
  return _white;
}

void piece::setPos(uint8_t nx, uint8_t ny) {
  if(nx >= 1 && nx <= 8) _posX = nx;
  if(ny >= 1 && ny <= 8) _posY = ny;
}