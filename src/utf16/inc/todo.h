#pragma once

#include <string>

namespace wacpp
{

class Todo
{
public:
    Todo(const std::string& name);

    const std::string& name() const noexcept;

private:
    std::string m_name;
};

}