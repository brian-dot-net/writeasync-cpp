#include <iostream>

#include "todo.h"

int main()
{
    using namespace wacpp;

    Todo todo{};
    std::cout << "Hello, " << todo.hello() << "!\n";
    return 0;
}
