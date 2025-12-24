#include "joystick.h"

joystick::joystick() {
    this->pinX = ANALOG_X_PIN;
    this->pinY = ANALOG_Y_PIN;
    this->pinButton = ANALOG_BUTTON_PIN;
}

joystick::joystick(int pinX, int pinY, int pinButton){
    this->pinX = pinX;
    this->pinY = pinY;
    this->pinButton = pinButton;
}

joystick::~joystick() {
}

void joystick::init() {
  // Initialization code for joystick pins
    pinMode(pinButton, INPUT_PULLUP);
}

static byte readAnalogAxisLevel(int pin) 
{ 
	 return map(analogRead(pin), 0, 1023, 0, 255); 
} 
	 
static bool isAnalogButtonPressed(int pin) 
{ 
	return digitalRead(pin) == 0; 
}
 
int joystick::readInputX() {
    xAxis = readAnalogAxisLevel(pinX) - ANALOG_X_CORRECTION;
    return xAxis;
}

int joystick::readInputY() {
    yAxis = readAnalogAxisLevel(pinY) - ANALOG_Y_CORRECTION;
    return yAxis;
}

bool joystick::isButtonPressed() {
    buttonPressed = isAnalogButtonPressed(pinButton);
    return buttonPressed;
}