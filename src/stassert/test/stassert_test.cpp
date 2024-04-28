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

#ifdef STASSERT_NAME_HAS_WRONG_TYPE
struct WrongType
{
    std::string name{};
};

TEST(example_test, name_has_wrong_type)
{
    WrongType val{};

    Example<WrongType> hello{ val };
}
#endif

#ifdef STASSERT_NAME_HAS_WRONG_SIZE
struct WrongSize
{
    const char* name{};
    const char* extra{};
};

TEST(example_test, name_has_wrong_size)
{
    WrongSize val{};

    Example<WrongSize> hello{ val };
}
#endif

}