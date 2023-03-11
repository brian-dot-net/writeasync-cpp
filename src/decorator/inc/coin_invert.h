#pragma once

#include "coin.h"

namespace wacpp
{

std::unique_ptr<ICoin> make_inverted_coin(std::unique_ptr<ICoin> inner);

}