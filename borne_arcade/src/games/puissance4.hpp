#ifndef _puissance4_hpp_
#define _puissance4_hpp_

#include "game.h"
#include "../components/button.h"

class puissance4 : public game {
  pulic : 
    puissance4();
    ~puissance4();

    void init(&leftButton, &rightButton, &upButton, &downButton, &centerButton);
    void run(void);
    
  private :
    button leftButton;
    button rightButton;
    button upButton;
    button downButton;
    button centerButton;
    bool _buttonSet;
    short _lastButtonState;
    
  };

#endif