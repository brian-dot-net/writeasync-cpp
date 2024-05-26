#include "todo.h"

namespace wacpp
{

    Todo::Todo(const std::string& name)
        : m_name{name}
    {}

    const std::string& Todo::name() const noexcept
    {
        return m_name;
    }
}