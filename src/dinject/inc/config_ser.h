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

}