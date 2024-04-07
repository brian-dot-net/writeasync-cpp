#include "todo.h"

namespace wacpp
{

Todo::Todo() : m_world{ "world" }
{}

const std::string& Todo::hello() const noexcept
{
    return m_world;
}

}