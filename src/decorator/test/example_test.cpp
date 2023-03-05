#include <gtest/gtest.h>
#include "example.h"

namespace wacpp::test
{

TEST(example_test, produces_greeting)
{
    const Example example("you");

    const auto greeting = example.greet();

    ASSERT_EQ(std::string("Hello, you!"), greeting);
}

}