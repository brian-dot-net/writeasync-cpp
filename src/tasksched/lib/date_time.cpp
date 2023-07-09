#include "date_time.h"

namespace wacpp
{

DateTime make_date_time(std::chrono::year_month_day date, std::chrono::seconds time) noexcept
{
    return std::chrono::local_time<std::chrono::days>(date) + time;
}

}