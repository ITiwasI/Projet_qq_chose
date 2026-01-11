#ifndef _puissance4_hpp_
#define _puissance4_hpp_

#include "../components/button.h"

class puissance4 : public game {
  public : 
    puissance4();
    ~puissance4();

    void init() override;
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

#endif // _puissance4_hpp_