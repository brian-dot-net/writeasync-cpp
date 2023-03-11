#include <string>
#include <sstream>
#include <iostream>

#include "coin_trace.h"

void flip_many(wacpp::ICoin& coin)
{
    for (int i = 0; i < 10; ++i)
    {
        coin.flip();
    }
}

int main()
{
    auto tracer = wacpp::make_ostream_tracer(std::cout);

    auto inner1 = wacpp::make_double_headed_coin();
    auto coin1 = wacpp::make_traced_coin(std::move(inner1), tracer, "TwoHeads");
    flip_many(*coin1);

    auto inner2 = wacpp::make_fair_coin();
    auto coin2 = wacpp::make_traced_coin(std::move(inner2), tracer, "Fair");
    flip_many(*coin2);

    return 0;
}
