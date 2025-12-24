#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "games\game.h"
#include "components\component.h"

class application
{
  public :
    application();
    ~application();    

    void init(void);
    void run(void);
};
#endif