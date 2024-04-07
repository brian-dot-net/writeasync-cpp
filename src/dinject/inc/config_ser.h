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
    ConfigIniSerializer() noexcept;

    void serialize(const Config& value, std::ostream& out) final;

private:
    ConfigSectionIniSerializer m_inner;
};

}