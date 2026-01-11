#include <stdlib.h>
using namespace std;

#ifndef _grid_hpp_
#define _grid_hpp_

#include "row.hpp"

class Grid {
    public:
        Row** grid;;

        Grid();
        ~Grid();

        void DisplayGrid();
        void AddPiece(char Player, int C);
        bool isGridFull();
        char isWinner();
};

#endif