#ifndef _button_hpp_
#define _button_hpp_

#include <Arduino.h>
#include "component.hpp"

class Button : public Component
{
  private :
    int pin;

  public :
    Button();
    ~Button();  
    void init(int p);
    bool read();
    bool isPressed();  
    
	
};

#endif