#pragma once

#include <memory>
#include <ostream>
#include <variant>

namespace wacpp
{

template <typename T>
class ISerializer
{
public:
    virtual void serialize(const T& value, std::ostream& out) = 0;

    virtual ~ISerializer() = default;
};

template <typename T>
class RefOrUPtr
{
public:
    RefOrUPtr(T& ref) noexcept : m_value{ &ref }
    {}

    RefOrUPtr(std::unique_ptr<T> p) noexcept : m_value{ std::move(p) }
    {}

    T* operator->()
    {
        if (std::holds_alternative<T*>(m_value))
        {
            return std::get<T*>(m_value);
        }
        else
        {
            return std::get<std::unique_ptr<T>>(m_value).get();
        }
    }

private:
    std::variant<T*, std::unique_ptr<T>> m_value;
};

}