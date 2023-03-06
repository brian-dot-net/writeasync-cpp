#include <iostream>
#include <string>
#include "coin.h"

void flip_one(wacpp::ICoin& coin)
{
    if (coin.flip())
    {
        std::cout << "It was heads!" << std::endl;
    }
    else
    {
        std::cout << "It was tails!" << std::endl;
    }
}

void flip_many(wacpp::ICoin& coin, const std::string& name)
{
    std::cout << "Flipping " << name << "..." << std::endl;
    for (int i = 0; i < 10; ++i)
    {
        flip_one(coin);
    }
}

int main()
{
    auto coin1 = wacpp::make_double_headed_coin();
    auto coin2 = wacpp::make_fair_coin();

    flip_many(*coin1, "TwoHeads");
    flip_many(*coin2, "Fair");

    return 0;
}
