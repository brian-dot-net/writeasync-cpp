#include "str.h"

#include <benchmark/benchmark.h>

using namespace wacpp;

static void to_utf8_short_string(benchmark::State& state)
{
    const auto input = std::wstring{ L"\u4F60\u597D" };
    auto result = std::string{};

    for (auto _ : state)
    {
        result = str::to_utf8(input);
    }
}

BENCHMARK(to_utf8_short_string);

static void to_utf8_long_string(benchmark::State& state)
{
    const auto input = std::wstring{ L"\u4F60\u597D\uFF01\u4F60\u4F1A\u8BF4\u4E2D\u6587\u5417\uFF1F\u4E00\u4F1A\u513F\u89C1\u3002" };
    auto result = std::string{};

    for (auto _ : state)
    {
        result = str::to_utf8(input);
    }
}

BENCHMARK(to_utf8_long_string);

BENCHMARK_MAIN();