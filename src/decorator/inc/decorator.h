#pragma once

#include <functional>
#include <memory>
#include <tuple>

namespace wacpp
{

template <typename D, typename ...Args>
struct Decoration
{
    std::tuple<Args...> args;
};

template <typename D, typename ...Args>
Decoration<D, Args...> with_decoration(Args... args)
{
    return { std::forward_as_tuple(args...) };
}

template <typename C, typename D, typename ...Args>
std::unique_ptr<C> operator*(std::unique_ptr<C> decorated, Decoration<D, Args...>&& decoration)
{
    return std::apply(std::bind_front(&D::make_decorator, std::move(decorated)), decoration.args);
}

template <typename C, typename D, typename ...Args>
std::shared_ptr<C> operator*(std::shared_ptr<C> decorated, Decoration<D, Args...>&& decoration)
{
    return std::apply(std::bind_front(&D::make_decorator, std::move(decorated)), decoration.args);
}

}