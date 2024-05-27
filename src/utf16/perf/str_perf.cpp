#include "str.h"

#include <sstream>

#include <benchmark/benchmark.h>

using namespace wacpp;

static void to_utf8_short_string(benchmark::State& state)
{
    const auto input = std::wstring{ L"\u4F60\u597D" };
    auto ss = std::stringstream{};

    for (auto _ : state)
    {
        ss.clear();
        const auto result = str::to_utf8(input);
        ss << result;
    }
}

BENCHMARK(to_utf8_short_string);

static void to_utf8_tiny_block_short_string(benchmark::State& state)
{
    const auto input = std::wstring{ L"\u4F60\u597D" };
    auto ss = std::stringstream{};

    for (auto _ : state)
    {
        ss.clear();
        for (auto c : str::to_utf8<4>(input))
        {
            ss << c;
        }
    }
}

BENCHMARK(to_utf8_tiny_block_short_string);

static void to_utf8_long_string(benchmark::State& state)
{
    const auto input = std::wstring{ L"\u4F60\u597D\uFF01\u4F60\u4F1A\u8BF4\u4E2D\u6587\u5417\uFF1F\u4E00\u4F1A\u513F\u89C1\u3002" };
    auto ss = std::stringstream{};

    for (auto _ : state)
    {
        ss.clear();
        const auto result = str::to_utf8(input);
        ss << result;
    }
}

BENCHMARK(to_utf8_long_string);

static void to_utf8_tiny_block_long_string(benchmark::State& state)
{
    const auto input = std::wstring{ L"\u4F60\u597D\uFF01\u4F60\u4F1A\u8BF4\u4E2D\u6587\u5417\uFF1F\u4E00\u4F1A\u513F\u89C1\u3002" };
    auto ss = std::stringstream{};

    for (auto _ : state)
    {
        ss.clear();
        for (auto c : str::to_utf8<4>(input))
        {
            ss << c;
        }
    }
}

BENCHMARK(to_utf8_tiny_block_long_string);

static std::wstring make_very_long_string()
{
    auto very_long = std::wstring{ L"\u4F60\u597D\uFF01\u4F60\u4F1A\u8BF4\u4E2D\u6587\u5417\uFF1F\u4E00\u4F1A\u513F\u89C1\u3002" };
    for (int i = 0; i < 10; ++i)
    {
        const auto segment = very_long;
        very_long += segment;
    }

    return very_long;
}

static void to_utf8_very_long_string(benchmark::State& state)
{
    const auto input = make_very_long_string();
    auto ss = std::stringstream{};

    for (auto _ : state)
    {
        ss.clear();
        const auto result = str::to_utf8(input);
        ss << result;
    }
}

BENCHMARK(to_utf8_very_long_string);

static void to_utf8_very_long_string_by_char(benchmark::State& state)
{
    const auto input = make_very_long_string();
    auto ss = std::stringstream{};

    for (auto _ : state)
    {
        ss.clear();
        for (auto c : str::to_utf8(input))
        {
            ss << c;
        }
    }
}

BENCHMARK(to_utf8_very_long_string_by_char);

template <size_t N>
static void to_utf8_block_very_long_string(benchmark::State& state)
{
    const auto input = make_very_long_string();
    auto ss = std::stringstream{};

    for (auto _ : state)
    {
        ss.clear();
        for (auto c : str::to_utf8<N>(input))
        {
            ss << c;
        }
    }
}

static void to_utf8_64_block_very_long_string(benchmark::State& state)
{
    to_utf8_block_very_long_string<64>(state);
}

BENCHMARK(to_utf8_64_block_very_long_string);

static void to_utf8_256_block_very_long_string(benchmark::State& state)
{
    to_utf8_block_very_long_string<256>(state);
}

BENCHMARK(to_utf8_256_block_very_long_string);

static void to_utf8_1024_block_very_long_string(benchmark::State& state)
{
    to_utf8_block_very_long_string<1024>(state);
}

BENCHMARK(to_utf8_1024_block_very_long_string);

static void to_utf8_4096_block_very_long_string(benchmark::State& state)
{
    to_utf8_block_very_long_string<4096>(state);
}

BENCHMARK(to_utf8_4096_block_very_long_string);

static void to_utf8_16384_block_very_long_string(benchmark::State& state)
{
    to_utf8_block_very_long_string<16384>(state);
}

BENCHMARK(to_utf8_16384_block_very_long_string);

BENCHMARK_MAIN();