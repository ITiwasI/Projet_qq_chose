#include "chess.h"

chess::chess() : game() {}
chess::~chess() : game() {}

// Override time
void chess::init(void) {
  // Suppose the serial has begun
  Serial.println("chess!");
}
void chess::run(void) {
  checkSerial(500);
  printBoard(true);
  checkSerial(500);
  printBoard(false);
}

void chess::checkSerial(int deltaT) {
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

void chess::printBoard(bool showSelector) {
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