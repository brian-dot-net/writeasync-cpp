#pragma once

#include <string>

namespace wacpp
{

class Todo
{
public:
    Todo();

    const std::string& hello() const noexcept;

private:
    std::string m_world;
};

}