#include "todo.h"

namespace wacpp
{

    Todo::Todo(const std::wstring& name)
        : m_name{name}
    {}

    const std::wstring& Todo::name() const noexcept
    {
        return m_name;
    }
}