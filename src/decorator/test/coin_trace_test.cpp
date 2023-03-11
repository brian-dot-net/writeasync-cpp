#include <gtest/gtest.h>
#include "coin_trace.h"
#include "coin_invert.h"

namespace wacpp::test
{

TEST(coin_trace_test, traces_ctor_and_heads_flips)
{
    auto inner = make_double_headed_coin();
    std::stringstream ss;
    auto tracer = make_ostream_tracer(ss);
    auto coin = make_traced_coin(std::move(inner), tracer, "HeadsCoin");

    ASSERT_TRUE(coin->flip());
    ASSERT_TRUE(coin->flip());

    ASSERT_EQ("Flipping HeadsCoin...\nIt was heads!\nIt was heads!\n", ss.str());
}

TEST(coin_trace_test, traces_ctor_and_tails_flips)
{
    auto inner1 = make_double_headed_coin();
    auto inner2 = make_inverted_coin(std::move(inner1));
    std::stringstream ss;
    auto tracer = make_ostream_tracer(ss);
    auto coin = make_traced_coin(std::move(inner2), tracer, "TailsCoin");

    ASSERT_FALSE(coin->flip());
    ASSERT_FALSE(coin->flip());

    ASSERT_EQ("Flipping TailsCoin...\nIt was tails!\nIt was tails!\n", ss.str());
}

}