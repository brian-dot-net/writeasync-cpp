#pragma once

#include "config.h"
#include "ser.h"

namespace wacpp
{

class ConfigSectionIniSerializer final : public ISerializer<ConfigSection>
{
public:
    void serialize(const ConfigSection& value, std::ostream& out) final;
};

class ConfigIniSerializer final : public ISerializer<Config>
{
public:
    ConfigIniSerializer(RefOrPtr<ISerializer<ConfigSection>>&& inner) noexcept;

    void serialize(const Config& value, std::ostream& out) final;

private:
    RefOrPtr<ISerializer<ConfigSection>> m_inner;
};

std::unique_ptr<ISerializer<ConfigSection>> make_config_section_ini_serializer_u();

std::shared_ptr<ISerializer<ConfigSection>> make_config_section_ini_serializer_s();

}