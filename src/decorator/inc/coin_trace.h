#pragma once

#include "coin.h"
#include "trace.h"

namespace wacpp
{

std::unique_ptr<ICoin> make_traced_coin(std::unique_ptr<ICoin> coin, std::shared_ptr<ITracer> tracer, const std::string& name);

}