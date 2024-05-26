#pragma once

#include <string>

namespace wacpp
{

class Todo
{
public:
    Todo(const std::wstring& name);

    const std::wstring& name() const noexcept;

private:
    std::wstring m_name;
};

}