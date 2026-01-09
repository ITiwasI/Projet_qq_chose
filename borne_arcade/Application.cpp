#include "application.h"
#include <Arduino.h>

#include "components/joystick/joystick.cpp"
#include "components/component.cpp"
#include "games/game.cpp"
#include "games/four_in_a_raw/four_in_a_raw.cpp"

application::application(){
}
  
application::~application() {
}  

void application::init(void) {
  Serial.begin(9600);
  game_four_in_a_raw.init();
}

void application::run(void) {
  game_four_in_a_raw.run();
}
