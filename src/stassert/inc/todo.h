#pragma once

#include <string>

namespace wacpp
{

class Todo
{
public:
    Todo(std::string name) noexcept;

    std::string operator()() const;

private:
    std::string m_name;
};

}