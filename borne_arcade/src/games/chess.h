#ifndef CHESS_H_
#define CHESS_H_

#include "chess/pawn.h"
#include "chess/bishop.h"
#include "chess/knight.h"
#include "chess/rook.h"
#include "chess/king.h"
#include "chess/queen.h"
#include "chess/piece.h"
#include "Arduino.h"

class chess : public game {
  public :
    chess();
    ~chess();

    void init(void) override;
    void run(void) override;

    void checkSerial(int deltaT);
    void printBoard(bool showSelector); 
  protected :
    // All the pieces
    pawn   wpa1(true,  1, 2), wpa2(true,  2, 2), wpa3(true,  3, 2), wpa4(true,  4, 2);
    pawn   wpa5(true,  5, 2), wpa6(true,  6, 2), wpa7(true,  7, 2), wpa8(true,  8, 2);
    pawn   bpa1(false, 1, 7), bpa2(false, 2, 7), bpa3(false, 3, 7), bpa4(false, 4, 7);
    pawn   bpa5(false, 5, 7), bpa6(false, 6, 7), bpa7(false, 7, 7), bpa8(false, 8, 7);
    bishop wbi1(true,  3, 1), wbi2(true,  6, 1), bbi1(false, 3, 8), bbi2(false, 6, 8);
    knight wkn1(true,  2, 1), wkn2(true,  7, 1), bkn1(false, 2, 8), bkn2(false, 7, 8);
    rook   wro1(true,  1, 1), wro2(true,  8, 1), bro1(false, 1, 8), bro2(false, 8, 8);
    queen  wqu(true,  4, 1),  bqu(false, 4, 8);
    king   wki(true,  5, 1),  bki(false, 5, 8);

    // Don't wanna bother with index starting at 0,0 for pos a1
    piece *board[9][9] = {
      nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
      nullptr, &wro1,   &wkn1,   &wbi1,   &wqu,    &wki,    &wbi2,   &wkn2,   &wro2,
      nullptr, &wpa1,   &wpa2,   &wpa3,   &wpa4,   &wpa5,   &wpa6,   &wpa7,   &wpa8,
      nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
      nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
      nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
      nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
      nullptr, &bpa1,   &bpa2,   &bpa3,   &bpa4,   &bpa5,   &bpa6,   &bpa7,   &bpa8,
      nullptr, &bro1,   &bkn1,   &bbi1,   &bqu,    &bki,    &bbi2,   &bkn2,   &bro2
    };
    
    // In game selector
    uint8_t selX = 1;
    uint8_t selY = 1;

    // Piece selected
    uint8_t pickedX = 1;
    uint8_t pickedY = 1;
    
}

#endif