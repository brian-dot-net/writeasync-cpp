#pragma once

#include <ostream>

namespace wacpp
{

template <typename T>
class ISerializer
{
public:
    virtual void serialize(const T& value, std::ostream& out) = 0;

    virtual ~ISerializer() = default;
};

}