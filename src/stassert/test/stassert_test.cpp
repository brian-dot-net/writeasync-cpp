#include <gtest/gtest.h>

#include "example.h"

namespace wacpp::test
{

struct MyVal
{
    const char* name{};
};

TEST(example_test, has_name)
{
    MyVal val{ .name = "world" };
    Example<MyVal> hello{val};

    ASSERT_EQ("Hello, world!", hello());
}

TEST(example_test, has_null_name)
{
    MyVal val{};
    Example<MyVal> hello{ val };

    ASSERT_EQ("Hello, <null>!", hello());
}

}