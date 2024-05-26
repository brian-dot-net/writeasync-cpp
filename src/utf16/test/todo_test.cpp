#include "todo.h"

#include <gtest/gtest.h>

using namespace wacpp;

TEST(todo_test, name)
{
    const auto t = Todo{ L"xyz" };

    ASSERT_EQ(std::wstring{ L"xyz" }, t.name());
}
