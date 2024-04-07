#include "config_ser.h"

namespace wacpp
{

void ConfigSectionIniSerializer::serialize(const ConfigSection& value, std::ostream& out)
{
    out << "[" << value.name() << "]";
    for (const auto& [k, v] : value)
    {
        out << '\n' << k << '=' << v;
    }
}

}