#include <Arduino.h>
#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;      // à connecter à I2C
// bouton normal sur D3
// button tactile capacitif sur D5

#include <stdlib.h>
using namespace std;

#include "Row.hpp"
#include "Grid.hpp"
#include "Component.hpp"
#include "Button.hpp"


int push = 1;
char CurrentPlayer = 'A';

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("begin...");
  lcd.begin(16, 2);

}


void loop() {
  Button buttonNext;
  buttonNext.init(0);
  Button buttonSelect;
  buttonSelect.init(14);

  Grid grid4;
  grid4.DisplayGrid();

  while ((grid4.isGridFull() != 1) and (grid4.isWinner() == '/')) 
  {
    lcd.setCursor(0, 0);
    lcd.print("JoueurAct: ");
    lcd.print(CurrentPlayer);

    push = 1;
    lcd.setCursor(0, 1);
    lcd.print("ColonneAct: ");
    lcd.print(push);

    while (buttonSelect.read() == 0)
    {
      if (buttonNext.isPressed()) 
      {
        push += 1;
        if (push > 7)
        {
          push = 1;
        }
        lcd.setCursor(0, 1);
        lcd.print("ColonneAct: ");
        lcd.print(push);
      }
    }
    
    delay(500);  // pour que buttonSelect considere 1 seule pression

    Serial.println(" "); Serial.println(" "); Serial.println(" ");

    grid4.AddPiece(CurrentPlayer, push-1);
    grid4.DisplayGrid();

    if (CurrentPlayer == 'A')
    {CurrentPlayer = 'B';}
    else
    {CurrentPlayer = 'A';}
  }

  lcd.clear();

  if (grid4.isWinner() == 'X'){
    lcd.setCursor(0, 0);
    lcd.print("Joueur A a gagne");
    lcd.setCursor(0, 1);
    lcd.print("Bravo !");
  }

  if (grid4.isWinner() == 'O'){
    lcd.setCursor(0, 0);
    lcd.print("Joueur B a gagne");
    lcd.setCursor(0, 1);
    lcd.print("Bravo !");
  }
  
   if (grid4.isGridFull() == 1){
    lcd.setCursor(0, 0);
    lcd.print("Match nul");
  }

  delay(10000);
  exit(0);
}
