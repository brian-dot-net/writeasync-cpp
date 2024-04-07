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

ConfigIniSerializer::ConfigIniSerializer(RefOrUPtr<ISerializer<ConfigSection>>&& inner) noexcept : m_inner{ std::move(inner) }
{}

void ConfigIniSerializer::serialize([[maybe_unused]] const Config& value, [[maybe_unused]] std::ostream& out)
{
    for (const auto& s : value)
    {
        out << '\n';
        m_inner->serialize(s.second, out);
    }
}

std::unique_ptr<ISerializer<ConfigSection>> make_config_section_ini_serializer()
{
    return std::make_unique<ConfigSectionIniSerializer>();
}

}