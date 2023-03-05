#include "example.h"

namespace wacpp
{

Example::Example(const std::string& name)
    : m_name(name)
{
}

std::string Example::greet() const
{
    return "Hello, " + m_name + "!";
}

}