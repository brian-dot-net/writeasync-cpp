#include <stdexcept>

#include "config.h"

namespace wacpp
{

ConfigSection::ConfigSection(std::string&& name) : m_name{ std::move(name) }, m_values{}
{}

const std::string& ConfigSection::name() const noexcept
{
    return m_name;
}

const std::string& ConfigSection::value(const std::string& key) const
{
    const auto it = m_values.find(key);
    if (it == m_values.cend())
    {
        throw std::runtime_error("Key not found");
    }

    return it->second;
}

ConfigSection::Values::const_iterator ConfigSection::begin() const noexcept
{
    return m_values.cbegin();
}

ConfigSection::Values::const_iterator ConfigSection::end() const noexcept
{
    return m_values.cend();
}

void ConfigSection::insert(std::string&& key, std::string&& value)
{
    m_values.emplace(std::move(key), std::move(value));
}

void ConfigSection::remove(const std::string& key)
{
    const auto it = m_values.find(key);
    if (it != m_values.end())
    {
        m_values.erase(it);
    }
}

Config::Config() : m_sections{}
{}

ConfigSection& Config::section(const std::string& name)
{
    const auto it = m_sections.find(name);
    if (it == m_sections.end())
    {
        throw std::runtime_error("Section not found");
    }

    return it->second;
}

Config::Sections::iterator Config::begin() noexcept
{
    return m_sections.begin();
}

Config::Sections::const_iterator Config::begin() const noexcept
{
    return m_sections.cbegin();
}

Config::Sections::iterator Config::end() noexcept
{
    return m_sections.end();
}

Config::Sections::const_iterator Config::end() const noexcept
{
    return m_sections.cend();
}

void Config::insert(ConfigSection&& section)
{
    std::string name{ section.name() };
    m_sections.emplace(name, std::move(section));
}

void Config::remove(const std::string& name)
{
    const auto it = m_sections.find(name);
    if (it != m_sections.end())
    {
        m_sections.erase(it);
    }
}

}