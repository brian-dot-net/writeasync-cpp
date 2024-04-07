#pragma once

#include <map>
#include <string>
#include <vector>

namespace wacpp
{

class ConfigSection
{
public:
    using Values = std::map<std::string, std::string>;

    ConfigSection(std::string&& name);

    const std::string& name() const noexcept;

    const std::string& value(const std::string& key) const;

    Values::const_iterator begin() const noexcept;
    Values::const_iterator end() const noexcept;

    void insert(std::string&& key, std::string&& value);

    void remove(const std::string& key);

private:
    std::string m_name;
    Values m_values;
};

class Config
{
public:
    using Sections = std::map<std::string, ConfigSection>;

    Config();

    ConfigSection& section(const std::string& name);

    Sections::iterator begin() noexcept;
    Sections::iterator end() noexcept;

    Sections::const_iterator begin() const noexcept;
    Sections::const_iterator end() const noexcept;

    void insert(ConfigSection&& section);

    void remove(const std::string& name);

private:
    Sections m_sections;
};

}