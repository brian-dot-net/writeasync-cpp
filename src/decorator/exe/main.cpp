#include <iostream>
#include "example.h"

int main()
{
    wacpp::Example example("world");
    std::cout << example.greet() << std::endl;
    return 0;
}
