#include <iostream>

#include "config.h"

int main()
{
    using namespace wacpp;

    Config c{};
    for (const auto& [name, _] : c)
    {
        std::cout << name << "\n";
    }

    return 0;
}
