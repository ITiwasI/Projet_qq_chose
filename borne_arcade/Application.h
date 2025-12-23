#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "src/components/button.h"

class Application
{
  public :
    Application();
    ~Application();

    void init(void);
    void run(void);

  private :
    // Menu variables
    uint8_t _selector;
    short _lastButtonState;
    int _pressTime;

    button upButton;
    button downButton;
    button leftButton;
    button rightButton;
    button centerButton;

    void updateSelector();

};
#endif