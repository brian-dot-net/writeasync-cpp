#include "str.h"

#include <cstdint>

#include <gtest/gtest.h>

using namespace wacpp;

template <size_t N>
    requires (N > 3)
static void test_utf8_block(const std::wstring& input, const std::string& expected)
{
    auto ss = std::stringstream{};

    for (const auto c : str::to_utf8<N>(input))
    {
        ss << c;
    }

    ASSERT_EQ(expected, str::to_utf8(input));
}

template <size_t N>
    requires (N > 3)
static void fail_utf8_block(const std::wstring& input)
{
    auto fail = [&](const std::wstring& s) {
        auto ss = std::stringstream{};

        for (const auto c : str::to_utf8<N>(s))
        {
            ss << c;
        }
        };

    ASSERT_THROW(fail(input), wil::ResultException);
}

TEST(to_utf8_test, basic_block)
{
    const auto input = std::wstring{
        L"\u4F60\u597D\uFF01\u4F60\u4F1A\u8BF4\u4E2D\u6587"
        L"\u5417\uFF1F\u4E00\u4F1A\u513F\u89C1\u3002" };
    const auto expected = std::string{
        "\xE4\xBD\xA0\xE5\xA5\xBD\xEF\xBC\x81\xE4\xBD\xA0\xE4\xBC\x9A\xE8"
        "\xAF\xB4\xE4\xB8\xAD\xE6\x96\x87\xE5\x90\x97\xEF\xBC\x9F\xE4\xB8"
        "\x80\xE4\xBC\x9A\xE5\x84\xBF\xE8\xA7\x81\xE3\x80\x82"
    };

    test_utf8_block<4>(input, expected);
    test_utf8_block<9>(input, expected);
    test_utf8_block<14>(input, expected);
    test_utf8_block<19>(input, expected);
}

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

TEST(to_utf8_test, invalid_input)
{
    static constexpr const auto bad = std::array<uint16_t, 2>{0xD800, 0x0000};
    const auto input = std::wstring{ reinterpret_cast<const wchar_t*>(bad.data()) };

    ASSERT_THROW(str::to_utf8(input), wil::ResultException);
}

TEST(to_utf8_test, invalid_input_block)
{
    static constexpr const auto bad = std::array<uint16_t, 2>{0xD800, 0x0000};
    const auto input = std::wstring{ reinterpret_cast<const wchar_t*>(bad.data()) };

    fail_utf8_block<4>(input);
}

TEST(to_utf8_test, emoji)
{
    const auto raw = std::array<uint16_t, 5>{0xD83D, 0xDE0E, 0xD83D, 0xDC4D, 0x0000};
    const auto input = std::wstring{ reinterpret_cast<const wchar_t*>(raw.data()) };
    const auto expected = std::string{ "\xF0\x9F\x98\x8E\xF0\x9F\x91\x8D" };

    ASSERT_EQ(expected, str::to_utf8(input));
}

TEST(to_utf8_test, emoji_block)
{
    const auto raw = std::array<uint16_t, 5>{0xD83D, 0xDE0E, 0xD83D, 0xDC4D, 0x0000};
    const auto input = std::wstring{ reinterpret_cast<const wchar_t*>(raw.data()) };
    const auto expected = std::string{ "\xF0\x9F\x98\x8E\xF0\x9F\x91\x8D" };

    test_utf8_block<4>(input, expected);
    test_utf8_block<9>(input, expected);
    test_utf8_block<14>(input, expected);
    test_utf8_block<19>(input, expected);
}
