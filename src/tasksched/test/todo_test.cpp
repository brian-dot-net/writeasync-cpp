#include <gtest/gtest.h>
#include "todo.h"

namespace wacpp::test
{

TEST(todo_test, tbd)
{
    ASSERT_EQ(4, todo_add(2, 2));
}

}