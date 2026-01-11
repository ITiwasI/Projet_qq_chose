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
#include "game.h"
#include "../components/button.h"

class chess : public game {
  public :
    chess();
    ~chess();

    void init(void) override;
    void run(void) override;

    void checkButtons(bool showAction);
    void checkButtonTimed(unsigned long deltaT);
    void printBoard(bool showSelector); 

  protected :
    // All the pieces
    pawn   wpa1, wpa2, wpa3, wpa4, wpa5, wpa6, wpa7, wpa8;
    pawn   bpa1, bpa2, bpa3, bpa4, bpa5, bpa6, bpa7, bpa8;
    bishop wbi1, wbi2, bbi1, bbi2;
    knight wkn1, wkn2, bkn1, bkn2;
    rook   wro1, wro2, bro1, bro2;
    queen  wqu,  bqu;
    king   wki,  bki;

    // Don't wanna bother with index starting at 0,0 for pos a1
    piece *_board[9][9] = {
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

    // Copy of the initial board to reset game
    piece *_boardInit[9][9] = {
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

    bool isMoveLegal();
    void makeTheMove();
    uint8_t calculatePoints(bool white);
    int8_t checkWinner();
    bool _whiteTurn = true;
    bool _gameDone = false;


    // Buttons to interact
    button upButton, downButton, leftButton, rightButton, centerButton;
    
    // Button status
    int8_t _lastButtonState = 0;

    // In game selector
    uint8_t _selX = 1;
    uint8_t _selY = 1;

    // Piece selected
    bool isMyPiece(uint8_t x, uint8_t y);
    bool _picked = false;
    uint8_t _pickedX = 1;
    uint8_t _pickedY = 1;
    
};

#endif