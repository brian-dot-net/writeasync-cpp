#include <string>
#include <sstream>
#include <iostream>

#include "coin.h"
#include "trace.h"

void flip_one(wacpp::ICoin& coin, wacpp::ITracer& tracer)
{
    if (coin.flip())
    {
        tracer.trace("It was heads!");
    }
    else
    {
        tracer.trace("It was tails!");
    }
}

void flip_many(wacpp::ICoin& coin, wacpp::ITracer& tracer, const std::string& name)
{
    std::stringstream ss;
    ss << "Flipping " << name << "...";
    tracer.trace(ss.str());

    for (int i = 0; i < 10; ++i)
    {
        flip_one(coin, tracer);
    }
}

int main()
{
    auto tracer = wacpp::make_ostream_tracer(std::cout);

    auto coin1 = wacpp::make_double_headed_coin();
    flip_many(*coin1, *tracer, "TwoHeads");

    auto coin2 = wacpp::make_fair_coin();
    flip_many(*coin2, *tracer, "Fair");

    return 0;
}
