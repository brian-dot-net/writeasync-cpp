#pragma once

#include <chrono>

namespace wacpp
{

using DateTime = std::chrono::local_time<std::chrono::seconds>;

DateTime make_date_time(std::chrono::year_month_day date, std::chrono::seconds time) noexcept;

}