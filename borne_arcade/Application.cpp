#include "application.h"
#include <Arduino.h>

// Force compilation of joystick implementation in this TU (fix for Arduino build in nested folder)
#include "components/joystick/joystick.cpp"
// Also include base component implementation so constructors/destructors are linked
#include "components/component.cpp"

application::application(){
}
  
application::~application() {
}  

void application::init(void) {
    Serial.begin(9600);
    js.init();
}

void application::run(void) {
    Serial.print("X:"); 
    Serial.println(js.readInputX()); 
    
    Serial.print("Y:"); 
    Serial.println(js.readInputY()); 
    
    if (js.isButtonPressed()) { 
      Serial.println("Button pressed"); 
    } else { 
      Serial.println("Button not pressed"); 
    } 
    
    delay(200); 
}
