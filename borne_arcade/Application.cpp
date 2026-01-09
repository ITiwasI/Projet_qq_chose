#include "application.h"
#include <Arduino.h>

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
