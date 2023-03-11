#pragma once

#include "coin.h"
#include "decorator.h"

namespace wacpp
{

std::unique_ptr<ICoin> make_inverted_coin(std::unique_ptr<ICoin> inner);

struct CoinInvert
{
    static std::unique_ptr<ICoin> make_decorator(std::unique_ptr<ICoin> inner);
};

Decoration<CoinInvert> with_inversion();

}