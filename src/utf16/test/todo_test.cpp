#include "todo.h"

#include <gtest/gtest.h>

using namespace wacpp;

TEST(todo_test, name)
{
    const auto t = Todo{ "xyz" };

    ASSERT_EQ(std::string{ "xyz" }, t.name());
}
