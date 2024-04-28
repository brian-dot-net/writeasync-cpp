#pragma once

#include <string>

namespace wacpp
{

std::string get_name(const char* raw);

template <typename T>
class Example
{
public:
    Example(const T& input) : m_name{ get_name(input.name) }
    {}

    std::string operator()() const
    {
        return "Hello, " + m_name + "!";
    }

private:
    std::string m_name;
};

}