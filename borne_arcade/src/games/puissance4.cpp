#include "puissance4.hpp"
#include "puissance4/grid.hpp"

puissance4::puissance4() : game() {
}
puissance4::~puissance4() {
}

void puissance4::init() {
    rightButton.init(5);
    centerButton.init(4);

}


void puissance4::run(void) {
  int push = 1;
  char CurrentPlayer = 'A';
  Grid grid4;
  grid4.DisplayGrid();

  while ((grid4.isGridFull() != 1) and (grid4.isWinner() == '/')) 
    {
      Serial.print("Joueur Actuel: ");
      Serial.println(CurrentPlayer);
      
      push = 1;
      Serial.print("Colonne Actuelle: ");
      Serial.println(push);
      
      while (!centerButton.isPressed())
      {
        if (rightButton.isPressed()) 
        {
          push += 1;
          if (push > 7)
          {
            push = 1;
          }

          Serial.print("ColonneAct: ");
          Serial.println(push);

          delay(200);
        }
      }

      grid4.AddPiece(CurrentPlayer, push-1);
      grid4.DisplayGrid();

      if (CurrentPlayer == 'A')
      {CurrentPlayer = 'B';}
      else
      {CurrentPlayer = 'A';}

      delay(200);
    }


    if (grid4.isWinner() == 'X'){
      Serial.println("Joueur A a gagne");
    }

    if (grid4.isWinner() == 'O'){
      Serial.println("Joueur B a gagne");
    }
    
    if (grid4.isGridFull() == 1){
      Serial.println("Match null !");
    }

  }

    

    

