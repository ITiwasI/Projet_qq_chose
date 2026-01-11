#include <stdlib.h>
using namespace std;

#ifndef _row_hpp_
#define _row_hpp_

class Row {
    public:
        int dim;
        char* elements;

        Row();
        ~Row();

        void DisplayRow();
};

#endif 