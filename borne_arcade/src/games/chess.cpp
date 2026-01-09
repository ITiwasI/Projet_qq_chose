#include "chess.h"

chess::chess() : game(),
wpa1(true,  1, 2), wpa2(true,  2, 2), wpa3(true,  3, 2), wpa4(true,  4, 2),
wpa5(true,  5, 2), wpa6(true,  6, 2), wpa7(true,  7, 2), wpa8(true,  8, 2),
bpa1(false, 1, 7), bpa2(false, 2, 7), bpa3(false, 3, 7), bpa4(false, 4, 7),
bpa5(false, 5, 7), bpa6(false, 6, 7), bpa7(false, 7, 7), bpa8(false, 8, 7),
wbi1(true,  3, 1), wbi2(true,  6, 1), bbi1(false, 3, 8), bbi2(false, 6, 8),
wkn1(true,  2, 1), wkn2(true,  7, 1), bkn1(false, 2, 8), bkn2(false, 7, 8),
wro1(true,  1, 1), wro2(true,  8, 1), bro1(false, 1, 8), bro2(false, 8, 8),
wqu(true,  4, 1),  bqu(false, 4, 8),
wki(true,  5, 1),  bki(false, 5, 8)
{}
chess::~chess() {}

// Override time
void chess::init(void) {
  // Button init
  upButton.init(6);
  downButton.init(3);
  leftButton.init(2);
  rightButton.init(5);
  centerButton.init(4);

  // Suppose the serial has begun
  Serial.println("chess!");
}

bool chess::isMyTurn() {
  // If a piece exists at _sel(X,Y), verifies the color match
  bool res = false;
  if (board[_selY][_selX] != nullptr) {
    res = (board[_selY][_selX]->isWhite() == _whiteTurn);
  }
  return res;
}

bool chess::isMoveLegal() {
  return true;
}

void chess::makeTheMove() {
  // Updates the moving piece (_picked),
  // Updates the board of the movement (copy then removes og place)
  
  board[_pickedY][_pickedX]->setPos(_selX, _selY);
  board[_selY][_selX]=board[_pickedY][_pickedX];
  board[_pickedY][_pickedX]=nullptr;
}


void chess::checkButtons() {

  bool u = upButton.isPressed();
  bool d = downButton.isPressed();
  bool l = leftButton.isPressed();
  bool r = rightButton.isPressed();
  bool c = centerButton.isPressed();

  // All buttons released
  if (!u && !d && !l && !r && !c) _lastButtonState = 0;

  // If any rising edge, put last value to a different state
  else if ( _lastButtonState == 0) {
    if      (u) {_lastButtonState= 1;  _selY=constrain(_selY+1,1,8);}
    else if (d) {_lastButtonState=-1;  _selY=constrain(_selY-1,1,8);}
    else if (l) {_lastButtonState=-2;  _selX=constrain(_selX-1,1,8);}
    else if (r) {_lastButtonState= 2;  _selX=constrain(_selX+1,1,8);}
    else if (c) {_lastButtonState= 5;

      // First, turn check, then
      // If selector roaming on the board, we pick
      // Else => check for legal move, move if true, change turn

      if (isMyTurn() && !_picked) {
        _picked = true;
        _pickedX = _selX;
        _pickedY = _selY;
      } else if (isMyTurn()) {
        _picked = false;
        if (isMoveLegal()) {
          makeTheMove();
          _whiteTurn = !_whiteTurn;
        }
      }
    }
  }
}

void chess::checkButtonTimed(unsigned long deltaT) {
  unsigned long t_0 = millis();
  while (millis()-t_0 < deltaT) {
    checkButtons();
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
      // If position of the picked piece
      if (showSelector && _picked && _pickedX == nx && _pickedY == ny)
      {
        Serial.print("✜");
        didPrint = true;
      }
      // If position of the selector
      else if (showSelector && _selX == nx && _selY == ny)
      {
        if (!_picked) {Serial.print("✛"); didPrint = true;}
        else          {Serial.print("✜"); didPrint = true;}
      }
      // If picked piece can go here (null test should be useless because of isMyTurn())
      else if (showSelector && board[_pickedY][_pickedX] != nullptr)
      {
        if(_picked && board[_pickedY][_pickedX]->canMoveTo(nx, ny)) {Serial.print("⌧"); didPrint = true;}
      }
      // If piece and not anything above
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
      // If we still didn't print anything
      else if (!didPrint) Serial.print("﹘");
    }
    Serial.print("│\n");
  }
  Serial.print("└⸺⸺⸺⸺┘\n");
}

void chess::run(void) {
  //checkSerial(500);
  printBoard(true);
  //checkSerial(500);
  printBoard(false);
}