#include <iostream>

#include "todo.h"

int main()
{
    using namespace wacpp;

    Todo hello{ "world" };
    std::cout << hello() << "\n";

    return 0;
}
