#include "str.h"

#include <gtest/gtest.h>

using namespace wacpp;

TEST(to_utf8_test, basic)
{
    const auto input = std::wstring{
        L"\u4F60\u597D\uFF01\u4F60\u4F1A\u8BF4\u4E2D\u6587"
        L"\u5417\uFF1F\u4E00\u4F1A\u513F\u89C1\u3002" };
    const auto expected = std::string{
        "\xE4\xBD\xA0\xE5\xA5\xBD\xEF\xBC\x81\xE4\xBD\xA0\xE4\xBC\x9A\xE8"
        "\xAF\xB4\xE4\xB8\xAD\xE6\x96\x87\xE5\x90\x97\xEF\xBC\x9F\xE4\xB8"
        "\x80\xE4\xBC\x9A\xE5\x84\xBF\xE8\xA7\x81\xE3\x80\x82"
    };

    ASSERT_EQ(expected, str::to_utf8(input));
}

TEST(to_utf8_test, empty)
{
    const auto input = std::wstring{};
    const auto expected = std::string{};

    ASSERT_EQ(expected, str::to_utf8(input));
}
