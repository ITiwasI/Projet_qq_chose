#include "chess.h"

//══════════════════════════════════╦═════════════════════════╦══════════════════════════════════//
//                                  ║  Class basic functions  ║                                  //
//══════════════════════════════════╩═════════════════════════╩══════════════════════════════════//


chess::chess() : game(),
wpa1(true,  1, 2), wpa2(true,  2, 2), wpa3(true,  3, 2), wpa4(true,  4, 2),
wpa5(true,  5, 2), wpa6(true,  6, 2), wpa7(true,  7, 2), wpa8(true,  8, 2),
bpa1(false, 1, 7), bpa2(false, 2, 7), bpa3(false, 3, 7), bpa4(false, 4, 7),
bpa5(false, 5, 7), bpa6(false, 6, 7), bpa7(false, 7, 7), bpa8(false, 8, 7),
wbi1(true,  3, 1), wbi2(true,  6, 1), bbi1(false, 3, 8), bbi2(false, 6, 8),
wkn1(true,  2, 1), wkn2(true,  7, 1), bkn1(false, 2, 8), bkn2(false, 7, 8),
wro1(true,  1, 1), wro2(true,  8, 1), bro1(false, 1, 8), bro2(false, 8, 8),
wqu(true,  4, 1),  bqu(false, 4, 8),
wki(true,  5, 1),  bki(false, 5, 8) {}

chess::~chess() {}


//═══════════════════════════════════════╦═══════════════╦═══════════════════════════════════════//
//                                       ║  Chess rules  ║                                       //
//═══════════════════════════════════════╩═══════════════╩═══════════════════════════════════════//


bool chess::isMyPiece(uint8_t x, uint8_t y) {
  // If a piece exists at sel(x,y) , verifies the color match
  bool res = false;
  if (_board[y][x] != nullptr) {
    res = (_board[y][x]->isWhite() == _whiteTurn);
  }
  return res;
}

bool chess::isMoveLegal() {
  /*
   Assumptions : _picked(X,Y) points to a piece 
   (isMyturn falses empty squares, _picked assures x,y to be something inside the board) 

   isMoveLegal ensures most of the chess rules :
   - can't stall a turn (piece must move)
   - calls the picked piece method with the board info to (dis)approve the move
  
  */

  // If back to the same place, don't consider it as a legal move
  if (_pickedX==_selX && _pickedY==_selY) return false;
  
  return _board[_pickedY][_pickedX]->canMoveTo(_selX, _selY, _board);
}

int8_t chess::checkWinner() {
  bool whiteKingDead = true;
  bool blackKingDead = true;
  for (int y=1;y<9;y++) {
    for (int x=1;x<9;x++) {
      if (_board[y][x]!=nullptr) if (_board[y][x]->getId()==6) {
        if (_board[y][x]->isWhite()) whiteKingDead = false;
        else                         blackKingDead = false;
      }
    }
  }
  return (whiteKingDead)? 0 : (blackKingDead)? 1 : -1;
}

uint8_t chess::calculatePoints(bool white) {
  uint8_t counter=0;
  for (int y=1;y<9;y++) {
    for (int x=1;x<9;x++) {
      if (_board[y][x]!=nullptr) if (_board[y][x]->isWhite()==white) {
        switch (_board[y][x]->getId()) {
          case 1: counter += 1; break; // Pawn
          case 2: counter += 3; break; // Knight
          case 3: counter += 3; break; // Bishop
          case 4: counter += 5; break; // Rook
          case 5: counter += 9; break; // Queen
          // King doesn't count 
        }
      }
    }
  }
  return counter;
}

void chess::makeTheMove() {
  // Updates the moving piece (_picked),
  // Updates the board of the movement (copy then removes og place)
  
  _board[_pickedY][_pickedX]->setPos(_selX, _selY);
  _board[_selY][_selX]=_board[_pickedY][_pickedX];
  _board[_pickedY][_pickedX]=nullptr;
}


//═══════════════════════════════════╦══════════════════════╦════════════════════════════════════//
//                                   ║  Player interaction  ║                                    //
//═══════════════════════════════════╩══════════════════════╩════════════════════════════════════//


