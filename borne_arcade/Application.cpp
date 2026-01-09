#include "application.h"
#include <Arduino.h>

application::application(){
}
  
application::~application() {
}  

void application::init(void) {
  Serial.begin(9600);
  button_left.init(2);
  button_right.init(5);
  button_up.init(6);
  button_down.init(3);
  button_select.init(4);

}

void application::run(void) {
  if (button_left.isPressed()) {
    Serial.println("Left button pressed");
  }
  if (button_right.isPressed()) {
    Serial.println("Right button pressed");
  }
  if (button_up.isPressed()) {
    Serial.println("Up button pressed");
  } 
  if (button_down.isPressed()) {
    Serial.println("Down button pressed");
  }
  if (button_select.isPressed()) {
    Serial.println("Select button pressed");
  }
}
