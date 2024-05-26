#include "todo.h"

#include <benchmark/benchmark.h>

using namespace wacpp;

static void todo_short_string(benchmark::State& state)
{
    const auto name = std::wstring{ L"s" };
    auto result = std::wstring{};

    for (auto _ : state)
    {
        const auto t = Todo{ name };
        result = t.name();
    }
}

BENCHMARK(todo_short_string);

static void todo_long_string(benchmark::State& state)
{
    const auto name = std::wstring{ L"looooooooooooong" };
    auto result = std::wstring{};

    for (auto _ : state)
    {
        const auto t = Todo{ name };
        result = t.name();
    }
}

BENCHMARK(todo_long_string);

BENCHMARK_MAIN();