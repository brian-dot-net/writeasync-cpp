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

ConfigIniSerializer::ConfigIniSerializer() noexcept : m_inner{}
{}

void ConfigIniSerializer::serialize([[maybe_unused]] const Config& value, [[maybe_unused]] std::ostream& out)
{
    for (const auto& s : value)
    {
        out << '\n';
        m_inner.serialize(s.second, out);
    }
}

}