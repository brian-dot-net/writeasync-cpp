#include <string>
#include <sstream>
#include <iostream>

#include "coin_trace.h"
#include "trace_header.h"

void flip_many(wacpp::ICoin& coin)
{
    for (int i = 0; i < 10; ++i)
    {
        coin.flip();
    }
}

int main()
{
    using namespace wacpp;

    auto tracer = make_ostream_tracer(std::cout);

    auto coin1 = make_double_headed_coin() * with_tracer(tracer * with_header("!"), "TwoHeads");
    flip_many(*coin1);

    auto coin2 = make_fair_coin() * with_tracer(tracer * with_header("$"), "Fair");
    flip_many(*coin2);

    return 0;
}
