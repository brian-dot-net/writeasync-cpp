#include <gtest/gtest.h>

#include "date_time.h"

using namespace std::chrono_literals;

namespace wacpp::test
{

TEST(date_time_test, make)
{
    auto dt = make_date_time(2001y / 2 / 3, 4h + 5min + 6s);

    ASSERT_EQ("2001-02-03 04:05:06", std::format("{:%Y-%m-%d %T}", dt));
}

}