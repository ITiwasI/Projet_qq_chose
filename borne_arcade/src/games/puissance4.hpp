#ifndef _puissance4_hpp_
#define _puissance4_hpp_

#include "game.h"
#include "../components/button.h"

class puissance4 : public game {
  private :
    bool end;
  
  public : 
    puissance4();
    ~puissance4();

    void init(void);
    void run(void);
    
    button rightButton;
    button centerButton;
    
  };

#endif // _puissance4_hpp_