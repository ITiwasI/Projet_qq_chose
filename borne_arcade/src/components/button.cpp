#include "button.h"
#include "Arduino.h"

button::button() : component(1), _pin(-1), _pullUp(false) {}
  
button::~button() {}

void button::init(int p) {
  _pin = p;
  _pullUp = false;
  pinMode(p, INPUT);
}
void button::init(int p, bool pull_up) {
  _pin = p;
  _pullUp = pull_up;
  if (pull_up) {
    pinMode(p, INPUT_PULLUP);
  } else {
    pinMode(p, INPUT);
  }
}

bool button::read() {
  return digitalRead(_pin);
}
bool button::isPressed() {
  if (_pullUp) {
    return !digitalRead(_pin);
  }
  return digitalRead(_pin);
}