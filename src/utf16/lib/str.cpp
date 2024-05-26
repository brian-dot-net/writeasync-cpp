#include "str.h"

#include <Windows.h>

#include <gsl/gsl>
#include <wil/result_macros.h>

namespace wacpp::str
{

std::string to_utf8(const std::wstring& utf16_input)
{
    const auto input_size = gsl::narrow<int>(utf16_input.size());
    if (input_size == 0)
    {
        return {};
    }

    const auto required_size = WideCharToMultiByte(CP_UTF8, 0, utf16_input.c_str(), input_size, nullptr, 0, nullptr, nullptr);
    THROW_LAST_ERROR_IF_MSG(required_size == 0, "Failed to get required size");

    auto utf8_result = std::string(required_size, '\0');

    const auto actual_size = WideCharToMultiByte(CP_UTF8, 0, utf16_input.c_str(), input_size, utf8_result.data(), required_size, nullptr, nullptr);
    THROW_LAST_ERROR_IF_MSG(actual_size == 0, "Failed to convert to UTF-8");

    return utf8_result;
}

}