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

ConfigIniSerializer::ConfigIniSerializer(RefOrPtr<ISerializer<ConfigSection>>&& inner) noexcept : m_inner{ std::move(inner) }
{}

void ConfigIniSerializer::serialize(const Config& value, std::ostream& out)
{
    for (const auto& s : value)
    {
        out << '\n';
        m_inner->serialize(s.second, out);
    }
}

std::unique_ptr<ISerializer<ConfigSection>> make_config_section_ini_serializer_u()
{
    return std::make_unique<ConfigSectionIniSerializer>();
}

std::shared_ptr<ISerializer<ConfigSection>> make_config_section_ini_serializer_s()
{
    return std::make_shared<ConfigSectionIniSerializer>();
}

}