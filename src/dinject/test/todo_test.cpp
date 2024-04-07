#include <gtest/gtest.h>
#include "todo.h"

namespace wacpp::test
{

TEST(todo_test, hello)
{
    Todo todo{};

    ASSERT_EQ("world", todo.hello());
}

}