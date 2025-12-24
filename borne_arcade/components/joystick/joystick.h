#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "../component.h"

#define ANALOG_X_PIN A4
#define ANALOG_Y_PIN A3 
#define ANALOG_BUTTON_PIN A2
	 
//Default values when axis not actioned 
#define ANALOG_X_CORRECTION 128 
#define ANALOG_Y_CORRECTION 128 

class joystick: public component {
private:
    int pinX;
    int pinY;
    int pinButton;
    int xAxis;
    int yAxis;
    bool buttonPressed;
public:
    joystick();
    ~joystick();
    joystick(int pinX, int pinY, int pinButton);

    void init() override;

    int readInputX();
    int readInputY();
    bool isButtonPressed();
};


#endif // JOYSTICK_H