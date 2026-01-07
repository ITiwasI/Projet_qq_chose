#ifndef TESTGAME_H_
#define TESTGAME_H_

#include "game.h"
#include "button.h"

class testGame : public game {
  public :
    testGame();
    ~testGame();
    
    void init(&leftButton, &rightButton);
    void initButton(button *leftB, button *rightB);
    void selectorUpdate(void);
    void run(void);

  private:
    button leftButton;
    button rightButton;
    button upButton;
    button downButton;
    button centerButton;
    bool _buttonSet;
    int _gridX, _gridY;
    short _lastButtonState;
    short mm(short value, short min, short max);

};
#endif