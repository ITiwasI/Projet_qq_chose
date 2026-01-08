#include "pawn.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "king.h"
#include "queen.h"
#include "piece.h"

// In game selector
uint8_t selX = 1;
uint8_t selY = 1;
uint8_t selMoveX = 1;
uint8_t selMoveY = 1;
bool squareSelected = false;

// Static white pieces declaration
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

bool moveOk(uint8_t selMoveX, uint8_t selMoveY) {
  return true || selMoveX>2 || selMoveY>2;
}

void checkSerial(int deltaT) {
  uint32_t t_0 = millis();
  while (millis()-t_0 < deltaT) {
    if (Serial.available()>0) {
      char c = Serial.read();         // Extracts the first char
      while (Serial.available()>0) {
        Serial.read();
        delay(2);
      }
      
      switch(c) {
        case 'z': if(squareSelected) selMoveY = constrain(selMoveY+1, 1, 8);
                  else                   selY = constrain(selY+1, 1, 8);
                  break;
        case 's': if(squareSelected) selMoveY = constrain(selMoveY-1, 1, 8);
                  else                   selY = constrain(selY-1, 1, 8);
                  break;
        case 'q': if(squareSelected) selMoveX = constrain(selMoveX-1, 1, 8);
                  else                   selX = constrain(selX-1, 1, 8);
                  break;
        case 'd': if(squareSelected) selMoveX = constrain(selMoveX+1, 1, 8);
                  else                   selX = constrain(selX+1, 1, 8);
                  break;
        case ' ': if (!squareSelected) {squareSelected = true; selMoveY=selY; selMoveX=selX;}
                  else if (squareSelected && selY==selMoveY && selX==selMoveX) squareSelected = false;
                  else if (squareSelected && moveOk(selMoveX, selMoveY)) 
                  {
                    squareSelected = false;
                    board[selMoveY][selMoveX]=board[selY][selX];
                    board[selMoveY][selMoveX]->setPos(selMoveX, selMoveY);
                    board[selY][selX]=nullptr;
                    selY=selMoveY;
                    selX=selMoveX;
                  }
        default:  break;
      }
    }
  }
}

void printBoard(bool showSelector) {
  Serial.print("Board :\n┌⸺⸺⸺⸺┐\n");
                        //♙♙♙♙♙♙♙♙
                        //⌧⌧⌧⌧⛌⛌⛌⛌
  
  for (int ny = 8; ny >=1; ny--)
  {
    Serial.print("│");
    for (int nx = 1; nx <= 8; nx++)
    {
      bool didPrint = false;
      if (showSelector && squareSelected && selMoveX == nx && selMoveY == ny)
      {
        Serial.print("✜");
        didPrint = true;
      }
      else if (showSelector && selX == nx && selY == ny)
      {
        if (!squareSelected) {Serial.print("✛"); didPrint = true;}
        else                 {Serial.print("✜"); didPrint = true;}
      }
      else if (showSelector && board[selY][selX] != nullptr)
      {
        if(squareSelected && board[selY][selX]->canMoveTo(nx, ny)) {Serial.print("⌧"); didPrint = true;}
      }

      if (!didPrint && board[ny][nx]!=nullptr)
      {
        if(board[ny][nx]->isWhite())
        {
          // Yes I know, too much nested ifs
          switch(board[ny][nx]->getId())
          {
            case 1: Serial.print("♙"); break;
            case 2: Serial.print("♘"); break;
            case 3: Serial.print("♗"); break;
            case 4: Serial.print("♖"); break;
            case 5: Serial.print("♕"); break;
            case 6: Serial.print("♔"); break;
            default: break;
          }
        } else {
          switch(board[ny][nx]->getId())
          {
            case 1: Serial.print("♟"); break;
            case 2: Serial.print("♞"); break;
            case 3: Serial.print("♝"); break;
            case 4: Serial.print("♜"); break;
            case 5: Serial.print("♛"); break;
            case 6: Serial.print("♚"); break;
            default: break;
          }
        }
      }
      else if (!didPrint) Serial.print("﹘");
    }
    Serial.print("│\n");
  }
  Serial.print("└⸺⸺⸺⸺┘\n");
}

void setup() {
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  
  checkSerial(500);
  printBoard(true);
  checkSerial(500);
  printBoard(false);

}
