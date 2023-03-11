#include <gtest/gtest.h>
#include "coin_trace.h"
#include "coin_invert.h"

namespace wacpp::test
{

TEST(coin_trace_test, traces_ctor_and_heads_flips)
{
    std::stringstream ss;
    auto tracer = make_ostream_tracer(ss);
    auto coin = make_double_headed_coin() * with_tracer(tracer, "HeadsCoin");

    ASSERT_TRUE(coin->flip());
    ASSERT_TRUE(coin->flip());

    ASSERT_EQ("Flipping HeadsCoin...\nIt was heads!\nIt was heads!\n", ss.str());
}

TEST(coin_trace_test, traces_ctor_and_tails_flips)
{
    std::stringstream ss;
    auto tracer = make_ostream_tracer(ss);
    auto coin = make_double_headed_coin() * with_inversion() * with_tracer(tracer, "TailsCoin");

    ASSERT_FALSE(coin->flip());
    ASSERT_FALSE(coin->flip());

    ASSERT_EQ("Flipping TailsCoin...\nIt was tails!\nIt was tails!\n", ss.str());
}

}