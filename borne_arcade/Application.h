#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "src/button.h"
#include "src/game.h"
#include "src/testGame.h"

class application
{
  public :
    application();
    ~application();

    void init(void);
    void run(void);

  private :
    // Menu variables
    int8_t _selector;
    short _lastButtonState;

    button leftButton;
    button rightButton;
    button centerButton;

    game currentGame;

    void updateSelector();
    void runGame();

};
#endif