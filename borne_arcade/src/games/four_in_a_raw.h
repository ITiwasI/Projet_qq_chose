#ifndef FOUR_IN_A_RAW_H_
#define FOUR_IN_A_RAW_H_
#include "game.h"
#include "../components/joystick.h"


class four_in_a_raw : public game {
    private :
        int board[7][7];// 6x7 board for Four In A Row and an extra row for placement logic
        bool end;
    public :
        joystick joystick_four_in_a_raw;
        int player;
        four_in_a_raw();
        ~four_in_a_raw();

        void moveRight();
        void moveLeft();
        void showBoard();

        void init(void) override;
        void run(void) override;
        void endGame();
};

#endif // FOUR_IN_A_RAW_H_

