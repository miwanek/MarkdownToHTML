#ifndef CODE_H
#define CODE_H
#include <iostream>
#include "converter.h"

class converter;
using namespace std;
class code
{
    public:

        code();
        void simple_check(string& current);
        bool change( converter& conv, int place, string& current ) ;
        bool get_code_block();
        void reset();
        void set_previous_code_block();
        void correct(string& current);
        void replace_tag(string& current, int i ) ;

    protected:

    private:
         bool code_block;
         bool tab;
         bool space;
         int space_int;
        bool previous_code_block;
};

#endif // CODE_H
