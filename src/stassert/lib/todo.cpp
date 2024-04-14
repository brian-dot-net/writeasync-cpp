#include "todo.h"

namespace wacpp
{

Todo::Todo(std::string name) noexcept : m_name{ std::move(name) }
{}

std::string Todo::operator()() const
{
    return "Hello, " + m_name + "!";
}

}