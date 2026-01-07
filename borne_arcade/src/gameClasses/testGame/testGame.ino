#include "pawn.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "king.h"
#include "queen.h"
#include "piece.h"

pawn pa(true, 2, 2);
bishop bi(true, 3, 3);
knight kn(true, 3, 3);
rook ro(true, 3, 3);
queen qu(true, 3, 3);
king ki(true, 3, 3);

piece *l_piece[6] = {
  &pa,
  &bi,
  &kn,
  &ro,
  &qu,
  &ki
};

void setup() {
  Serial.begin(115200);
}

void loop() {
  for (int e=0; e<6; e++) {
    Serial.println(l_piece[e]->getId());

    uint8_t posX = l_piece[e]->getPos()/10;
    uint8_t posY = l_piece[e]->getPos()%10;
    for (int ny = 8; ny >=1; ny--) {
      for (int nx = 1; nx <= 8; nx++) {
        if (posX == nx && posY == ny)           Serial.print("⯀");  // Cursor on the piece
        else if (l_piece[e]->canMoveTo(nx,ny))  Serial.print("⮽"); 
        else                                    Serial.print("☐");
      }
      Serial.println();
    }
    Serial.println();
    Serial.println();
  }
  
  delay(10000);
}
