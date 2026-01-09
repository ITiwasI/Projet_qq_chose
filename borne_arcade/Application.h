#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "src/components/joystick.h"
#include "src/games/four_in_a_raw.h"


class application
{
  public :
    application();
    ~application();    

    void init(void);
    void run(void);

    four_in_a_raw game_four_in_a_raw;
};
#endif // APPLICATION_H_

