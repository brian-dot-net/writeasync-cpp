#include <iostream>

#include "todo.h"

int main()
{
    using namespace wacpp;

    int x = 2;
    int y = 3;

    std::cout << "Q: What is " << x << " + " << y << "?\n";
    std::cout << "A: " << todo_add(x, y) << "\n";

    return 0;
}
