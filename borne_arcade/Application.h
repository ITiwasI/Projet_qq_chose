#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "src/components/joystick.h"
#include "src/components/button.h"
#include "src/games/four_in_a_raw.h"


class application
{
  public :
    application();
    ~application();    

    void init(void);
    void run(void);


    button button_left;
    button button_right;
    button button_select;
    button button_up;
    button button_down;

    int selected_game;
    void afficheMenu();
    bool game_running;
    four_in_a_raw game_four_in_a_raw;
    //declare echecs game here
};
#endif // APPLICATION_H_

