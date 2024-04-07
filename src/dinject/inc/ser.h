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
class RefOrPtr
{
public:
    RefOrPtr(T& ref) noexcept : m_value{ &ref }
    {}

    RefOrPtr(std::shared_ptr<T> p) noexcept : m_value{ std::move(p) }
    {}

    RefOrPtr(std::unique_ptr<T> p) noexcept : m_value{ std::move(p) }
    {}

    T* operator->()
    {
        if (std::holds_alternative<T*>(m_value))
        {
            return std::get<T*>(m_value);
        }
        else if (std::holds_alternative<std::shared_ptr<T>>(m_value))
        {
            return std::get<std::shared_ptr<T>>(m_value).get();
        }
        else
        {
            return std::get<std::unique_ptr<T>>(m_value).get();
        }
    }

private:
    std::variant<T*, std::shared_ptr<T>, std::unique_ptr<T>> m_value;
};

}