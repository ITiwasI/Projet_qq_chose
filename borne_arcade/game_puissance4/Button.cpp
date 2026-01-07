#include "Component.hpp"
#include "Button.hpp"

Button::Button() {}
  
Button::~Button() {}

void Button::init(int p) {
    pin = p;
    pinMode(p, INPUT);
}

bool Button::read() {
    return digitalRead(pin);
}

bool Button::isPressed() {
    if (digitalRead(pin) == 0) {
        delay(150);
        if (digitalRead(pin) == 1) {
            return 1;
        }
        else {
          return 0;
        }
    }
    else {
      return 0;
    }
}

