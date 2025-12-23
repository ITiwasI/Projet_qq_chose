#ifndef BUTTON_H_
#define BUTTON_H_

#include "component.h"
#include "Arduino.h"

class button : public component {
  private :
    int _pin;
    bool _pullUp;
  public :
    button();
    ~button();
    void init(int p);
    void init(int p, bool pull_up);
    bool read();
	  bool isPressed();
};

#endif