void chess::printBoard(bool showSelector) {
  if(_whiteTurn) Serial.print("White's turn - Points : W=");
  else           Serial.print("Black's turn - Points : W=");

  Serial.print(calculatePoints(true));
  Serial.print(" B=");
  Serial.println(calculatePoints(false));

  for (int ny = 8; ny >=1; ny--) {
    Serial.print("│");
    for (int nx = 1; nx <= 8; nx++) {
      bool didPrint = false;
      // If position of the picked piece
      if (showSelector && _picked && _pickedX == nx && _pickedY == ny) {
        Serial.print("✜");
        didPrint = true;
      }
      // If position of the selector
      else if (showSelector && _selX == nx && _selY == ny) {
        if (!_picked) {Serial.print("✛"); didPrint = true;}
        else          {Serial.print("✜"); didPrint = true;}
      }
      // If picked piece can go here (null test should be useless because of isMyTurn())
      else if (showSelector && _board[_pickedY][_pickedX] != nullptr) {
        if(_picked && _board[_pickedY][_pickedX]->canMoveTo(nx, ny, _board)) {
          Serial.print("⌧"); didPrint = true;
        }
      }
      // If piece and not anything above
      if (!didPrint && _board[ny][nx]!=nullptr) {
        if(_board[ny][nx]->isWhite()) {
          // Yes I know, too much nested ifs
          switch(_board[ny][nx]->getId()) {
            case 1: Serial.print("♙"); break;
            case 2: Serial.print("♘"); break;
            case 3: Serial.print("♗"); break;
            case 4: Serial.print("♖"); break;
            case 5: Serial.print("♕"); break;
            case 6: Serial.print("♔"); break;
            default: break;
          }
        } else {
          switch(_board[ny][nx]->getId()) {
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

void chess::checkButtons(bool showAction) {

  bool u = upButton.isPressed();
  bool d = downButton.isPressed();
  bool l = leftButton.isPressed();
  bool r = rightButton.isPressed();
  bool c = centerButton.isPressed();

  // All buttons released
  if (!u && !d && !l && !r && !c) _lastButtonState = 0;

  // If any rising edge, put last value to a different state
  else if ( _lastButtonState == 0) {
    if      (u && !_gameDone) {_lastButtonState= 1;  _selY=constrain(_selY+1,1,8);}
    else if (d && !_gameDone) {_lastButtonState=-1;  _selY=constrain(_selY-1,1,8);}
    else if (l && !_gameDone) {_lastButtonState=-2;  _selX=constrain(_selX-1,1,8);}
    else if (r && !_gameDone) {_lastButtonState= 2;  _selX=constrain(_selX+1,1,8);}
    else if (c) {_lastButtonState= 5;

      if (!_gameDone) {
        // First, turn check, then
        // If selector roaming on the board, we pick
        // Else => check for legal move, move if true, change turn

        if (isMyPiece(_selX, _selY) && !_picked) {
          _picked = true;
          _pickedX = _selX;
          _pickedY = _selY;
        } else if (isMyPiece(_pickedX, _pickedY) && _picked) {
          _picked = false;
          if (isMoveLegal()) {
            makeTheMove();
            _whiteTurn = !_whiteTurn;
          }
        }
      } else {
        // Places back the pointers, resets internal piece position
        for (int y=1;y<9;y++) {
          for (int x=1;x<9;x++) {
            _board[y][x] = _boardInit[y][x];

            if (_board[y][x]!=nullptr) _board[y][x]->setPos(x,y);
          }
        }
        _gameDone = false;
        _whiteTurn = true;
        _selX = 1;
        _selY = 1;
        _picked = false;
      }
    }
    // If anything changed, display board
    if (showAction && (u || d || l || r || c)) {
      printBoard(true);
      int8_t gameRes = checkWinner();
      if (gameRes != -1) {
        if (gameRes == 1) {
          Serial.print("\nWhite won !\n\nClick select to play again.");
        } else {
          Serial.print("\nBlack won !\n\nClick select to play again.");
        }
        _gameDone = true;
      }
    }
  }
  // Avoids potential contact bounce
  delay(10);
}

void chess::checkButtonTimed(unsigned long deltaT) {
  unsigned long t_0 = millis();
  while (millis()-t_0 < deltaT) {
    checkButtons(false);
  }
}


//══════════════════════════════╦═════════════════════════════════╦══════════════════════════════//
//                              ║  Main functions for aplication  ║                              //
//══════════════════════════════╩═════════════════════════════════╩══════════════════════════════//


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
  printBoard(true);
}

void chess::run(void) {
  /*
  checkButtonTimed(500);
  printBoard(true);
  checkButtonTimed(500);
  printBoard(false);
  */
  checkButtons(true);
}