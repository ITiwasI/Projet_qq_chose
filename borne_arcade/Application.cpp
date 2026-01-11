#include "application.h"

#ifndef Arduino_h
#include <Arduino.h>
#endif

application::application(){
}
  
application::~application() {
}  

void application::init(void) {
  Serial.begin(115200);

  button_left.init(2);
  button_right.init(5);
  button_up.init(6);
  button_down.init(3);
  button_select.init(4);
  Serial.println("Application initialized.");
  Serial.println("To reset to menu at any time, press all buttons simultaneously.");
  Serial.println("Use the UP and DOWN buttons to navigate the menu.");
  Serial.println("Press the SELECT button to choose a game.");
  delay(5000);
  selected_game = 1; // Default to first game
  this->afficheMenu();
  game_running = false;
}

void application::run(void) {
  if (button_left.isPressed() && button_right.isPressed() && button_up.isPressed() && button_down.isPressed() && button_select.isPressed()) {
    //Reset to menu
    this->init(); //the games will be reinitialized cause game_running is set to false
  }
  if (!game_running) {
    //Menu logic to select and start a game
    if (button_select.isPressed() && selected_game == 1) {
      game_running = true;
      game_four_in_a_raw.init();
    }
    if (button_select.isPressed() && selected_game == 2) {
      game_running = true;
      game_puissance4.init();
    }
    if (button_select.isPressed() && selected_game == 3) {
      game_running = true;
      game_chess.init();
    }
    if (button_up.isPressed()) {
      selected_game--;
      if (selected_game < 1) {
        selected_game = 1;
      }
    }
    if (button_down.isPressed()) {
      selected_game++;
      if (selected_game > 2) { //  Nombre de jeux total
        selected_game = 2;
      }
    }
    this->afficheMenu();
    Serial.print("Selected game: ");
    Serial.println(selected_game);
    Serial.println("Press the select button to start the game.");
    delay(500);

    
  }else if (selected_game == 1) {
    game_four_in_a_raw.run();
  }else if (selected_game == 2) {
    game_puissance4.run();
  }else if (selected_game == 3) {
    game_chess.run();
  }
}

void application::afficheMenu() {
  Serial.println("\nMenu des jeux:");
  Serial.println("1. Puissance 4");
  Serial.println("2. Puissance 4 Retro");
  Serial.println("3. Echecs");
}