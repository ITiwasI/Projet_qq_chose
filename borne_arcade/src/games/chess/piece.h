#ifndef PIECE_H_
#define PIECE_H_

#include "Arduino.h"

class piece {
  public :
	piece();
    piece(uint8_t id, bool wh, uint8_t px, uint8_t py);
    ~piece();
    
    virtual bool canMoveTo(uint8_t nx, uint8_t ny, piece *(&board)[9][9])=0;
    static  bool isInBounds(uint8_t x, uint8_t y);

    uint8_t getId();
    uint8_t getPos();
    bool isWhite();
    void setPos(uint8_t nx, uint8_t ny); 

  protected :
    // Id : 1-pawn  2-knight  3-bishop  4-rook  5-queen  6-king
    uint8_t   _id;
    bool      _white;
    uint8_t   _posX;      // Between 1-8
    uint8_t   _posY;      // Between 1-8

  private :
    static uint8_t _pieceCount;
    static piece* _pieceList[32];
};
#endif