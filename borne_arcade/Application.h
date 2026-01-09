#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "src/components/joystick.h"
#include "src/components/button.h"
#include "src/games/four_in_a_raw.h"
#include "src/games/puissance4.hpp"
#include "src/games/chess.h"

class application
{
  public :
    application();
    ~application();    

    void init(void);
    void run(void);
    
    //four_in_a_raw game_four_in_a_raw;
    //puissance4 game_puissance4;
    chess game_chess;

};
#endif // APPLICATION_H_

