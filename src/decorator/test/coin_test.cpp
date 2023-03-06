#include <gtest/gtest.h>
#include "coin.h"

namespace wacpp::test
{

TEST(coin_test, double_headed_coin_always_heads)
{
    auto coin = make_double_headed_coin();
    int heads = 0;

    for (int i = 0; i < 100; ++i)
    {
        if (coin->flip())
        {
            ++heads;
        }
    }

    ASSERT_EQ(100, heads);
}

TEST(coin_test, fair_coin_sometimes_heads)
{
    auto coin = make_fair_coin();
    int heads = 0;

    for (int i = 0; i < 100; ++i)
    {
        if (coin->flip())
        {
            ++heads;
        }
    }

    ASSERT_GT(heads, 0);
}

}