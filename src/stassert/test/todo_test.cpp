#include <gtest/gtest.h>

#include "todo.h"

namespace wacpp::test
{

TEST(todo_test, todo)
{
    Todo hello{ "world" };

    ASSERT_EQ("Hello, world!", hello());
}

}