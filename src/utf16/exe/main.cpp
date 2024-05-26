#include "str.h"

#include <iostream>

#include <gsl/gsl>
#include <wil/result_macros.h>

using namespace wacpp;

int wmain(int argc, wchar_t* argv[])
try
{
    const auto args = gsl::make_span(argv, argc);
    THROW_HR_IF_MSG(E_INVALIDARG, args.size() < 2, "Need at least 2 arguments, but got %llu", args.size());
    const auto s = str::to_utf8(argv[1]);
    std::cout << s << "\n";
    return 0;
}
CATCH_RETURN()