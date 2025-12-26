#include <Arduino.h>
#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;      // à connecter à I2C

#include <stdlib.h>
using namespace std;

#include "Row.hpp"
#include "Grid.hpp"

#define buttonNext 0 // bouton normal = D3
#define buttonSelect 14 // button tactile capacitif = D5

int push = 1;
char CurrentPlayer = 'A';

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("begin...");
  lcd.begin(16, 2);

  pinMode(0, INPUT);
  pinMode(14, INPUT);
}


void loop() {
  Grid grid4;

  while ((grid4.isGridFull() != 1) and (grid4.isWinner() == '/')) 
  {
    lcd.setCursor(0, 0);
    lcd.print("JoueurAct: ");
    lcd.print(CurrentPlayer);

    push = 1;
    lcd.setCursor(0, 1);
    lcd.print("ColonneAct: ");
    lcd.print(push);

    while (digitalRead(buttonSelect) == 0)
    {
      if (digitalRead(buttonNext) == 0) {
        delay(150);
        if (digitalRead(buttonNext) == 1) {
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
    }
    
    delay(500);

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
