#include <iostream>
#include "coin.h"

int main()
{
    auto coin = wacpp::make_double_headed_coin();
    if (coin->flip())
    {
        std::cout << "It was heads!" << std::endl;
    }
    else
    {
        std::cout << "It was tails!" << std::endl;
    }

    return 0;
}
