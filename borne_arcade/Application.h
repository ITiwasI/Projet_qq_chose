#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "components/joystick/joystick.h"


class application
{
  public :
    application();
    ~application();    

    void init(void);
    void run(void);

    joystick js;
};
#endif // APPLICATION_H_

