#pragma once

#include "coin.h"
#include "decorator.h"

namespace wacpp
{

struct CoinInvert
{
    static std::unique_ptr<ICoin> make_decorator(std::unique_ptr<ICoin> inner);
};

Decoration<CoinInvert> with_inversion();

}