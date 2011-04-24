#include <iostream>
#include "Calc.h"

int main(int arc, char* argv[])
{
    Calc c;
    std::cout << c.calc(argv[1]) << std::endl;

    return 0;
}
