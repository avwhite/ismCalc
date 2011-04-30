#include <iostream>
#include "Calc.h"

int main(int arc, char* argv[])
{
    Calc c;
    optDouble res = c.calc(argv[1]);
    if(res.second == true)
        std::cout << c.calc(argv[1]).first << std::endl;
    else
        std::cout << "ERROR" << std::endl;

    return 0;
}
