#include "puissance4.hpp"
#include "puissance4/grid.hpp"

puissance4::puissance4() : _buttonSet(false) {}
puissance4::~puissance4() {}

void puissance4::init() {
    _quit = false;
    _lastButtonState = 0;

    int push = 1;
    char CurrentPlayer = 'A';
    Grid grid4;
    grid4.DisplayGrid();
}


void puissance4::run(void) {
  while (!_quit) {
    
    while ((grid4.isGridFull() != 1) and (grid4.isWinner() == '/')) 
    {
      Serial.print("JoueurAct: ");
      Serial.println(CurrentPlayer);
      
      push = 1;
      Serial.print("ColonneAct: ");
      Serial.println(push);
      
      while (!centerButton.isPressed())
      {
        if (right.isPressed()) 
        {
          push += 1;
          if (push > 7)
          {
            push = 1;
          }

          Serial.print("ColonneAct: ");
          Serial.println(push);
        }
      }
      
      Serial.println(" "); Serial.println(" "); Serial.println(" ");

      grid4.AddPiece(CurrentPlayer, push-1);
      grid4.DisplayGrid();

      if (CurrentPlayer == 'A')
      {CurrentPlayer = 'B';}
      else
      {CurrentPlayer = 'A';}
    }


    if (grid4.isWinner() == 'X'){
      Serial.print("Joueur A a gagne");
    }

    if (grid4.isWinner() == 'O'){
      Serial.print("Joueur B a gagne");
    }
    
    if (grid4.isGridFull() == 1){
      Serial.print("Match null !");
    }

  }

  Serial.println("quit");
}
    

    

